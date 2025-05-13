#include "MyThread_Work.h"
#include <QThread>
#include <QDebug>
MyThread_work::MyThread_work(QObject* parent)
{
}

MyThread_work::~MyThread_work()
{
}

void MyThread_work::working()
{
    int count = 0;
    while (m_running) {
        emit numberGenerated(count);
        count++;
        QThread::usleep(100);
    }

    qDebug() << "run() 执行完毕, 子线程退出...";
}
