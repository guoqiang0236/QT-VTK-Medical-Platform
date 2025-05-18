// DcmCStoreSender.h
#ifndef DCM_CSTORE_SENDER_H
#define DCM_CSTORE_SENDER_H

#include "pch.h"
#include "DcmtkUtil_Export.h"
#include <dcmtk/dcmnet/scu.h>
#include <dcmtk/dcmdata/dctk.h>



struct DcmtkUtil_API DicomImageData {
    std::string patientName = "";
    std::string patientID = "";
    std::vector<unsigned char> pixelData;
    unsigned int rows = 0;
    unsigned int cols = 0;
    unsigned int channels = 0;
    unsigned int total = 0;
};

class DcmtkUtil_API DcmCStoreSender :public QObject 
{
    Q_OBJECT
public:
    DcmCStoreSender();
    ~DcmCStoreSender();

    void initSCU();
    void setAETitle(const std::string& aeTitle);
    void setPeerHostName(const std::string& hostName);
    void setPeerPort(unsigned short port);
    void setPeerAETitle(const std::string& peerAETitle);
    void setFilePath(const std::string& filePath);
    bool send();
    bool senddataset();
    void setimageData(const DicomImageData& imageData);

private:
    DcmSCU* m_pScu;
    std::string m_aeTitle;
    std::string m_peerHostName;
    unsigned short m_peerPort;
    std::string m_peerAETitle;
    std::string m_filePath;
    DicomImageData m_imageData;
};

#endif // DCM_CSTORE_SENDER_H