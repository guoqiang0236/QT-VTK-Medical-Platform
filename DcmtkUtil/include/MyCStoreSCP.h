#pragma once
#include "pch.h"
#include "DcmtkUtil_Export.h"

#include <dcmtk/dcmnet/scp.h>
#include <dcmtk/dcmdata/dctk.h>

class DcmtkUtil_API MyCStoreSCP : public QObject, public DcmSCP
{
    Q_OBJECT
public:
    using DcmSCP::DcmSCP; // 继承 DcmSCP 构造函数

    // 启动监听
    void start();
    DcmDataset* getDataset();
signals:
    //void dicomReceived();
    void dicomReceived(std::shared_ptr<DcmDataset> dataset);

protected:
    OFCondition handleIncomingCommand(T_DIMSE_Message* incomingMsg,
        const DcmPresentationContextInfo& presInfo) override;
private:
	std::shared_ptr<DcmDataset> m_datasetPtr;
    std::mutex m_mutex;
};