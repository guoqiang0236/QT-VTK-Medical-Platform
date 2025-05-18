#pragma once

#include "pch.h"
#include <QDialog>
#include "OpenCVTest_UI.h" // 这是由 .ui 文件生成的头文件

class MyOpenCVDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MyOpenCVDialog(QWidget* parent = nullptr);

private:
    void InitSlots();
    void UpdateGUI();
    void UpdateSize();
private:
    std::unique_ptr<Ui::OpenCVDialog> m_ui; // 主窗口UI界面指针
};
