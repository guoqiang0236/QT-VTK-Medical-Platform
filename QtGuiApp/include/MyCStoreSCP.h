#pragma once
#include <QObject>
#include <dcmtk/dcmnet/scp.h>
#include <dcmtk/dcmdata/dctk.h>
#include <iostream>

class MyCStoreSCP : public QObject, public DcmSCP
{
    Q_OBJECT
public:
    using DcmSCP::DcmSCP; // 继承 DcmSCP 构造函数

    // 启动监听
    void start();
    DcmDataset* getDataset() { return m_datasetPtr.get(); }
signals:
    void dicomReceived();

protected:
    OFCondition handleIncomingCommand(T_DIMSE_Message* incomingMsg,
        const DcmPresentationContextInfo& presInfo) override;
private:
	std::shared_ptr<DcmDataset> m_datasetPtr;
};