#include "MyOpenCVDialog.h"

MyOpenCVDialog::MyOpenCVDialog(QWidget* parent)
    : QDialog(parent),
	m_ui(std::make_unique<Ui::OpenCVDialog>())
{
    m_ui->setupUi(this); // �ؼ�������UI
}

void MyOpenCVDialog::InitSlots()
{
}

void MyOpenCVDialog::UpdateGUI()
{
}

void MyOpenCVDialog::UpdateSize()
{
    sysconfig::GlobalConfig& config = sysconfig::GlobalConfig::get();
    QSize windowsize = config.getAdjustedSize();
    this->resize(windowsize);
}
