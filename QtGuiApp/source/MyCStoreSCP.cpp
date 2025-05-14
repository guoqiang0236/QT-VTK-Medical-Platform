#include "MyCStoreSCP.h"

void MyCStoreSCP::start()
{
	qDebug() << "Starting DICOM C-STORE SCP...";
    m_datasetPtr = std::make_shared<DcmDataset>();
    this->listen();
}

OFCondition MyCStoreSCP::handleIncomingCommand(T_DIMSE_Message* incomingMsg,
                                               const DcmPresentationContextInfo& presInfo)
{
    if (incomingMsg->CommandField == DIMSE_C_STORE_RQ)
    {
        /*T_DIMSE_C_StoreRQ* storeReq = &incomingMsg->msg.CStoreRQ;
        std::cout << "Received C-STORE request for SOP Instance: " << storeReq->AffectedSOPInstanceUID << std::endl;

        OFString outputFilename = "D:/receivefolder/received_" + OFString(storeReq->AffectedSOPInstanceUID) + ".dcm";
        DcmDataset* dataset = nullptr;
        T_ASC_PresentationContextID presentationContextID = presInfo.presentationContextID;

        OFCondition status = receiveSTORERequestDataset(&presentationContextID, *storeReq, outputFilename);
        if (status.good() && dataset)
        {
            status = dataset->saveFile(outputFilename.c_str(), EXS_LittleEndianExplicit);
            if (status.good())
            {
                std::cout << "DICOM file saved as: " << outputFilename << std::endl;
               
            }
            else
            {
                std::cerr << "Failed to save DICOM file: " << status.text() << std::endl;
            }
            delete dataset;
        }
        else
        {
            std::cerr << "Failed to receive DICOM dataset: " << status.text() << std::endl;
        }
        emit dicomReceived(outputFilename.c_str());
        return sendSTOREResponse(presInfo.presentationContextID, storeReq->MessageID,
                                 storeReq->AffectedSOPClassUID, storeReq->AffectedSOPInstanceUID,
                                 STATUS_Success, nullptr);*/

        T_DIMSE_C_StoreRQ* storeReq = &incomingMsg->msg.CStoreRQ;
        DcmDataset* dataset = nullptr;
        T_ASC_PresentationContextID presentationContextID = presInfo.presentationContextID;

        // 直接用 receiveSTORERequest 获取 dataset
        OFCondition status = receiveSTORERequest(*storeReq, presentationContextID, dataset);

        if (status.good() && dataset)
        {
            m_datasetPtr = std::shared_ptr<DcmDataset>(dataset);
            emit dicomReceived(); // 直接通过信号发送数据集指针
            // 注意：接收方负责释放 dataset
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
