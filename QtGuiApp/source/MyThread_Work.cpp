#include "MyThread_work.h"
#include <QThread>
#include <QDebug>
MyThread_Work::MyThread_Work(QObject* parent)
{
}

MyThread_Work::~MyThread_Work()
{
}

void MyThread_Work::working()
{
    int count = 0;
    while (m_running) {
        emit numberGenerated(count);
        count++;
        QThread::usleep(10);
    }

    qDebug() << "run() 执行完毕, 子线程退出...";
}
