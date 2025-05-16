// DcmCStoreSender.h
#ifndef DCM_CSTORE_SENDER_H
#define DCM_CSTORE_SENDER_H

#include <string>
#include <dcmtk/dcmnet/scu.h>
#include <dcmtk/dcmdata/dctk.h>
#include <iostream>
#include <vector>

#ifdef _WIN32
  #ifdef DcmtkUtil_EXPORTS
    #define DcmtkUtil_API __declspec(dllexport)
  #else
    #define DcmtkUtil_API __declspec(dllimport)
  #endif
#else
  #define DcmtkUtil_API
#endif

struct DcmtkUtil_API DicomImageData {
    std::string patientName;
    std::string patientID;
    std::vector<unsigned char> pixelData;
    unsigned int rows;
    unsigned int cols;
    unsigned int channels;
    unsigned int total;
};

class DcmtkUtil_API DcmCStoreSender {
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