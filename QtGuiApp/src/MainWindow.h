#ifndef MED_IMG_MAINWINDOW_H
#define MED_IMG_MAINWINDOW_H

#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <MainWindow-MEDQT.h>
#include <QFile>
#include <FileManager.h>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    
    void test();
private slots:
    void ReadDicomFile();
    void ReadDicomFiles();
    void StyleChanged(const QString &style);
    void ShutDown();
private:
    void initsolt();
    void UpdateGUI();
    void loadStyleSheet(const QString& path); // ∂ØÃ¨º”‘ÿ QSS
private:
    std::unique_ptr<FileManager> m_filemanager;
    Ui::MainWindow_UI ui;
    
};

#endif // MED_IMG_MAINWINDOW_H