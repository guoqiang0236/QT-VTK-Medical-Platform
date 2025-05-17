/*****************************************************************************
 *                                                                           *
 *      COPYRIGHT  2025  -  PULSEVISION TECHNOLOGIES SHANGHAI CO. LTD        *
 *                                                                           *
 *                                                                           *
 * This is the confidential proprietary property of PulseVision Technologies *
 * Shanghai Co. Ltd., of Room 703, Building 3 No. 99 Haiji Six Road Lin Gang *
 * New City Shanghai China. Absolutely no use, dissemination or copying in   *
 * any media of any portion of this material is to be made without the prior *
 * written authorisation of PulseVision Technologies Shanghai China.         *
 * All rights reserved.  In the event of publication, statutory copyright    *
 * protection is hereby claimed.                                             *
 *                                                                           *
 * Copyright 2025, PulseVision Technologies Shanghai Co. Ltd                 *
 *                                                                           *
 ****************************************************************************/
 //
 // PROGRAM : OpencvUtil.cpp : Opencv video service class
 //
 // HISTORY :
 //
 //    Date     Author    Description
 // ------------------------------------------------------------------------
 // 05/03/2025  郭强                  实现视频捕捉
 //
 //***************************************************************************

#include "pch.h"
#include "OpenCVUtil.h"
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <mmsystem.h>  

//------------------------------------------------------------------
//
// 函数名: OpencvUtil()
// 描述: OpencvUtil类的构造函数，初始化成员变量
// 输入: 无
// 输出: 无
//------------------------------------------------------------------


OpencvUtil::OpencvUtil(QObject* parent):
	isRecording(false), 
	hRecordingThread(NULL), 
	videoWriter(nullptr),
	m_cap(nullptr)
{
	// 初始化临界区，用于线程同步
	InitializeCriticalSection(&csRecording);
}

//------------------------------------------------------------------
//
// 函数名: ~OpencvUtil()
// 描述: OpencvUtil类的析构函数，停止录制并释放资源
// 输入: 无
// 输出: 无
//------------------------------------------------------------------
OpencvUtil::~OpencvUtil() {
	
	StopRecording();
	DeleteCriticalSection(&csRecording);
}

//------------------------------------------------------------------
//
// 函数名: StartRecording()
// 描述: 开始录制屏幕区域到指定路径的视频文件
// 输入: 要录制的屏幕区域矩形，视频文件输出路径
// 输出: 无
//------------------------------------------------------------------
void OpencvUtil::StartRecording(const RECT& rect, const char*  path) {
	// 进入临界区，确保线程安全
	EnterCriticalSection(&csRecording);
	// 如果已经在录制，则直接返回
	if (isRecording) {
		LeaveCriticalSection(&csRecording);
		return;
	}

	captureRect = rect;
	outputPath = path;
	// 计算录制区域的宽度和高度
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	// 初始化VideoWriter
	cv::VideoWriter* writer = new cv::VideoWriter(
		outputPath,
		cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
		30.0,
		cv::Size(width, height),
		true
	);

	// 如果VideoWriter打开失败，释放资源并返回
	if (!writer->isOpened()) {
		delete writer;
		LeaveCriticalSection(&csRecording);
		return;
	}

	videoWriter = writer;
	isRecording = true;

	// 创建录制线程
	hRecordingThread = CreateThread(
		NULL,
		0,
		RecordingThread,
		this,
		0,
		NULL
	);

	LeaveCriticalSection(&csRecording);
}

//------------------------------------------------------------------
//
// 函数名: StopRecording()
// 描述: 停止录制，释放相关资源
// 输入: 无
// 输出: 无
//------------------------------------------------------------------
void OpencvUtil::StopRecording() {
	EnterCriticalSection(&csRecording);
	// 如果没有在录制，则直接返回
	if (!isRecording) {
		LeaveCriticalSection(&csRecording);
		return;
	}
	isRecording = false;
	LeaveCriticalSection(&csRecording);
	WaitForSingleObject(hRecordingThread, INFINITE);
	CloseHandle(hRecordingThread);
	hRecordingThread = NULL;

	// 释放VideoWriter资源
	cv::VideoWriter* writer = static_cast<cv::VideoWriter*>(videoWriter);
	if (writer) {
		writer->release();
		delete writer;
		videoWriter = nullptr;
	}
}

//------------------------------------------------------------------
//
// 函数名: RecordingThread()
// 描述: 录制线程函数，负责不断捕捉屏幕区域并写入视频文件
// 输入: 指向OpencvUtil对象的指针
// 输出: 线程退出码
//------------------------------------------------------------------
DWORD WINAPI OpencvUtil::RecordingThread(LPVOID lpParam) {
	OpencvUtil* pThis = static_cast<OpencvUtil*>(lpParam);
	const RECT& rect = pThis->captureRect;
	// 计算录制区域的宽度和高度
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	HDC hScreenDC = GetDC(NULL);
	HDC hMemDC = CreateCompatibleDC(hScreenDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
	HGDIOBJ hOld = SelectObject(hMemDC, hBitmap);
	BITMAPINFOHEADER bi = { 0 };
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = -height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;

	cv::Mat frame(height, width, CV_8UC4);
	// 用于存储转换后的BGR格式帧
	cv::Mat bgrFrame;

	// 高精度计时器
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	const double targetFrameTime = 1.0 / 30.0;

	int frameCount = 0;
	DWORD startTime = GetTickCount();
	while (true) {
		EnterCriticalSection(&pThis->csRecording);
		bool recording = pThis->isRecording;
		LeaveCriticalSection(&pThis->csRecording);

		// 如果停止录制，则退出循环
		if (!recording) break;

		QueryPerformanceCounter(&start);

		BitBlt(hMemDC, 0, 0, width, height, hScreenDC, rect.left, rect.top, SRCCOPY);
		GetDIBits(hMemDC, hBitmap, 0, height, frame.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
		// 将BGRA格式转换为BGR格式
		cv::cvtColor(frame, bgrFrame, cv::COLOR_BGRA2BGR);
		cv::VideoWriter* writer = static_cast<cv::VideoWriter*>(pThis->videoWriter);
		*writer << bgrFrame;
		frameCount++;
	
		if (GetTickCount() - startTime >= 1000) {
			//OutputDebugStringA(("实际FPS: " + std::to_string(frameCount)).c_str());
			frameCount = 0;
			startTime = GetTickCount();
		}

		// 记录结束时间
		QueryPerformanceCounter(&end);
		double elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / freq.QuadPart;
		double remainingTime = targetFrameTime - elapsed;
		// 控制帧率
		if (remainingTime > 0) {
			Sleep(static_cast<DWORD>(remainingTime * 1000));
		}

	}

	SelectObject(hMemDC, hOld);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(NULL, hScreenDC);

	return 0;
}
