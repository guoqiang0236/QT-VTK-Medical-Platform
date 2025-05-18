// VisualizationManager.h
#pragma once
#include "pch.h"
#include "VtkUtil_Export.h"  // 导出宏头文件
#include "Viewer2D.h"
#include "Viewer3D.h"
#include "VtkFileTypeDetector.h"


class VTKUTIL_API VisualizationManager : public QObject {
    Q_OBJECT
public:
    explicit VisualizationManager(QObject* parent = nullptr);
    ~VisualizationManager();

    QVTKOpenGLNativeWidget* getVTKWidget() const;
    QVTKOpenGLNativeWidget* getVTKWidget_Axial() const;
    QVTKOpenGLNativeWidget* getVTKWidget_Coronal() const;
    QVTKOpenGLNativeWidget* getVTKWidget_Sagittal() const;
	Viewer2D* getDicom2DViewer_axial() const;
	Viewer2D* getDicom2DViewer_coronal() const;
	Viewer2D* getDicom2DViewer_sagittal() const;
	int getm_axial_sliceall() const { return m_axial_sliceall; }
	int getm_coronal_sliceall() const { return m_coronal_sliceall; }
	int getm_sagittal_sliceall() const { return m_sagittal_sliceall; }
    void setAxialSlice(int slice);
	void setCoronalSlice(int slice);
	void setSagittalSlice(int slice);
    QString getDirPath() { return dir_path; }
	QString getRawDataPath() { return rawdata_path; }
	void setFlieType(VtkFileType fileType) { m_fileType = fileType; }
	VtkFileType getFlieType() { return m_fileType; }
	void setm_bcompanyrawdata(bool bcompanyrawdata) { m_bcompanyrawdata = bcompanyrawdata; }
public:
    void changeViewOrientation(int orientation);
    void loadFile(const QString& filePath);
    void loadFiles(const QString& filePath);
    void loadRawData(const QString& filePath);
    void loadCompanyRawData(const QString& filePath);
    void loadDicomSingleFile(const QString& filePath);
    void loadDicomSeries(const QString& dirPath);
    void DataToSurFace(const QString& dirPath);
    void DataToVolume(const QString& dirPath);
    void initxyzSlots();
    void VolumeDicomSeries(const QString& dirPath);
    void VolumeRawData(const QString& dirPath);
    void SurFaceDicomSeries(const QString& dirPath);
    void SurFaceRawData(const QString& dirPath);

signals: 
    void loadDicomFileFinish();
	void loadDicomSeriesFinish();
    void sliceChanged(int slice);
    void progressChanged(int value, int max); // 当前进度，最大值

private:
    void initializeResources();
    void cleanupCurrentViewer();
	void cleanupMainViewer();
    int m_orientation;
    std::unique_ptr<VtkFileTypeDetector> m_fileDetector;
    std::unique_ptr<Viewer2D> m_dicom2DViewer;
    std::unique_ptr<Viewer2D> m_dicom2DViewer_axial;
    std::unique_ptr<Viewer2D> m_dicom2DViewer_coronal;
    std::unique_ptr<Viewer2D> m_dicom2DViewer_sagittal;
    std::unique_ptr<Viewer3D> m_dicom3DViewer;
    QVTKOpenGLNativeWidget* m_vtkWidget;
    QVTKOpenGLNativeWidget* m_vtkWidget_axial;
    QVTKOpenGLNativeWidget* m_vtkWidget_coronal;
    QVTKOpenGLNativeWidget* m_vtkWidget_sagittal;
    int m_axial_sliceall;
	int m_coronal_sliceall;
	int m_sagittal_sliceall;
    vtkRenderer* m_mainRenderer;
    QString dir_path;
    QString rawdata_path;
    VtkFileType m_fileType;
    bool m_bcompanyrawdata;
};