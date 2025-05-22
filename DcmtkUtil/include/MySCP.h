#pragma once
#include "DcmtkUtil_Export.h"
#include <Qobject>
#include <dcmtk/ofstd/ofstdinc.h>
#include <dcmtk/dcmnet/scp.h>
#include <dcmtk/dcmnet/diutil.h>
#include <dcmtk/dcmdata/dctk.h>
#include <opencv2/opencv.hpp>
class DcmtkUtil_API MySCP :public QObject,public DcmSCP
{
	Q_OBJECT
public:
	MySCP();
	~MySCP();

	int startSCP();
	void stopSCP();

	virtual OFCondition handleIncomingCommand(T_DIMSE_Message* incomingMsg, const DcmPresentationContextInfo& presInfo);

};

