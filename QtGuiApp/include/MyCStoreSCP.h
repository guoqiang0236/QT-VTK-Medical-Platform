#pragma once
#include <QObject>
#include <dcmtk/dcmnet/scp.h>
#include <dcmtk/dcmdata/dctk.h>
#include <iostream>
#include <mutex>
class MyCStoreSCP : public QObject, public DcmSCP
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