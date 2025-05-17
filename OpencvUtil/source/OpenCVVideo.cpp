/*****************************************************************************
 *                                                                           *
 *      COPYRIGHT  2025  -  PULSEVISION TECHNOLOGIES SHANGHAI CO. LTD                 *
 *                                                                           *
 *                                                                           *
 * This is the confidential proprietary property of PulseVision Technologies *
 * Shanghai Co. Ltd., of Room 703, Building 3 No. 99 Haiji Six Road Lin Gang *
 * New City Shanghai China. Absolutely no use, dissemination or copying in   *
 * any media of any portion of this material is to be made without the prior *
 * written authorisation of PulseVision Technologies Shanghai China.                 *
 * All rights reserved.  In the event of publication, statutory copyright    *
 * protection is hereby claimed.                                                                                         *
 *                                                                           *
 * Copyright 2025, PulseVision Technologies Shanghai Co. Ltd                 *
 *                                                                           *
 ****************************************************************************/
 //
 // PROGRAM : OpenCVVideo.cpp : Opencv video service class
 //
 // HISTORY :
 //
 //    Date     Author    Description
 // ------------------------------------------------------------------------
 // 12/03/2025  郭强                  实现视频捕捉和播放
 //
 //***************************************************************************

#include "pch.h"
#include "OpenCVVideo.h"
#include <opencv2/opencv.hpp>
#include <filesystem>

//------------------------------------------------------------------
//
// 函数名: COpencvVideo()
// 描述: COpencvVideo类的构造函数，初始化成员变量
// 输入: 无
// 输出: 无
//------------------------------------------------------------------
COpencvVideo::COpencvVideo()
	: m_bPlaying(false), m_bPaused(false), m_hWnd(nullptr),
	hPlayingThread(NULL), m_pVideoCapture(nullptr),
	m_totalFrames(0), m_currentFrame(0), m_hwndNotify(NULL),
	m_videoPath(""), m_bInSlider(false), m_oribPaused(false)
{
	ZeroMemory(&m_bmpInfo, sizeof(m_bmpInfo));
	InitializeCriticalSection(&csPlaying);
}

//------------------------------------------------------------------
//
// 函数名: ~COpencvVideo()
// 描述: COpencvVideo类的析构函数，停止视频播放并释放资源
// 输入: 无
// 输出: 无
//------------------------------------------------------------------

COpencvVideo::~COpencvVideo()
{
	StopVideo();
	DeleteCriticalSection(&csPlaying);
}

//------------------------------------------------------------------
//
// 函数名: OpenVideo()
// 描述: 打开指定路径的视频文件，获取视频参数
// 输入: 视频文件的路径
// 输出: 打开成功返回true，失败返回false
//------------------------------------------------------------------
bool COpencvVideo::OpenVideo(const char* path)
{
	cv::VideoCapture* capture = new cv::VideoCapture(path);

	if (!capture->isOpened()) {
		delete capture;
		return false;
	}
	EnterCriticalSection(&csPlaying);
	m_videoPath = path;
	LeaveCriticalSection(&csPlaying);
	// 获取视频参数
	int w = static_cast<int>(capture->get(cv::CAP_PROP_FRAME_WIDTH));
	int h = static_cast<int>(capture->get(cv::CAP_PROP_FRAME_HEIGHT));
	double fps = capture->get(cv::CAP_PROP_FPS);
	m_totalFrames = static_cast<long>(capture->get(cv::CAP_PROP_FRAME_COUNT));

	// 备用方式获取总帧数（某些格式可能不支持）
	if (m_totalFrames <= 0) {
		double duration = capture->get(cv::CAP_PROP_POS_MSEC);
		if (duration > 0 && fps > 0) {
			m_totalFrames = static_cast<long>(duration * fps / 1000);
		}
	}

	// 验证尺寸有效性
	if (w <= 0 || h <= 0) {
		delete capture;
		return false;
	}

	m_pVideoCapture = capture;
	return true;
}

//------------------------------------------------------------------
//
// 函数名: UpdateRECT()
// 描述: 更新视频显示的矩形区域，使视频居中显示
// 输入: 要更新的矩形区域
// 输出: 更新成功返回true，失败返回false
//------------------------------------------------------------------
bool COpencvVideo::UpdateRECT(RECT rect)
{
	// 居中显示计算
	m_rect = rect;
	cv::VideoCapture* capture = static_cast<cv::VideoCapture*>(m_pVideoCapture);
	if (!capture)
		return false;
	int w = static_cast<int>(capture->get(cv::CAP_PROP_FRAME_WIDTH));
	int h = static_cast<int>(capture->get(cv::CAP_PROP_FRAME_HEIGHT));
	int w0 = m_rect.right - m_rect.left;
	int h0 = m_rect.bottom - m_rect.top;
	m_rect.left += (w0 - w) / 2;
	m_rect.right = m_rect.left + w;
	m_rect.top += (h0 - h) / 2;
	m_rect.bottom = m_rect.top + h;
	return true;
}

