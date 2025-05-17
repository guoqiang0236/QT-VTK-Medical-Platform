#ifndef MYTHREAD_WORK_H
#define MYTHREAD_WORK_H

#include <Qobject>


class MyThread_Work : public QObject
{
    Q_OBJECT

public:
    explicit MyThread_Work(QObject* parent = nullptr);
    ~MyThread_Work();

    // 设置任务
    void working();
signals:
    void taskFinished(); // 任务完成信号
    void numberGenerated(int num); // 信号：发送生成的数字


private:
    std::function<void()> m_task; // 存储任务的函数对象
    std::atomic<bool> m_running{ true }; // 标志变量，线程安全
    static std::atomic<int> activeThreadCount; // 活动线程计数器
};


#endif // MYTHREAD_H