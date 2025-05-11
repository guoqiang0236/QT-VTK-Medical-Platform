#ifndef MED_IMG_MAINWINDOW_H
#define MED_IMG_MAINWINDOW_H
#include "pch.h"
#include "MyThread.h"
#include <memory>

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


private:
    void initSlots();
    void UpdateGUI();
    void UpdateSize();
    void loadStyleSheet(const QString& path); // 动态加载 QSS
    void InitNumThread();


private:
    std::unique_ptr <Ui::MainWindow_UI> m_ui;
    std::unique_ptr <QQuickWidget> m_LoadingWidget;
    std::unique_ptr<VisualizationManager> m_VisualManager;
    MyThread* m_thread; 
	QTimer* m_current_time;
};

#endif // MED_IMG_MAINWINDOW_H