//------------------------------------------------------------------
//
// 函数名: PlayVideo()
// 描述: 播放视频
// 输入: 播放窗口句柄
// 输出: 是否成功标志
//------------------------------------------------------------------

bool COpencvVideo::PlayVideo(void* hWnd)
{
	if (!m_pVideoCapture) return false;

	EnterCriticalSection(&csPlaying);
	if (m_bPlaying) {
		LeaveCriticalSection(&csPlaying);
		StopVideo();
		EnterCriticalSection(&csPlaying);
	}

	m_hWnd = static_cast<HWND>(hWnd);
	if (!m_hWnd) {
		LeaveCriticalSection(&csPlaying);
		return false;
	}

	m_bPlaying = true;
	m_bPaused = false;
	m_oribPaused = m_bPaused;
	LeaveCriticalSection(&csPlaying);

	hPlayingThread = CreateThread(
		NULL, 0, PlayingThread, this, 0, NULL
	);

	return hPlayingThread != NULL;
}

//------------------------------------------------------------------
//
// 函数名: StopVideo()
// 描述: 停止视频播放，释放相关资源
// 输入: 无
// 输出: 无
//------------------------------------------------------------------
void COpencvVideo::StopVideo()
{
	EnterCriticalSection(&csPlaying);
	// 清空窗口内容
	if (m_hWnd) {
		HDC hDC = GetDC(m_hWnd);
		if (hDC) {
			RECT rc;
			GetClientRect(m_hWnd, &rc);
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
			FillRect(hDC, &rc, hBrush);
			DeleteObject(hBrush);
			ReleaseDC(m_hWnd, hDC);
		}
		// 刷新窗口，确保清空显示
		InvalidateRect(m_hWnd, NULL, TRUE);
		UpdateWindow(m_hWnd);
	}
	if (m_bPlaying) {
		m_bPlaying = false;
		m_bPaused = false;
		LeaveCriticalSection(&csPlaying);

		// 等待线程安全退出
		WaitForSingleObject(hPlayingThread, INFINITE);
		CloseHandle(hPlayingThread);
		hPlayingThread = NULL;
	}
	else {
		LeaveCriticalSection(&csPlaying);
	}
	
	// 显式释放VideoCapture资源
	if (m_pVideoCapture) 
	{
		static_cast<cv::VideoCapture*>(m_pVideoCapture)->release();
		delete static_cast<cv::VideoCapture*>(m_pVideoCapture);
		m_pVideoCapture = nullptr;
	}
}

//------------------------------------------------------------------
//
// 函数名: PauseVideo()
// 描述: 暂停视频播放
// 输入: 无
// 输出: 无
//------------------------------------------------------------------
void COpencvVideo::PauseVideo()
{
	EnterCriticalSection(&csPlaying);
	if (m_bPlaying && !m_bPaused) {
		m_bPaused = true;
		m_oribPaused = m_bPaused;
	}
	LeaveCriticalSection(&csPlaying);
}

//------------------------------------------------------------------
//
// 函数名: ResumeVideo()
// 描述: 恢复视频播放
// 输入: 无
// 输出: 无
//------------------------------------------------------------------
void COpencvVideo::ResumeVideo()
{
	EnterCriticalSection(&csPlaying);
	if (m_bPlaying && m_bPaused) {
		m_bPaused = false;
		m_oribPaused = m_bPaused;
	}
	m_bInSlider = false;
	LeaveCriticalSection(&csPlaying);
}

//------------------------------------------------------------------
//
// 函数名: IsPlaying()
// 描述: 判断视频是否正在播放
// 输入: 无
// 输出: 正在播放返回true，否则返回false
//------------------------------------------------------------------
bool COpencvVideo::IsPlaying() const
{
	EnterCriticalSection(&csPlaying);
	bool ret = m_bPlaying;
	LeaveCriticalSection(&csPlaying);
	return ret;
}

//------------------------------------------------------------------
//
// 函数名: IsPaused()
// 描述: 判断视频是否处于暂停状态
// 输入: 无
// 输出: 处于暂停状态返回true，否则返回false
//------------------------------------------------------------------
bool COpencvVideo::IsPaused() const
{
	EnterCriticalSection(&csPlaying);
	bool ret = m_bPaused;
	LeaveCriticalSection(&csPlaying);
	return ret;
}

