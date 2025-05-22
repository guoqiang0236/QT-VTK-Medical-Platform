#ifndef MED_IMG_MAINWINDOW_H
#define MED_IMG_MAINWINDOW_H
#include "pch.h"
#include "DcmCStoreSender.h"
#include "MyOpenCVDialog.h"
#include "OpenCVUtil.h"
class QVTKOpenGLNativeWidget;
class vtkRenderer;
class VisualizationManager;
namespace Ui {
    class MainWindow_UI;
}
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void ReadFile();
    void ReadFiles();
    void DataTo3DVolume();
    void DataTo3DSurface();
    void ReadRawFile();
    void StyleChanged(const QString& style);
    void ViewChange(const QString& viewport);
    void LoadDicomFinished();
    void LoadDicomsFinished();
    void SetCurrentSliderEnable(bool enable);
    void SetCurrentAXIALSliderValue(int slice);
	void SetCurrentCORONALSliderValue(int slice);
	void SetCurrentSAGITTALSliderValue(int slice);
    void ShutDown();
    void OnAnimationFinished();
    void Change_CurrentTime();
    void ControlRecording();
	void ProgressChanged(int value, int max); // 进度条更新

signals:

private:
    void InitSlots();
    void UpdateGUI();
    void UpdateSize();
    void loadStyleSheet(const QString& path); // 动态加载 QSS
    void InitThread();

   
	
private:
    std::mutex m_mutex; // 互斥锁
    std::unique_ptr<Ui::MainWindow_UI> m_ui; 
    MyThread* m_thread; 
    MyThread_Work* m_thread_work; 
    MyThread_Runnable* m_thread_runnable; 
    QTimer* m_current_time; 
    QThread* m_sub;
    QThread* m_numsub; 
    std::unique_ptr<MyProgressDialog> m_progressDialog; // 进度对话框指针

    //VtkUtil
    std::unique_ptr<VisualizationManager> m_VisualManager;
    //DcmtkUtil
	DcmCStoreSender m_dcmCStoreSender;
    //OpenCVUtil
    std::unique_ptr<OpencvUtil> m_opencvUtil;
    std::unique_ptr<MyOpenCVDialog> m_opencvDialog; // OpenCV对话框指针
    
};

#endif // MED_IMG_MAINWINDOW_H