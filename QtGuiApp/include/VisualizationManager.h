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

public slots:
    void loadFile(const QString& filePath);
    void loadDicomSeries(const QString& dirPath);
    void loadVolumeData(const QString& dirPath);
    void changeViewOrientation(int orientation);

private:
    void initializeResources();
    void cleanupCurrentViewer();
    int m_orientation;
    std::unique_ptr<VtkFileTypeDetector> m_fileDetector;
    std::unique_ptr<DicomViewer2D> m_dicom2DViewer;
    std::unique_ptr<DicomViewer3D> m_dicom3DViewer;
    QVTKOpenGLNativeWidget* m_vtkWidget;
    vtkRenderer* m_mainRenderer;
};