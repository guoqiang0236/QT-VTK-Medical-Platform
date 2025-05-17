/****************************************************************************
*      COPYRIGHT  2025 - PULSEVISION TECHNOLOGIES SHANGHAI CO.LTD           *
*																			*
*                                                                           *
* This is the confidential proprietary property of PulseVision Technologies *
* Shanghai Co.Ltd., of Room 703, Building 3 No. 99 Haiji Six Road Lin Gang	*
* New City Shanghai China.Absolutely no use, dissemination or copying in	*
* any media of any portion of this material is to be made without the prior *
* written authorisation of PulseVision Technologies Shanghai China.         *
* All rights reserved.In the event of publication, statutory copyright		*
* protection is hereby claimed.                                             *
*                                                                           *
* Copyright 2025, PulseVision Technologies Shanghai Co.Ltd					*
*                                                                           *
*************************************************************************** /
//
// PROGRAM : OpencvUtil.h : Opencv video service class
//
// HISTORY :
//
//    Date     Author    Description
// ------------------------------------------------------------------------
// 05/03/2025  郭强                  实现视频捕捉
//
//***************************************************************************/

#include "OpencvUtil_Export.h"
#include "pch.h"
#include <windows.h>
#include <string>
#include <QObject>

class OpencvUtil : public QObject
{
	Q_OBJECT
public:
	explicit OPENCVUTIL_API OpencvUtil(QObject* parent = nullptr);
	OPENCVUTIL_API ~OpencvUtil();

	void OPENCVUTIL_API StartRecording(const RECT& rect, const char*  path);
	void OPENCVUTIL_API StopRecording();
	bool OPENCVUTIL_API GetIsRecording() const { return isRecording; }

private:
	bool isRecording;
	HANDLE hRecordingThread;
	CRITICAL_SECTION csRecording; 

	void* videoWriter; 
	void* m_cap;
	RECT captureRect;
	std::string outputPath;

	static DWORD WINAPI RecordingThread(LPVOID lpParam);
};