#ifndef CUSTOMSPLASHSCREEN_H
#define CUSTOMSPLASHSCREEN_H

#include <QSplashScreen>

// 前置声明
QT_FORWARD_DECLARE_CLASS(QProgressBar)

/**
 * @brief The CustomSplashScreen class 自定义开场动画类
 */
class CustomSplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    explicit CustomSplashScreen(QWidget *parent = nullptr);

    // 初始化
    void init();


private:
    // 进度条
    QProgressBar*       m_pProgressBar;
};

#endif // CUSTOMSPLASHSCREEN_H
