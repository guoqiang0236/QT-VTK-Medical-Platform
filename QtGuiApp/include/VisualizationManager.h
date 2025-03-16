// VisualizationManager.h
#pragma once
#include <QObject>
#include <string>
#include <memory>
#include "VtkFileTypeDetector.h"
#include "DicomViewer2D.h"
#include "DicomViewer3D.h"
#include <QVTKOpenGLNativeWidget.h>

class VisualizationManager : public QObject {
    Q_OBJECT
public:
    explicit VisualizationManager(QObject* parent = nullptr);
    ~VisualizationManager();

    QVTKOpenGLNativeWidget* getVTKWidget() const;
    QVTKOpenGLNativeWidget* getVTKWidget_Axial() const;
    QVTKOpenGLNativeWidget* getVTKWidget_Coronal() const;
    QVTKOpenGLNativeWidget* getVTKWidget_Sagittal() const;
	DicomViewer2D* getDicom2DViewer_axial() const;
	DicomViewer2D* getDicom2DViewer_coronal() const;
	DicomViewer2D* getDicom2DViewer_sagittal() const;
	int getm_axial_sliceall() const { return m_axial_sliceall; }
	int getm_coronal_sliceall() const { return m_coronal_sliceall; }
	int getm_sagittal_sliceall() const { return m_sagittal_sliceall; }
    void setAxialSlice(int slice);
	void setCoronalSlice(int slice);
	void setSagittalSlice(int slice);
    QString getDirPath() { return dir_path; }
signals:
	void loadDicomSeriesFinish();
    void sliceChanged(int slice);
public slots:
    void loadFile(const QString& filePath);
    void loadDicomSeries(const QString& dirPath);
    void loadVolumeData(const QString& dirPath);
    void loadDataVolume(const QString& dirPath);
    void loadDataSurFace(const QString& dirPath);
    void changeViewOrientation(int orientation);
    void initxyzSlots();
private:
    void initializeResources();
    void cleanupCurrentViewer();
	void cleanupMainViewer();
    int m_orientation;
    std::unique_ptr<VtkFileTypeDetector> m_fileDetector;
    std::unique_ptr<DicomViewer2D> m_dicom2DViewer;
    std::unique_ptr<DicomViewer2D> m_dicom2DViewer_axial;
    std::unique_ptr<DicomViewer2D> m_dicom2DViewer_coronal;
    std::unique_ptr<DicomViewer2D> m_dicom2DViewer_sagittal;
    std::unique_ptr<DicomViewer3D> m_dicom3DViewer;
    QVTKOpenGLNativeWidget* m_vtkWidget;
    QVTKOpenGLNativeWidget* m_vtkWidget_axial;
    QVTKOpenGLNativeWidget* m_vtkWidget_coronal;
    QVTKOpenGLNativeWidget* m_vtkWidget_sagittal;
    int m_axial_sliceall;
	int m_coronal_sliceall;
	int m_sagittal_sliceall;
    vtkRenderer* m_mainRenderer;
    QString dir_path;
};