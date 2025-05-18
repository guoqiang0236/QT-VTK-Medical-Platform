// This file implements the functionality of the DcmCStoreSender class, including sending DICOM files and initializing the SCU.

#include "pch.h"
#include "DcmCStoreSender.h"
#include <dcmtk/dcmnet/scu.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmnet/dicom.h>

DcmCStoreSender::DcmCStoreSender()
    : m_peerPort(104) 
{
	m_pScu = NULL;
	m_imageData = DicomImageData();
}

DcmCStoreSender::~DcmCStoreSender()
{
	if (m_pScu != NULL)
	{
		m_pScu->releaseAssociation();
		delete m_pScu;
	}
}

void DcmCStoreSender::initSCU()
{
	if (m_pScu == NULL)
	{
		m_pScu = new DcmSCU();

		m_pScu->setAETitle(m_aeTitle.c_str());
		m_pScu->setPeerHostName(m_peerHostName.c_str());
		m_pScu->setPeerPort(m_peerPort);
		m_pScu->setPeerAETitle(m_peerAETitle.c_str());

		OFList<OFString> transferSyntaxes;
		transferSyntaxes.push_back(UID_LittleEndianExplicitTransferSyntax);
		transferSyntaxes.push_back(UID_LittleEndianImplicitTransferSyntax);
	    m_pScu->addPresentationContext(UID_UltrasoundImageStorage, transferSyntaxes);
	}
}

void DcmCStoreSender::setAETitle(const std::string& aeTitle)
{
    m_aeTitle = aeTitle;
}

void DcmCStoreSender::setPeerHostName(const std::string& hostName)
{
    m_peerHostName = hostName;
}

void DcmCStoreSender::setPeerPort(unsigned short port)
{
    m_peerPort = port;
}

void DcmCStoreSender::setPeerAETitle(const std::string& peerAETitle)
{
    m_peerAETitle = peerAETitle;
}

void DcmCStoreSender::setFilePath(const std::string& filePath)
{
    m_filePath = filePath;
}

bool DcmCStoreSender::send()
{
    DcmSCU scu;
    scu.setAETitle(m_aeTitle.c_str());
    scu.setPeerHostName(m_peerHostName.c_str());
    scu.setPeerPort(m_peerPort);
    scu.setPeerAETitle(m_peerAETitle.c_str());

    OFList<OFString> transferSyntaxes;
    transferSyntaxes.push_back(UID_LittleEndianExplicitTransferSyntax);
    transferSyntaxes.push_back(UID_LittleEndianImplicitTransferSyntax);
    scu.addPresentationContext(UID_UltrasoundImageStorage, transferSyntaxes);

    OFCondition status = scu.initNetwork();
    if (!status.good())
    {
        std::cerr << "Failed to initialize network: " << status.text() << std::endl;
        return false;
    }

    status = scu.negotiateAssociation();
    if (!status.good())
    {
        std::cerr << "Failed to negotiate association: " << status.text() << std::endl;
        return false;
    }

    T_ASC_PresentationContextID presID = scu.findPresentationContextID(UID_UltrasoundImageStorage, UID_LittleEndianExplicitTransferSyntax);
    if (presID == 0)
    {
        std::cerr << "No valid presentation context for C-STORE" << std::endl;
        scu.releaseAssociation();
        return false;
    }

    DcmFileFormat file;
    status = file.loadFile(m_filePath.c_str());
    if (!status.good())
    {
        std::cerr << "Failed to load DICOM file: " << status.text() << std::endl;
        scu.releaseAssociation();
        return false;
    }

    DcmDataset* dataset = file.getDataset();
    OFString patientName;

    DcmDataset* statusDetail = NULL;
    Uint16 rspStatusCode = 0;
    status = scu.sendSTORERequest(
        presID,
        OFFilename(m_filePath.c_str()),
        statusDetail,
        rspStatusCode
    );
    if (!status.good())
    {
        scu.releaseAssociation();
        return false;
    }

    scu.releaseAssociation();
    return true;
}

bool DcmCStoreSender::senddataset()
{
	if (m_pScu == NULL)
	{
		initSCU();
	}
	if (m_imageData.pixelData.size() == 0)
		return false;

	DcmFileFormat fileFormat;
	DcmDataset* dataset = fileFormat.getDataset();
	char uid[128];

	dataset->putAndInsertString(DCM_PatientName, m_imageData.patientName.c_str());
	dataset->putAndInsertString(DCM_PatientID, m_imageData.patientID.c_str());
	dataset->putAndInsertString(DCM_SOPInstanceUID, dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT));
	dataset->putAndInsertString(DCM_SOPClassUID, UID_SecondaryCaptureImageStorage);

	dataset->putAndInsertUint16(DCM_Rows, m_imageData.rows);
	dataset->putAndInsertUint16(DCM_Columns, m_imageData.cols);
	dataset->putAndInsertUint16(DCM_BitsAllocated, 8);
	dataset->putAndInsertUint16(DCM_BitsStored, 8);
	dataset->putAndInsertUint16(DCM_HighBit, 7);
	dataset->putAndInsertUint16(DCM_PixelRepresentation, 0);
	dataset->putAndInsertUint16(DCM_SamplesPerPixel, m_imageData.channels);
	
	dataset->putAndInsertString(DCM_PhotometricInterpretation, "RGB");
	dataset->putAndInsertUint16(DCM_PlanarConfiguration, 0);
	dataset->putAndInsertUint8Array(DCM_PixelData, m_imageData.pixelData.data(), m_imageData.total * m_imageData.channels);

	OFCondition status;	
	if (!m_pScu->isConnected())
	{
		status = m_pScu->initNetwork();
		if (!status.good())
		{
			std::cerr << "Failed to initialize network: " << status.text() << std::endl;
			return false;
		}

		status = m_pScu->negotiateAssociation();
		if (!status.good())
		{
			std::cerr << "Failed to negotiate association: " << status.text() << std::endl;
			return false;
		}
	}

	T_ASC_PresentationContextID presID = m_pScu->findPresentationContextID(UID_UltrasoundImageStorage, UID_LittleEndianExplicitTransferSyntax);
	if (presID == 0)
	{
		std::cerr << "No valid presentation context for C-STORE" << std::endl;
		m_pScu->releaseAssociation();
		return false;
	}

	Uint16 rspStatusCode = 0;
	status = m_pScu->sendSTORERequest(
		presID,
		NULL,
		dataset,
		rspStatusCode
	);
	if (!status.good())
	{
		m_pScu->abortAssociation();
		m_pScu->releaseAssociation();
		return false;
	}

	return true;
}

void DcmCStoreSender::setimageData(const DicomImageData& imageData) {
	m_imageData = imageData;
}