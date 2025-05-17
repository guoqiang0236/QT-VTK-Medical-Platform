/*****************************************************************************
 *                                                                           *
 *      COPYRIGHT  2025  -  PULSEVISION TECHNOLOGIES SHANGHAI CO. LTD		 *
 *                                                                           *
 *                                                                           *
 * This is the confidential proprietary property of PulseVision Technologies *
 * Shanghai Co. Ltd., of Room 703, Building 3 No. 99 Haiji Six Road Lin Gang *
 * New City Shanghai China. Absolutely no use, dissemination or copying in   *
 * any media of any portion of this material is to be made without the prior *
 * written authorisation of PulseVision Technologies Shanghai China.		 *
 * All rights reserved.  In the event of publication, statutory copyright    *
 * protection is hereby claimed.											 *
 *                                                                           *
 * Copyright 2025, PulseVision Technologies Shanghai Co. Ltd                 *
 *                                                                           *
 ****************************************************************************/
 //
 // PROGRAM : OpenCVVideo.h : Opencv video service class
 //
 // HISTORY :
 //
 //    Date     Author    Description
 // ------------------------------------------------------------------------
 // 12/03/2025  ��ǿ		  ʵ����Ƶ��׽�Ͳ���
 //
 //***************************************************************************



#include "OpencvUtil_Export.h"
#include <windows.h>
#include <string>



class  COpencvVideo {
public:
	OPENCVUTIL_API COpencvVideo();
	OPENCVUTIL_API ~COpencvVideo();

	bool OPENCVUTIL_API OpenVideo(const char* path);
	bool OPENCVUTIL_API UpdateRECT(RECT rect);
	bool OPENCVUTIL_API PlayVideo(void* hWnd);
	void OPENCVUTIL_API StopVideo();
	void OPENCVUTIL_API PauseVideo();
	void OPENCVUTIL_API ResumeVideo();
	bool OPENCVUTIL_API IsPlaying() const;
	bool OPENCVUTIL_API IsPaused() const;
	void OPENCVUTIL_API SetNotifyWindow(HWND hWnd);   
	long OPENCVUTIL_API GetTotalFrames() const;      
	long OPENCVUTIL_API GetCurrentFrame() const;      
	bool OPENCVUTIL_API SeekToPosition(double pos);   
	RECT OPENCVUTIL_API GetMyRect();
	void OPENCVUTIL_API SetbInSlider(bool flag);
	void OPENCVUTIL_API SetbPaused(bool flag);
	void OPENCVUTIL_API SetOribPaused(bool flag);
	void OPENCVUTIL_API RefuseOribPaused();

private:
	bool m_bPlaying;
	bool m_bPaused;
	bool m_oribPaused;
	bool m_bInSlider;
	HWND m_hWnd;
	HWND m_hwndNotify;               
	HANDLE hPlayingThread;
	mutable CRITICAL_SECTION csPlaying;
	BITMAPINFO m_bmpInfo;
	void* m_pVideoCapture;
	RECT m_rect;
	long m_totalFrames;              
	long m_currentFrame;              
	std::string m_videoPath;
	static DWORD WINAPI PlayingThread(LPVOID lpParam);

};





