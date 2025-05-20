#pragma once

#include "pch.h"
#include <QDialog>
#include "OpenCVTest_UI.h" // 这是由 .ui 文件生成的头文件
#include "OpenCVImageUtil.h"

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
private slots:
	void on_pushButton_openimage_clicked(); // 打开图片按钮点击事件
	
private:
    std::unique_ptr<Ui::OpenCVDialog> m_ui; // 主窗口UI界面指针

    
	std::unique_ptr<OpenCVImageUtil> m_opencvImageUtil; // OpenCV图像处理类指针
};
