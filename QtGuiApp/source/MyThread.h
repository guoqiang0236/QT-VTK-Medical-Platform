#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <functional>
#include <atomic>

class MyThread : public QThread
{
    Q_OBJECT

public:
    explicit MyThread(QObject* parent = nullptr);
    ~MyThread();

    static int getActiveThreadCount(); // 获取当前活动线程数
    // 设置任务
    void setTask(const std::function<void()>& task);
    void stopthread(); // 停止线程
signals:
    void taskFinished(); // 任务完成信号
    void numberGenerated(int num); // 信号：发送生成的数字

protected:
    void run() override;

private:
    std::function<void()> m_task; // 存储任务的函数对象
    std::atomic<bool> m_running{ true }; // 标志变量，线程安全
    static std::atomic<int> activeThreadCount; // 活动线程计数器
};

#endif // MYTHREAD_H
