#include "MyThread_QRunnable.h"
#include <QThread>
#include <QDebug>

MyThread_Runnable::MyThread_Runnable(QObject* parent)
{
    
    // ����ִ�����,�ö����Զ�����
    setAutoDelete(true);
   
}

MyThread_Runnable::~MyThread_Runnable()
{
}

void MyThread_Runnable::run()
{
    int count = 0;
    while (m_running) {
        emit numberGenerated(count);
        count++;
        QThread::usleep(100);
    }

    qDebug() << "run() ִ�����, ���߳��˳�...";
}
