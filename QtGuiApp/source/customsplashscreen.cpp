#include "customsplashscreen.h"

#include <QPixmap>
#include <QThread>
#include <QDateTime>
#include <QApplication>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QFile>
#define DELAYTIME 1000 // DELAYTIME为需要延时的毫秒数
#define SHOWNO  3 // 显示加载次数

CustomSplashScreen::CustomSplashScreen(QWidget* parent)
{
   
    // 设置像素图
    QString strScreen = ":/res/picture/loading.jpg";
    QPixmap loadingPix(strScreen);
    setPixmap(loadingPix.scaled(1920, 1080));
   

    //字体大小
    QFont font = this->font();
    font.setPixelSize(23);
    setFont(font);
    // 进度条
    m_pProgressBar = new QProgressBar(this);
    m_pProgressBar->setRange(0 ,100);
    m_pProgressBar->setValue(0);
    m_pProgressBar->setStyleSheet("QProgressBar{color:#ff0000;}");

    QLabel* pLabel = new QLabel("加载中...");
    pLabel->setStyleSheet("QLabel {color:#ff0000;  font-weight: bold;  font-style: italic;  font-size: 23px;}");
    QHBoxLayout* pHB = new QHBoxLayout();
    pHB->addStretch();
    pHB->addWidget(pLabel);
    pHB->addStretch();

    QVBoxLayout* pVB = new QVBoxLayout(this);
    pVB->addStretch();
    pVB->addLayout(pHB);
    pVB->addWidget(m_pProgressBar);

    this->setLayout(pVB);
}

void CustomSplashScreen::init()
{
    // 先设置显示，再设置显示信息，如果设置完显示信息再设置显示，会看不到
    show();

    // 设置鼠标指针不转圈
    QApplication::setOverrideCursor(Qt::ArrowCursor);

    // 显示信息，及文本对齐方式：右上， 字体:red
    showMessage("程序正在加载...", Qt::AlignTop|Qt::AlignRight, Qt::red);
    QDateTime time = QDateTime::currentDateTime();
    QDateTime currentTime = QDateTime::currentDateTime(); // 记录当前时间
    m_pProgressBar->setValue(0);
    int nInter = time.msecsTo(currentTime);
    while(nInter <= DELAYTIME)
    {
        currentTime = QDateTime::currentDateTime();
        m_pProgressBar->setValue(0.025*nInter);
        nInter = time.msecsTo(currentTime);
    }

    for(int i = 0; i < SHOWNO; ++i)
    {
        showMessage(QString("请稍等%1...").arg(SHOWNO-i), Qt::AlignTop|Qt::AlignRight, Qt::red);
        time = currentTime;
        nInter = time.msecsTo(currentTime);
        while(nInter <= DELAYTIME)
        {
            currentTime = QDateTime::currentDateTime();
            m_pProgressBar->setValue(25*(i+1) + 0.025*nInter);
            nInter = time.msecsTo(currentTime);
        }
    }
    m_pProgressBar->setValue(100);
}

