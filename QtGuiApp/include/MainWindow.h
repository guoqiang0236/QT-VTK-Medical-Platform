#ifndef MED_IMG_MAINWINDOW_H
#define MED_IMG_MAINWINDOW_H
#include "pch.h"
#include "DcmCStoreSender.h"
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
    void numcounttaskstarted(); // 任务开始信号

private:
    void InitSlots();
    void UpdateGUI();
    void UpdateSize();
    void loadStyleSheet(const QString& path); // 动态加载 QSS
    void InitThread();
   
	
private:
    std::mutex m_mutex; // 互斥锁
    std::unique_ptr<Ui::MainWindow_UI> m_ui; // 主窗口UI界面指针
    MyThread* m_thread; // QThread子类指针
    MyThread_Work* m_thread_work; // 工作线程对象指针
    MyThread_Runnable* m_thread_runnable; // 线程池任务对象指针
    QTimer* m_current_time; // 定时器指针
    QThread* m_sub; // 子线程指针
    QThread* m_numsub; // 子线程指针2
    std::unique_ptr<MyProgressDialog> m_progressDialog; // 进度对话框指针，用于显示耗时操作的进度提示

    //VtkUtil
    std::unique_ptr<VisualizationManager> m_VisualManager;
    //DcmtkUtil
	DcmCStoreSender m_dcmCStoreSender;
    //OpenCVUtil
    std::unique_ptr<OpencvUtil> m_opencvUtil;
};

#endif // MED_IMG_MAINWINDOW_H