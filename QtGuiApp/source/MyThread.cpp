#include "MyThread.h"

std::atomic<int> MyThread::activeThreadCount{ 0 };

MyThread::MyThread(QObject* parent)
    : QThread(parent)
{
    activeThreadCount++;
}

MyThread::~MyThread()
{
    activeThreadCount--;
    // 确保线程安全退出
    if (isRunning()) {
        quit();
        wait();
    }
}

int MyThread::getActiveThreadCount()
{
    return activeThreadCount.load();
}

void MyThread::setTask(const std::function<void()>& task)
{
    m_task = task;
}

void MyThread::stopthread()
{
    m_running = false;
}



void MyThread::run()
{
    int count = 0; 
    while (m_running) {
        emit numberGenerated(count);
        count++; 
        QThread::msleep(100); // 每次循环暂停 1 秒
    }
    
}