//------------------------------------------------------------------
//
// 函数名: SetNotifyWindow()
// 描述: 设置用于接收视频播放进度通知的窗口句柄
// 输入: 窗口句柄
// 输出: 无
//------------------------------------------------------------------
void COpencvVideo::SetNotifyWindow(HWND hWnd)
{
	EnterCriticalSection(&csPlaying);
	m_hwndNotify = hWnd;
	//做进度条用
	if (m_hwndNotify)
	{
		
	}
	LeaveCriticalSection(&csPlaying);
}

//------------------------------------------------------------------
//
// 函数名: GetTotalFrames()
// 描述: 获取视频的总帧数
// 输入: 无
// 输出: 视频的总帧数
//------------------------------------------------------------------
long COpencvVideo::GetTotalFrames() const
{
	EnterCriticalSection(&csPlaying);
	long ret = m_totalFrames;
	LeaveCriticalSection(&csPlaying);
	return ret;
}

//------------------------------------------------------------------
//
// 函数名: GetCurrentFrame()
// 描述: 获取视频当前播放的帧数
// 输入: 无
// 输出: 视频当前播放的帧数
//------------------------------------------------------------------
long COpencvVideo::GetCurrentFrame() const
{
	EnterCriticalSection(&csPlaying);
	long ret = m_currentFrame;
	LeaveCriticalSection(&csPlaying);
	return ret;
}

//------------------------------------------------------------------
//
// 函数名: SeekToPosition()
// 描述: 将视频定位到指定的播放位置
// 输入: 播放位置，范围为0到1.0
// 输出: 定位成功返回true，失败返回false
//------------------------------------------------------------------
bool COpencvVideo::SeekToPosition(double pos)
{
	if (!m_pVideoCapture || pos < 0 || pos > 1.0)
		return false;
	cv::VideoCapture* capture = static_cast<cv::VideoCapture*>(m_pVideoCapture);
	bool wasPlaying = false;
	bool wasPaused = false;

	EnterCriticalSection(&csPlaying);
	wasPlaying = m_bPlaying;
	wasPaused = m_bPaused;

	if (wasPlaying && !wasPaused) {
		m_bPaused = true; // 暂停确保定位准确
	}
	LeaveCriticalSection(&csPlaying);

	// 计算目标帧
	long targetFrame = static_cast<long>(pos * m_totalFrames);
	Sleep(20);
	bool success = capture->set(cv::CAP_PROP_POS_FRAMES, targetFrame);

	EnterCriticalSection(&csPlaying);
	if (success) {
		m_currentFrame = targetFrame;
	}
	LeaveCriticalSection(&csPlaying);

	// 如果处于暂停状态，读取并显示一帧
	if (wasPaused) {
		cv::Mat frame;
		*capture >> frame;
		if (!frame.empty()) {
			HDC hDC = GetDC(m_hWnd);
			if (hDC) {
				RECT rc;
				GetClientRect(m_hWnd, &rc);
				//对齐4字节否则视频播放出问题
				int w = rc.right - rc.left;
				int h = rc.bottom - rc.top;
				float ratio = (float)h / (float)w;

				int imgW = (int)(w / 4 * 4);
				int imgH = (int)(imgW * ratio);
				cv::Mat newFrame;
				cv::resize(frame, newFrame, cv::Size(imgW, imgH), 0, 0, cv::INTER_CUBIC);

				EnterCriticalSection(&csPlaying);
				BITMAPINFOHEADER& bmiHeader = m_bmpInfo.bmiHeader;
				bmiHeader.biWidth = imgW;
				bmiHeader.biHeight = -imgH;
				bmiHeader.biSizeImage = frame.cols * frame.rows * 3;
				LeaveCriticalSection(&csPlaying);

				SetStretchBltMode(hDC, COLORONCOLOR);
				StretchDIBits(
					hDC,
					0, 0, rc.right, rc.bottom,
					0, 0, newFrame.cols, newFrame.rows,
					newFrame.data,
					&m_bmpInfo,
					DIB_RGB_COLORS,
					SRCCOPY
				);
				ReleaseDC(m_hWnd, hDC);
			}
		}
	}

	return success;
}


//------------------------------------------------------------------
//
// 函数名: GetMyRect()
// 描述: 获取视频显示的矩形区域
// 输入: 无
// 输出: 视频显示的矩形区域
//------------------------------------------------------------------
RECT COpencvVideo::GetMyRect()
{
	return m_rect;
}

