#ifndef MYTHREAD_DCMTK_SCP_WORK
#define MYTHREAD_DCMTK_SCP_WORK
#include "OpencvUtil_Export.h"
#include <QObject>
#include "MySCP.h"


class OPENCVUTIL_API MyThread_DCMTK_SCP_Work : public QObject
{
    Q_OBJECT
public:
    explicit MyThread_DCMTK_SCP_Work(QObject* parent = nullptr);
    ~MyThread_DCMTK_SCP_Work();
   
	MySCP& GetSCP() { return m_scp; } 
signals:
    void WorkFinished(); 
public slots:
    void Working();
    void StopWorking();
private:
    std::function<void()> m_task;
    std::atomic<bool> m_running{ true }; 
    static std::atomic<int> activeThreadCount; 
	MySCP m_scp; 
};


#endif // MYTHREAD_DCMTK_SCP_WORK