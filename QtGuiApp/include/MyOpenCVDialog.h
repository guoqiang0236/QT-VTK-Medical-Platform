#pragma once

#include "pch.h"
#include <QDialog>
#include "OpenCVTest_UI.h" // 这是由 .ui 文件生成的头文件
#include "OpenCVImageUtil.h"
#include "MyThread_DCMTK_SCP_Work.h"

class MyOpenCVDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MyOpenCVDialog(QWidget* parent = nullptr);
    ~MyOpenCVDialog();
private:
    void InitSlots();
    void UpdateGUI();
    void UpdateSize();
signals:
   
private slots:
	void on_pushButton_openimage_clicked(); 
    void StartOrStop_SCU();
	
private:
    bool bthreadrun = false;
    std::unique_ptr<Ui::OpenCVDialog> m_ui; 

    QThread* m_thread; 
    MyThread_DCMTK_SCP_Work* m_thread_scpwork;
    
	std::unique_ptr<OpenCVImageUtil> m_opencvImageUtil; // OpenCV图像处理类指针
};
