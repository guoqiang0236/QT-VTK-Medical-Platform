#include "MyThread_DCMTK_SCP_Work.h"
#include <QThread>
#include <QDebug>
MyThread_DCMTK_SCP_Work::MyThread_DCMTK_SCP_Work(QObject* parent)
{

}

MyThread_DCMTK_SCP_Work::~MyThread_DCMTK_SCP_Work()
{
}

void MyThread_DCMTK_SCP_Work::StopWorking()
{
    qDebug() << "请求停止 DICOM SCP 监听...";
    m_scp.stopSCP();
}

void MyThread_DCMTK_SCP_Work::Working()
{
    qDebug() << "准备启动 DICOM SCP 监听...";

    // 启动监听
    int result = m_scp.startSCP();
    if (result != 0) {
        qDebug() << "SCP 启动失败，错误码:" << result;
        return;
    }

    qDebug() << "SCP 已启动，进入监听循环...";
}
