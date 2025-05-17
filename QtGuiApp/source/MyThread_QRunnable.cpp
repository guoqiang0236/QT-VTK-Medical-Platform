#include "MyThread_QRunnable.h"
#include <QThread>
#include <QDebug>

MyThread_Runnable::MyThread_Runnable(QObject* parent)
{
    
    // 任务执行完毕,该对象自动销毁
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

    qDebug() << "run() 执行完毕, 子线程退出...";
}
