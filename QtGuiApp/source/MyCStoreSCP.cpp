#include "MyCStoreSCP.h"

void MyCStoreSCP::start()
{
	qDebug() << "Starting DICOM C-STORE SCP...";
    m_datasetPtr = std::make_shared<DcmDataset>();
    this->listen();
}

DcmDataset* MyCStoreSCP::getDataset()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_datasetPtr.get();
}

OFCondition MyCStoreSCP::handleIncomingCommand(T_DIMSE_Message* incomingMsg,
                                               const DcmPresentationContextInfo& presInfo)
{
    if (incomingMsg->CommandField == DIMSE_C_STORE_RQ)
    {

        T_DIMSE_C_StoreRQ* storeReq = &incomingMsg->msg.CStoreRQ;
        DcmDataset* dataset = nullptr;
        T_ASC_PresentationContextID presentationContextID = presInfo.presentationContextID;

        // 直接用 receiveSTORERequest 获取 dataset
        OFCondition status = receiveSTORERequest(*storeReq, presentationContextID, dataset);

        if (status.good() && dataset)
        {
            auto datasetPtr = std::shared_ptr<DcmDataset>(dataset);
            emit dicomReceived(datasetPtr); // 直接通过信号发送数据集指针
            m_datasetPtr = datasetPtr;
          
        }
        else
        {
            std::cerr << "Failed to receive DICOM dataset: " << status.text() << std::endl;
            //if (dataset) delete dataset;
        }
        return sendSTOREResponse(presInfo.presentationContextID, storeReq->MessageID,
            storeReq->AffectedSOPClassUID, storeReq->AffectedSOPInstanceUID,
            STATUS_Success, nullptr);
    }

    return DcmSCP::handleIncomingCommand(incomingMsg, presInfo);
}
