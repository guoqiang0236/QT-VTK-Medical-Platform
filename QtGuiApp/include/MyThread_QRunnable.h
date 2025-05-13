#ifndef MYTHREAD_RUNNABLE_H
#define MYTHREAD_RUNNABLE_H

#include <QObject>
#include <QRunnable>
#include <functional>
#include <atomic>

class MyThread_Runnable : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit MyThread_Runnable(QObject* parent = nullptr);

    ~MyThread_Runnable();

    void run() override;
signals:
    void taskFinished(); // 任务完成信号
    void numberGenerated(int num); // 信号：发送生成的数字


private:
    std::function<void()> m_task; // 存储任务的函数对象
    std::atomic<bool> m_running{ true }; // 标志变量，线程安全
    static std::atomic<int> activeThreadCount; // 活动线程计数器

};

#endif // MYTHREAD_RUNNABLE_H