void OPENCVUTIL_API COpencvVideo::SetbInSlider(bool flag)
{
	m_bInSlider = flag;
}

void OPENCVUTIL_API COpencvVideo::SetbPaused(bool flag)
{
	m_bPaused = flag;
}

void OPENCVUTIL_API COpencvVideo::SetOribPaused(bool flag)
{
	m_oribPaused = flag;
}

void OPENCVUTIL_API COpencvVideo::RefuseOribPaused()
{
	m_bPaused = m_oribPaused;
}

//------------------------------------------------------------------
//
// 函数名: PlayingThread()
// 描述: 视频播放的线程函数，负责读取视频帧并显示
// 输入: 指向COpencvVideo对象的指针
// 输出: 线程退出码
//------------------------------------------------------------------
DWORD WINAPI COpencvVideo::PlayingThread(LPVOID lpParam)
{
	COpencvVideo* pThis = static_cast<COpencvVideo*>(lpParam);
	cv::VideoCapture* capture = static_cast<cv::VideoCapture*>(pThis->m_pVideoCapture);

	// 获取视频参数
	double fps = capture->get(cv::CAP_PROP_FPS);
	int delay = fps > 0 ? static_cast<int>(1000 / fps) : 33;

	// 初始化BITMAPINFO
	BITMAPINFOHEADER& bmiHeader = pThis->m_bmpInfo.bmiHeader;
	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiHeader.biPlanes = 1;
	bmiHeader.biBitCount = 24;
	bmiHeader.biCompression = BI_RGB;

	DWORD lastNotifyTime = 0;
	const DWORD notifyInterval = 100; // 进度更新间隔100ms

	while (true) {
		EnterCriticalSection(&pThis->csPlaying);
		bool bContinue = pThis->m_bPlaying;
		bool bPaused = pThis->m_bPaused;
		LeaveCriticalSection(&pThis->csPlaying);

		if (!bContinue) break;

		if (bPaused) {
			Sleep(10);
			continue;
		}

		// 检查视频文件是否存在
		if (!std::filesystem::exists(pThis->m_videoPath)) {
			pThis->StopVideo();
			break;   
		}

		cv::Mat frame;
		*capture >> frame;

		// 检查是否播放结束
		if (frame.empty()) {
			EnterCriticalSection(&pThis->csPlaying);
			std::string videoPath = pThis->m_videoPath;
			LeaveCriticalSection(&pThis->csPlaying);

			// 释放旧资源
			if (capture) {
				capture->release();
			}
			delete pThis->m_pVideoCapture;
			pThis->m_pVideoCapture = new cv::VideoCapture(videoPath);
			capture = static_cast<cv::VideoCapture*>(pThis->m_pVideoCapture);
			*capture >> frame;
			if (!capture->isOpened()) break;
			continue; // 继续下一轮循环
		}

		// 更新当前帧
		EnterCriticalSection(&pThis->csPlaying);
		pThis->m_currentFrame = static_cast<long>(
			capture->get(cv::CAP_PROP_POS_FRAMES));
		LeaveCriticalSection(&pThis->csPlaying);

		// 发送进度通知
		DWORD currentTime = GetTickCount();
		if (currentTime - lastNotifyTime >= notifyInterval) {

			lastNotifyTime = currentTime;
		}
		// 绘制到窗口
		HDC hDC = GetDC(pThis->m_hWnd);
		if (hDC) {
			RECT rc;
			GetClientRect(pThis->m_hWnd, &rc);
			//对齐4字节否则视频播放出问题
			int w = rc.right - rc.left;
			int h = rc.bottom - rc.top;
			float ratio = (float)h / (float)w;

			int imgW = (int)(w / 4 * 4);
			int imgH = (int)(imgW * ratio);
			cv::Mat newFrame;
			cv::resize(frame, newFrame, cv::Size(imgW, imgH), 0, 0, cv::INTER_CUBIC);

			EnterCriticalSection(&pThis->csPlaying);
			bmiHeader.biWidth = imgW;
			bmiHeader.biHeight = -imgH;
			bmiHeader.biSizeImage = frame.cols * frame.rows * 3;
			LeaveCriticalSection(&pThis->csPlaying);

			SetStretchBltMode(hDC, COLORONCOLOR);
			StretchDIBits(
				hDC,
				0, 0, rc.right, rc.bottom,
				0, 0, newFrame.cols, newFrame.rows,
				newFrame.data,
				&pThis->m_bmpInfo,
				DIB_RGB_COLORS,
				SRCCOPY
			);
			ReleaseDC(pThis->m_hWnd, hDC);
		}

		Sleep(delay);
	}

	pThis->StopVideo();
	return 0;
}