/********************************************************************************
** Form generated from reading UI file 'MainWindow-MEDQT.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_2D_MEDQT_H
#define MAINWINDOW_2D_MEDQT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qvtkopenglnativewidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow_UI
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_menu;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_openfile;
    QPushButton *pushButton_rawcompany;
    QPushButton *pushButton_opendicoms;
    QPushButton *pushButton_ti;
    QPushButton *pushButton_mian;
    QComboBox *comboBox_2;
    QFrame *frame;
    QWidget *tab_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_shutdown;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QWidget *tab;
    QComboBox *comboBox;
    QLabel *label_5;
    QFrame *frame_vtkrender;
    QHBoxLayout *horizontalLayout_2;
    QVTKOpenGLNativeWidget *openGLWidget;
    QFrame *frame_XYZ;
    QFrame *frame_AXIAL;
    QOpenGLWidget *openGLWidget_AXIAL;
    QSlider *Slider_AXIAL;
    QLabel *label_AXIALMIN;
    QLabel *label_AXIAL_2;
    QLabel *label_AXIALMAX;
    QFrame *frame_CORONAL;
    QOpenGLWidget *openGLWidget_CORONAL;
    QSlider *Slider_CORONAL;
    QLabel *label_CORONAL;
    QLabel *label_CORONALMIN;
    QLabel *label_CORONALMAX;
    QFrame *frame_SAGITTAL;
    QOpenGLWidget *openGLWidget_SAGITTAL;
    QSlider *Slider_SAGITTAL;
    QLabel *label_SAGITTAL;
    QLabel *label_SAGITTALMIN;
    QLabel *label_SAGITTALMAX;

    void setupUi(QMainWindow *MainWindow_UI)
    {
        if (MainWindow_UI->objectName().isEmpty())
            MainWindow_UI->setObjectName("MainWindow_UI");
        MainWindow_UI->resize(1920, 1080);
        centralwidget = new QWidget(MainWindow_UI);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_menu = new QFrame(centralwidget);
        frame_menu->setObjectName("frame_menu");
        frame_menu->setMaximumSize(QSize(208, 16777215));
        frame_menu->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: transparent; /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    border: none;                /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));
        frame_menu->setFrameShape(QFrame::Shape::StyledPanel);
        frame_menu->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(frame_menu);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(frame_menu);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setAutoFillBackground(true);
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        verticalLayout_2 = new QVBoxLayout(tab_3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 0, -1, -1);
        pushButton_openfile = new QPushButton(tab_3);
        pushButton_openfile->setObjectName("pushButton_openfile");
        pushButton_openfile->setMaximumSize(QSize(16777215, 16777215));
        pushButton_openfile->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(pushButton_openfile);

        pushButton_rawcompany = new QPushButton(tab_3);
        pushButton_rawcompany->setObjectName("pushButton_rawcompany");

        verticalLayout_2->addWidget(pushButton_rawcompany);

        pushButton_opendicoms = new QPushButton(tab_3);
        pushButton_opendicoms->setObjectName("pushButton_opendicoms");
        pushButton_opendicoms->setMaximumSize(QSize(16777215, 16777215));
        pushButton_opendicoms->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(pushButton_opendicoms);

        pushButton_ti = new QPushButton(tab_3);
        pushButton_ti->setObjectName("pushButton_ti");

        verticalLayout_2->addWidget(pushButton_ti);

        pushButton_mian = new QPushButton(tab_3);
        pushButton_mian->setObjectName("pushButton_mian");

        verticalLayout_2->addWidget(pushButton_mian);

        comboBox_2 = new QComboBox(tab_3);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");

        verticalLayout_2->addWidget(comboBox_2);

        frame = new QFrame(tab_3);
        frame->setObjectName("frame");
        frame->setEnabled(false);
        frame->setMaximumSize(QSize(16777215, 200));
        frame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: transparent; /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    border: none;                /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_2->addWidget(frame);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        pushButton_2 = new QPushButton(tab_4);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(1, 1, 100, 100));
        pushButton_2->setMinimumSize(QSize(100, 100));
        pushButton_2->setMaximumSize(QSize(100, 100));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::AddressBookNew));
        pushButton_2->setIcon(icon);
        pushButton_2->setIconSize(QSize(100, 100));
        pushButton_3 = new QPushButton(tab_4);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(107, 1, 100, 100));
        pushButton_3->setMinimumSize(QSize(100, 100));
        pushButton_3->setMaximumSize(QSize(100, 100));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::EditUndo));
        pushButton_3->setIcon(icon1);
        pushButton_3->setIconSize(QSize(100, 100));
        pushButton_4 = new QPushButton(tab_4);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(107, 107, 100, 100));
        pushButton_4->setMinimumSize(QSize(100, 100));
        pushButton_4->setMaximumSize(QSize(100, 100));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::UserAvailable));
        pushButton_4->setIcon(icon2);
        pushButton_4->setIconSize(QSize(100, 100));
        pushButton_5 = new QPushButton(tab_4);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(1, 107, 100, 100));
        pushButton_5->setMinimumSize(QSize(100, 100));
        pushButton_5->setMaximumSize(QSize(100, 100));
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::AudioVolumeHigh));
        pushButton_5->setIcon(icon3);
        pushButton_5->setIconSize(QSize(100, 100));
        pushButton_shutdown = new QPushButton(tab_4);
        pushButton_shutdown->setObjectName("pushButton_shutdown");
        pushButton_shutdown->setGeometry(QRect(107, 213, 100, 100));
        pushButton_shutdown->setMinimumSize(QSize(100, 100));
        pushButton_shutdown->setMaximumSize(QSize(100, 100));
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::SystemShutdown));
        pushButton_shutdown->setIcon(icon4);
        pushButton_shutdown->setIconSize(QSize(100, 100));
        pushButton_7 = new QPushButton(tab_4);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(1, 213, 100, 100));
        pushButton_7->setMinimumSize(QSize(100, 100));
        pushButton_7->setMaximumSize(QSize(100, 100));
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause));
        pushButton_7->setIcon(icon5);
        pushButton_7->setIconSize(QSize(100, 100));
        pushButton_8 = new QPushButton(tab_4);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(107, 319, 100, 100));
        pushButton_8->setMinimumSize(QSize(100, 100));
        pushButton_8->setMaximumSize(QSize(100, 100));
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStop));
        pushButton_8->setIcon(icon6);
        pushButton_8->setIconSize(QSize(100, 100));
        pushButton_9 = new QPushButton(tab_4);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(1, 319, 100, 100));
        pushButton_9->setMinimumSize(QSize(100, 100));
        pushButton_9->setMaximumSize(QSize(100, 100));
        QIcon icon7(QIcon::fromTheme(QIcon::ThemeIcon::GoNext));
        pushButton_9->setIcon(icon7);
        pushButton_9->setIconSize(QSize(100, 100));
        pushButton_10 = new QPushButton(tab_4);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(107, 425, 100, 100));
        pushButton_10->setMinimumSize(QSize(100, 100));
        pushButton_10->setMaximumSize(QSize(100, 100));
        QIcon icon8(QIcon::fromTheme(QIcon::ThemeIcon::WeatherClear));
        pushButton_10->setIcon(icon8);
        pushButton_10->setIconSize(QSize(100, 100));
        pushButton_11 = new QPushButton(tab_4);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(1, 425, 100, 100));
        pushButton_11->setMinimumSize(QSize(100, 100));
        pushButton_11->setMaximumSize(QSize(100, 100));
        QIcon icon9(QIcon::fromTheme(QIcon::ThemeIcon::CameraPhoto));
        pushButton_11->setIcon(icon9);
        pushButton_11->setIconSize(QSize(100, 100));
        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        comboBox = new QComboBox(tab);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(70, 20, 111, 24));
        label_5 = new QLabel(tab);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(3, 20, 61, 21));
        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);


        horizontalLayout_3->addWidget(frame_menu);

        frame_vtkrender = new QFrame(centralwidget);
        frame_vtkrender->setObjectName("frame_vtkrender");
        frame_vtkrender->setMinimumSize(QSize(0, 0));
        frame_vtkrender->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: transparent; /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    border: none;                /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));
        frame_vtkrender->setFrameShape(QFrame::Shape::StyledPanel);
        frame_vtkrender->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_vtkrender);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        openGLWidget = new QVTKOpenGLNativeWidget(frame_vtkrender);
        openGLWidget->setObjectName("openGLWidget");

        horizontalLayout_2->addWidget(openGLWidget);

        frame_XYZ = new QFrame(frame_vtkrender);
        frame_XYZ->setObjectName("frame_XYZ");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_XYZ->sizePolicy().hasHeightForWidth());
        frame_XYZ->setSizePolicy(sizePolicy);
        frame_XYZ->setMinimumSize(QSize(500, 0));
        frame_XYZ->setMaximumSize(QSize(500, 16777215));
        frame_XYZ->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: transparent; /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    border: none;                /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));
        frame_XYZ->setFrameShape(QFrame::Shape::StyledPanel);
        frame_XYZ->setFrameShadow(QFrame::Shadow::Raised);
        frame_AXIAL = new QFrame(frame_XYZ);
        frame_AXIAL->setObjectName("frame_AXIAL");
        frame_AXIAL->setGeometry(QRect(50, 10, 450, 350));
        frame_AXIAL->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: transparent; /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    border: none;                /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));
        frame_AXIAL->setFrameShape(QFrame::Shape::StyledPanel);
        frame_AXIAL->setFrameShadow(QFrame::Shadow::Raised);
        openGLWidget_AXIAL = new QOpenGLWidget(frame_AXIAL);
        openGLWidget_AXIAL->setObjectName("openGLWidget_AXIAL");
        openGLWidget_AXIAL->setGeometry(QRect(90, 0, 300, 300));
        Slider_AXIAL = new QSlider(frame_AXIAL);
        Slider_AXIAL->setObjectName("Slider_AXIAL");
        Slider_AXIAL->setGeometry(QRect(90, 320, 301, 16));
        Slider_AXIAL->setOrientation(Qt::Orientation::Horizontal);
        label_AXIALMIN = new QLabel(frame_AXIAL);
        label_AXIALMIN->setObjectName("label_AXIALMIN");
        label_AXIALMIN->setGeometry(QRect(20, 0, 54, 16));
        label_AXIAL_2 = new QLabel(frame_AXIAL);
        label_AXIAL_2->setObjectName("label_AXIAL_2");
        label_AXIAL_2->setGeometry(QRect(60, 320, 21, 16));
        label_AXIALMAX = new QLabel(frame_AXIAL);
        label_AXIALMAX->setObjectName("label_AXIALMAX");
        label_AXIALMAX->setGeometry(QRect(400, 320, 54, 16));
        frame_CORONAL = new QFrame(frame_XYZ);
        frame_CORONAL->setObjectName("frame_CORONAL");
        frame_CORONAL->setGeometry(QRect(50, 370, 450, 350));
        frame_CORONAL->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: transparent; /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    border: none;                /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));
        frame_CORONAL->setFrameShape(QFrame::Shape::StyledPanel);
        frame_CORONAL->setFrameShadow(QFrame::Shadow::Raised);
        openGLWidget_CORONAL = new QOpenGLWidget(frame_CORONAL);
        openGLWidget_CORONAL->setObjectName("openGLWidget_CORONAL");
        openGLWidget_CORONAL->setGeometry(QRect(90, 0, 300, 300));
        Slider_CORONAL = new QSlider(frame_CORONAL);
        Slider_CORONAL->setObjectName("Slider_CORONAL");
        Slider_CORONAL->setGeometry(QRect(90, 320, 301, 16));
        Slider_CORONAL->setOrientation(Qt::Orientation::Horizontal);
        label_CORONAL = new QLabel(frame_CORONAL);
        label_CORONAL->setObjectName("label_CORONAL");
        label_CORONAL->setGeometry(QRect(20, 0, 54, 16));
        label_CORONALMIN = new QLabel(frame_CORONAL);
        label_CORONALMIN->setObjectName("label_CORONALMIN");
        label_CORONALMIN->setGeometry(QRect(60, 320, 21, 16));
        label_CORONALMAX = new QLabel(frame_CORONAL);
        label_CORONALMAX->setObjectName("label_CORONALMAX");
        label_CORONALMAX->setGeometry(QRect(400, 320, 31, 16));
        frame_SAGITTAL = new QFrame(frame_XYZ);
        frame_SAGITTAL->setObjectName("frame_SAGITTAL");
        frame_SAGITTAL->setGeometry(QRect(50, 730, 450, 350));
        frame_SAGITTAL->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: transparent; /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    border: none;                /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));
        frame_SAGITTAL->setFrameShape(QFrame::Shape::StyledPanel);
        frame_SAGITTAL->setFrameShadow(QFrame::Shadow::Raised);
        openGLWidget_SAGITTAL = new QOpenGLWidget(frame_SAGITTAL);
        openGLWidget_SAGITTAL->setObjectName("openGLWidget_SAGITTAL");
        openGLWidget_SAGITTAL->setGeometry(QRect(90, 0, 300, 300));
        Slider_SAGITTAL = new QSlider(frame_SAGITTAL);
        Slider_SAGITTAL->setObjectName("Slider_SAGITTAL");
        Slider_SAGITTAL->setGeometry(QRect(90, 320, 301, 16));
        Slider_SAGITTAL->setOrientation(Qt::Orientation::Horizontal);
        label_SAGITTAL = new QLabel(frame_SAGITTAL);
        label_SAGITTAL->setObjectName("label_SAGITTAL");
        label_SAGITTAL->setGeometry(QRect(20, 0, 54, 16));
        label_SAGITTALMIN = new QLabel(frame_SAGITTAL);
        label_SAGITTALMIN->setObjectName("label_SAGITTALMIN");
        label_SAGITTALMIN->setGeometry(QRect(60, 320, 21, 16));
        label_SAGITTALMAX = new QLabel(frame_SAGITTAL);
        label_SAGITTALMAX->setObjectName("label_SAGITTALMAX");
        label_SAGITTALMAX->setGeometry(QRect(400, 320, 31, 16));

        horizontalLayout_2->addWidget(frame_XYZ);


        horizontalLayout_3->addWidget(frame_vtkrender);

        MainWindow_UI->setCentralWidget(centralwidget);
#if QT_CONFIG(shortcut)
        label_5->setBuddy(comboBox);
#endif // QT_CONFIG(shortcut)

        retranslateUi(MainWindow_UI);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow_UI);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_UI)
    {
        MainWindow_UI->setWindowTitle(QCoreApplication::translate("MainWindow_UI", "MainWindow", nullptr));
        pushButton_openfile->setText(QCoreApplication::translate("MainWindow_UI", "\346\211\223\345\274\200\346\226\207\344\273\266(.raw/.dicom)", nullptr));
        pushButton_rawcompany->setText(QCoreApplication::translate("MainWindow_UI", "\346\211\223\345\274\200\345\205\254\345\217\270raw\346\226\207\344\273\266", nullptr));
        pushButton_opendicoms->setText(QCoreApplication::translate("MainWindow_UI", "\346\211\223\345\274\200DICOM\346\226\207\344\273\266\345\244\271", nullptr));
        pushButton_ti->setText(QCoreApplication::translate("MainWindow_UI", "\344\275\223\347\273\230\345\210\266", nullptr));
        pushButton_mian->setText(QCoreApplication::translate("MainWindow_UI", "\351\235\242\347\273\230\345\210\266", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow_UI", "\346\250\252\346\226\255\351\235\242", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow_UI", "\345\206\240\347\212\266\351\235\242", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow_UI", "\347\237\242\347\212\266\351\235\242", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow_UI", "\346\202\243\350\200\205\344\277\241\346\201\257", nullptr));
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_shutdown->setText(QString());
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
        pushButton_9->setText(QString());
        pushButton_10->setText(QString());
        pushButton_11->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow_UI", "\345\233\276\345\203\217\345\244\204\347\220\206", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow_UI", "ElegantDark", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow_UI", "AMOLED", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow_UI", "Aqua", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow_UI", "ConsoleStyle", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow_UI", "MacOS", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("MainWindow_UI", "ManjaroMix", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("MainWindow_UI", "MaterialDark", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("MainWindow_UI", "NeonButtons", nullptr));
        comboBox->setItemText(8, QCoreApplication::translate("MainWindow_UI", "Ubuntu", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow_UI", "\344\270\273\351\242\230", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow_UI", "\347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        label_AXIALMIN->setText(QCoreApplication::translate("MainWindow_UI", "\346\250\252\346\226\255\351\235\242", nullptr));
        label_AXIAL_2->setText(QCoreApplication::translate("MainWindow_UI", "0", nullptr));
        label_AXIALMAX->setText(QCoreApplication::translate("MainWindow_UI", "100", nullptr));
        label_CORONAL->setText(QCoreApplication::translate("MainWindow_UI", "\345\206\240\347\212\266\351\235\242", nullptr));
        label_CORONALMIN->setText(QCoreApplication::translate("MainWindow_UI", "0", nullptr));
        label_CORONALMAX->setText(QCoreApplication::translate("MainWindow_UI", "100", nullptr));
        label_SAGITTAL->setText(QCoreApplication::translate("MainWindow_UI", "\347\237\242\347\212\266\351\235\242", nullptr));
        label_SAGITTALMIN->setText(QCoreApplication::translate("MainWindow_UI", "0", nullptr));
        label_SAGITTALMAX->setText(QCoreApplication::translate("MainWindow_UI", "100", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_UI: public Ui_MainWindow_UI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_2D_MEDQT_H
