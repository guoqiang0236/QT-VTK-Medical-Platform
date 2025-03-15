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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton;
    QPushButton *pushButton_6;
    QPushButton *pushButton_12;
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

    void setupUi(QMainWindow *MainWindow_UI)
    {
        if (MainWindow_UI->objectName().isEmpty())
            MainWindow_UI->setObjectName("MainWindow_UI");
        MainWindow_UI->resize(1600, 900);
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
        label = new QLabel(tab_3);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(tab_3);
        lineEdit->setObjectName("lineEdit");

        verticalLayout_2->addWidget(lineEdit);

        label_2 = new QLabel(tab_3);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label_2);

        lineEdit_2 = new QLineEdit(tab_3);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        verticalLayout_2->addWidget(lineEdit_2);

        label_3 = new QLabel(tab_3);
        label_3->setObjectName("label_3");
        label_3->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label_3);

        lineEdit_3 = new QLineEdit(tab_3);
        lineEdit_3->setObjectName("lineEdit_3");

        verticalLayout_2->addWidget(lineEdit_3);

        label_4 = new QLabel(tab_3);
        label_4->setObjectName("label_4");
        label_4->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label_4);

        lineEdit_4 = new QLineEdit(tab_3);
        lineEdit_4->setObjectName("lineEdit_4");

        verticalLayout_2->addWidget(lineEdit_4);

        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName("pushButton");
        pushButton->setMaximumSize(QSize(120, 16777215));
        pushButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(pushButton);

        pushButton_6 = new QPushButton(tab_3);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setMaximumSize(QSize(120, 16777215));
        pushButton_6->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(pushButton_6);

        pushButton_12 = new QPushButton(tab_3);
        pushButton_12->setObjectName("pushButton_12");

        verticalLayout_2->addWidget(pushButton_12);

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
        frame_vtkrender->setFrameShape(QFrame::Shape::StyledPanel);
        frame_vtkrender->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_vtkrender);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);

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
        label->setText(QCoreApplication::translate("MainWindow_UI", "\345\247\223\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow_UI", "\345\207\272\347\224\237\346\227\245\346\234\237", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow_UI", "\347\224\265\350\257\235", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow_UI", "\345\234\260\345\235\200", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow_UI", "\346\211\223\345\274\200DICOM\346\226\207\344\273\266", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow_UI", "\346\211\223\345\274\200DICOM\346\226\207\344\273\266\345\244\271", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow_UI", "\344\275\223\347\273\230\345\210\266\357\274\214\351\230\210\345\200\274\345\267\262\347\273\217\345\206\231\346\255\273", nullptr));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow_UI: public Ui_MainWindow_UI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_2D_MEDQT_H
