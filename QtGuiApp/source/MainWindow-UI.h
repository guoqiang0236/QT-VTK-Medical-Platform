/********************************************************************************
** Form generated from reading UI file 'MainWindow-UI.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_2D_UI_H
#define MAINWINDOW_2D_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qvtkopenglnativewidget.h>
#include "pannellitem/imageswitch/imageswitch.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow_UI
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *frame_menu;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QGridLayout *gridLayout_7;
    QPushButton *pushButton_openfile;
    QPushButton *pushButton_opendicoms;
    QFrame *frame;
    QPushButton *pushButton_rawcompany;
    QComboBox *comboBox_2;
    QLabel *label_showthreadnum;
    QPushButton *pushButton_ti;
    QPushButton *pushButton_mian;
    QWidget *tab_4;
    QGridLayout *gridLayout_9;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_Pannel3D;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_bone_full_opacity;
    QSlider *horizontalSlider_bone_full_opacity;
    QLabel *label_bone_full_opacity;
    QGridLayout *gridLayout_cubeAxes;
    ImageSwitch *widget_object_cubeAxes;
    QLabel *label_object_cubeAxes;
    QGridLayout *gridLayout_fat_opacity;
    QLabel *label_fat_opacity;
    QSlider *horizontalSlider_fat_opacity;
    QGridLayout *gridLayout_soft_tissue_opacity;
    QLabel *label_soft_tissue_opacity;
    QSlider *horizontalSlider_soft_tissue_opacity;
    QGridLayout *gridLayout_bone_transition_opacity;
    QSlider *horizontalSlider_bone_transition_opacity;
    QLabel *label__bone_transition_opacity;
    QWidget *tab;
    QComboBox *comboBox;
    QLabel *label_5;
    QPushButton *pushButton_opencvtest;
    QFrame *frame_2;
    QPushButton *pushButton_shutdown;
    QFrame *frame_vtkrender;
    QGridLayout *gridLayout_2;
    QFrame *frame_XYZ;
    QGridLayout *gridLayout_3;
    QFrame *frame_AXIAL;
    QGridLayout *gridLayout_4;
    QLabel *label_AXIALMIN;
    QVTKOpenGLNativeWidget *openGLWidget_AXIAL;
    QLabel *label_AXIAL_2;
    QSlider *Slider_AXIAL;
    QLabel *label_AXIALMAX;
    QFrame *frame_CORONAL;
    QGridLayout *gridLayout_5;
    QLabel *label_CORONAL;
    QVTKOpenGLNativeWidget *openGLWidget_CORONAL;
    QLabel *label_CORONALMIN;
    QSlider *Slider_CORONAL;
    QLabel *label_CORONALMAX;
    QFrame *frame_SAGITTAL;
    QGridLayout *gridLayout_6;
    QLabel *label_SAGITTAL;
    QVTKOpenGLNativeWidget *openGLWidget_SAGITTAL;
    QLabel *label_SAGITTALMIN;
    QSlider *Slider_SAGITTAL;
    QLabel *label_SAGITTALMAX;
    QFrame *frame_main;
    QGridLayout *gridLayout_8;
    QVTKOpenGLNativeWidget *openGLWidget;
    QFrame *frame_3;
    QFrame *frame1;
    QHBoxLayout *horizontalLayout;
    QLabel *label_hospital;
    QLabel *label_currenttime;

    void setupUi(QMainWindow *MainWindow_UI)
    {
        if (MainWindow_UI->objectName().isEmpty())
            MainWindow_UI->setObjectName("MainWindow_UI");
        MainWindow_UI->resize(1395, 897);
        centralwidget = new QWidget(MainWindow_UI);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
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
        gridLayout_7 = new QGridLayout(tab_3);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_7->setContentsMargins(-1, 0, -1, -1);
        pushButton_openfile = new QPushButton(tab_3);
        pushButton_openfile->setObjectName("pushButton_openfile");
        pushButton_openfile->setMaximumSize(QSize(16777215, 16777215));
        pushButton_openfile->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        gridLayout_7->addWidget(pushButton_openfile, 0, 0, 1, 1);

        pushButton_opendicoms = new QPushButton(tab_3);
        pushButton_opendicoms->setObjectName("pushButton_opendicoms");
        pushButton_opendicoms->setMaximumSize(QSize(16777215, 16777215));
        pushButton_opendicoms->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        gridLayout_7->addWidget(pushButton_opendicoms, 2, 0, 1, 1);

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

        gridLayout_7->addWidget(frame, 7, 0, 1, 1);

        pushButton_rawcompany = new QPushButton(tab_3);
        pushButton_rawcompany->setObjectName("pushButton_rawcompany");

        gridLayout_7->addWidget(pushButton_rawcompany, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(tab_3);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");

        gridLayout_7->addWidget(comboBox_2, 5, 0, 1, 1);

        label_showthreadnum = new QLabel(tab_3);
        label_showthreadnum->setObjectName("label_showthreadnum");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_showthreadnum->sizePolicy().hasHeightForWidth());
        label_showthreadnum->setSizePolicy(sizePolicy);
        label_showthreadnum->setMaximumSize(QSize(200, 100));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        label_showthreadnum->setFont(font);

        gridLayout_7->addWidget(label_showthreadnum, 6, 0, 1, 1);

        pushButton_ti = new QPushButton(tab_3);
        pushButton_ti->setObjectName("pushButton_ti");

        gridLayout_7->addWidget(pushButton_ti, 3, 0, 1, 1);

        pushButton_mian = new QPushButton(tab_3);
        pushButton_mian->setObjectName("pushButton_mian");

        gridLayout_7->addWidget(pushButton_mian, 4, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        gridLayout_9 = new QGridLayout(tab_4);
        gridLayout_9->setObjectName("gridLayout_9");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_9->addItem(verticalSpacer, 1, 0, 1, 1);

        groupBox_Pannel3D = new QGroupBox(tab_4);
        groupBox_Pannel3D->setObjectName("groupBox_Pannel3D");
        groupBox_Pannel3D->setMinimumSize(QSize(0, 500));
        gridLayout_10 = new QGridLayout(groupBox_Pannel3D);
        gridLayout_10->setObjectName("gridLayout_10");
        gridLayout_bone_full_opacity = new QGridLayout();
        gridLayout_bone_full_opacity->setObjectName("gridLayout_bone_full_opacity");
        horizontalSlider_bone_full_opacity = new QSlider(groupBox_Pannel3D);
        horizontalSlider_bone_full_opacity->setObjectName("horizontalSlider_bone_full_opacity");
        horizontalSlider_bone_full_opacity->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_bone_full_opacity->addWidget(horizontalSlider_bone_full_opacity, 1, 0, 1, 1);

        label_bone_full_opacity = new QLabel(groupBox_Pannel3D);
        label_bone_full_opacity->setObjectName("label_bone_full_opacity");

        gridLayout_bone_full_opacity->addWidget(label_bone_full_opacity, 0, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_bone_full_opacity, 4, 0, 1, 1);

        gridLayout_cubeAxes = new QGridLayout();
        gridLayout_cubeAxes->setSpacing(0);
        gridLayout_cubeAxes->setObjectName("gridLayout_cubeAxes");
        gridLayout_cubeAxes->setContentsMargins(-1, 10, -1, 10);
        widget_object_cubeAxes = new ImageSwitch(groupBox_Pannel3D);
        widget_object_cubeAxes->setObjectName("widget_object_cubeAxes");
        widget_object_cubeAxes->setMinimumSize(QSize(100, 25));
        widget_object_cubeAxes->setMaximumSize(QSize(100, 25));

        gridLayout_cubeAxes->addWidget(widget_object_cubeAxes, 0, 1, 1, 1);

        label_object_cubeAxes = new QLabel(groupBox_Pannel3D);
        label_object_cubeAxes->setObjectName("label_object_cubeAxes");
        label_object_cubeAxes->setMinimumSize(QSize(50, 25));
        label_object_cubeAxes->setMaximumSize(QSize(200, 25));

        gridLayout_cubeAxes->addWidget(label_object_cubeAxes, 0, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_cubeAxes, 0, 0, 1, 1);

        gridLayout_fat_opacity = new QGridLayout();
        gridLayout_fat_opacity->setObjectName("gridLayout_fat_opacity");
        label_fat_opacity = new QLabel(groupBox_Pannel3D);
        label_fat_opacity->setObjectName("label_fat_opacity");

        gridLayout_fat_opacity->addWidget(label_fat_opacity, 0, 0, 1, 1);

        horizontalSlider_fat_opacity = new QSlider(groupBox_Pannel3D);
        horizontalSlider_fat_opacity->setObjectName("horizontalSlider_fat_opacity");
        horizontalSlider_fat_opacity->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_fat_opacity->addWidget(horizontalSlider_fat_opacity, 1, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_fat_opacity, 1, 0, 1, 1);

        gridLayout_soft_tissue_opacity = new QGridLayout();
        gridLayout_soft_tissue_opacity->setObjectName("gridLayout_soft_tissue_opacity");
        label_soft_tissue_opacity = new QLabel(groupBox_Pannel3D);
        label_soft_tissue_opacity->setObjectName("label_soft_tissue_opacity");

        gridLayout_soft_tissue_opacity->addWidget(label_soft_tissue_opacity, 0, 0, 1, 1);

        horizontalSlider_soft_tissue_opacity = new QSlider(groupBox_Pannel3D);
        horizontalSlider_soft_tissue_opacity->setObjectName("horizontalSlider_soft_tissue_opacity");
        horizontalSlider_soft_tissue_opacity->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_soft_tissue_opacity->addWidget(horizontalSlider_soft_tissue_opacity, 1, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_soft_tissue_opacity, 2, 0, 1, 1);

        gridLayout_bone_transition_opacity = new QGridLayout();
        gridLayout_bone_transition_opacity->setObjectName("gridLayout_bone_transition_opacity");
        horizontalSlider_bone_transition_opacity = new QSlider(groupBox_Pannel3D);
        horizontalSlider_bone_transition_opacity->setObjectName("horizontalSlider_bone_transition_opacity");
        horizontalSlider_bone_transition_opacity->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_bone_transition_opacity->addWidget(horizontalSlider_bone_transition_opacity, 1, 0, 1, 1);

        label__bone_transition_opacity = new QLabel(groupBox_Pannel3D);
        label__bone_transition_opacity->setObjectName("label__bone_transition_opacity");

        gridLayout_bone_transition_opacity->addWidget(label__bone_transition_opacity, 0, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_bone_transition_opacity, 3, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_Pannel3D, 0, 0, 1, 1);

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
        pushButton_opencvtest = new QPushButton(tab);
        pushButton_opencvtest->setObjectName("pushButton_opencvtest");
        pushButton_opencvtest->setGeometry(QRect(40, 100, 121, 28));
        frame_2 = new QFrame(tab);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(40, 390, 120, 80));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        pushButton_shutdown = new QPushButton(tab);
        pushButton_shutdown->setObjectName("pushButton_shutdown");
        pushButton_shutdown->setGeometry(QRect(40, 170, 121, 23));
        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout->addWidget(frame_menu, 0, 0, 1, 1);

        frame_vtkrender = new QFrame(centralwidget);
        frame_vtkrender->setObjectName("frame_vtkrender");
        frame_vtkrender->setMinimumSize(QSize(0, 0));
        frame_vtkrender->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: transparent; /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    border: none;                /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));
        frame_vtkrender->setFrameShape(QFrame::Shape::StyledPanel);
        frame_vtkrender->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_2 = new QGridLayout(frame_vtkrender);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        frame_XYZ = new QFrame(frame_vtkrender);
        frame_XYZ->setObjectName("frame_XYZ");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_XYZ->sizePolicy().hasHeightForWidth());
        frame_XYZ->setSizePolicy(sizePolicy1);
        frame_XYZ->setMinimumSize(QSize(500, 0));
        frame_XYZ->setMaximumSize(QSize(500, 16777215));
        frame_XYZ->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: transparent; /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    border: none;                /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));
        frame_XYZ->setFrameShape(QFrame::Shape::StyledPanel);
        frame_XYZ->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_3 = new QGridLayout(frame_XYZ);
        gridLayout_3->setObjectName("gridLayout_3");
        frame_AXIAL = new QFrame(frame_XYZ);
        frame_AXIAL->setObjectName("frame_AXIAL");
        frame_AXIAL->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: transparent; /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    border: none;                /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));
        frame_AXIAL->setFrameShape(QFrame::Shape::StyledPanel);
        frame_AXIAL->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_4 = new QGridLayout(frame_AXIAL);
        gridLayout_4->setObjectName("gridLayout_4");
        label_AXIALMIN = new QLabel(frame_AXIAL);
        label_AXIALMIN->setObjectName("label_AXIALMIN");
        label_AXIALMIN->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        gridLayout_4->addWidget(label_AXIALMIN, 0, 0, 1, 1);

        openGLWidget_AXIAL = new QVTKOpenGLNativeWidget(frame_AXIAL);
        openGLWidget_AXIAL->setObjectName("openGLWidget_AXIAL");
        openGLWidget_AXIAL->setMinimumSize(QSize(100, 100));

        gridLayout_4->addWidget(openGLWidget_AXIAL, 0, 1, 1, 1);

        label_AXIAL_2 = new QLabel(frame_AXIAL);
        label_AXIAL_2->setObjectName("label_AXIAL_2");

        gridLayout_4->addWidget(label_AXIAL_2, 1, 0, 1, 1);

        Slider_AXIAL = new QSlider(frame_AXIAL);
        Slider_AXIAL->setObjectName("Slider_AXIAL");
        Slider_AXIAL->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_4->addWidget(Slider_AXIAL, 1, 1, 1, 1);

        label_AXIALMAX = new QLabel(frame_AXIAL);
        label_AXIALMAX->setObjectName("label_AXIALMAX");

        gridLayout_4->addWidget(label_AXIALMAX, 1, 2, 1, 1);


        gridLayout_3->addWidget(frame_AXIAL, 0, 0, 1, 1);

        frame_CORONAL = new QFrame(frame_XYZ);
        frame_CORONAL->setObjectName("frame_CORONAL");
        frame_CORONAL->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: transparent; /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    border: none;                /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));
        frame_CORONAL->setFrameShape(QFrame::Shape::StyledPanel);
        frame_CORONAL->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_5 = new QGridLayout(frame_CORONAL);
        gridLayout_5->setObjectName("gridLayout_5");
        label_CORONAL = new QLabel(frame_CORONAL);
        label_CORONAL->setObjectName("label_CORONAL");
        label_CORONAL->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        gridLayout_5->addWidget(label_CORONAL, 0, 0, 1, 1);

        openGLWidget_CORONAL = new QVTKOpenGLNativeWidget(frame_CORONAL);
        openGLWidget_CORONAL->setObjectName("openGLWidget_CORONAL");
        openGLWidget_CORONAL->setMinimumSize(QSize(100, 100));

        gridLayout_5->addWidget(openGLWidget_CORONAL, 0, 1, 1, 1);

        label_CORONALMIN = new QLabel(frame_CORONAL);
        label_CORONALMIN->setObjectName("label_CORONALMIN");

        gridLayout_5->addWidget(label_CORONALMIN, 1, 0, 1, 1);

        Slider_CORONAL = new QSlider(frame_CORONAL);
        Slider_CORONAL->setObjectName("Slider_CORONAL");
        Slider_CORONAL->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_5->addWidget(Slider_CORONAL, 1, 1, 1, 1);

        label_CORONALMAX = new QLabel(frame_CORONAL);
        label_CORONALMAX->setObjectName("label_CORONALMAX");

        gridLayout_5->addWidget(label_CORONALMAX, 1, 2, 1, 1);


        gridLayout_3->addWidget(frame_CORONAL, 1, 0, 1, 1);

        frame_SAGITTAL = new QFrame(frame_XYZ);
        frame_SAGITTAL->setObjectName("frame_SAGITTAL");
        frame_SAGITTAL->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: transparent; /* \350\203\214\346\231\257\351\200\217\346\230\216 */\n"
"    border: none;                /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));
        frame_SAGITTAL->setFrameShape(QFrame::Shape::StyledPanel);
        frame_SAGITTAL->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_6 = new QGridLayout(frame_SAGITTAL);
        gridLayout_6->setObjectName("gridLayout_6");
        label_SAGITTAL = new QLabel(frame_SAGITTAL);
        label_SAGITTAL->setObjectName("label_SAGITTAL");
        label_SAGITTAL->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        gridLayout_6->addWidget(label_SAGITTAL, 0, 0, 1, 1);

        openGLWidget_SAGITTAL = new QVTKOpenGLNativeWidget(frame_SAGITTAL);
        openGLWidget_SAGITTAL->setObjectName("openGLWidget_SAGITTAL");
        openGLWidget_SAGITTAL->setMinimumSize(QSize(100, 100));

        gridLayout_6->addWidget(openGLWidget_SAGITTAL, 0, 1, 1, 1);

        label_SAGITTALMIN = new QLabel(frame_SAGITTAL);
        label_SAGITTALMIN->setObjectName("label_SAGITTALMIN");

        gridLayout_6->addWidget(label_SAGITTALMIN, 1, 0, 1, 1);

        Slider_SAGITTAL = new QSlider(frame_SAGITTAL);
        Slider_SAGITTAL->setObjectName("Slider_SAGITTAL");
        Slider_SAGITTAL->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_6->addWidget(Slider_SAGITTAL, 1, 1, 1, 1);

        label_SAGITTALMAX = new QLabel(frame_SAGITTAL);
        label_SAGITTALMAX->setObjectName("label_SAGITTALMAX");

        gridLayout_6->addWidget(label_SAGITTALMAX, 1, 2, 1, 1);


        gridLayout_3->addWidget(frame_SAGITTAL, 2, 0, 1, 1);


        gridLayout_2->addWidget(frame_XYZ, 0, 1, 1, 1);

        frame_main = new QFrame(frame_vtkrender);
        frame_main->setObjectName("frame_main");
        frame_main->setFrameShape(QFrame::Shape::StyledPanel);
        frame_main->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_8 = new QGridLayout(frame_main);
        gridLayout_8->setObjectName("gridLayout_8");
        openGLWidget = new QVTKOpenGLNativeWidget(frame_main);
        openGLWidget->setObjectName("openGLWidget");
        openGLWidget->setMinimumSize(QSize(500, 500));

        gridLayout_8->addWidget(openGLWidget, 1, 0, 1, 1);

        frame_3 = new QFrame(frame_main);
        frame_3->setObjectName("frame_3");
        frame_3->setMaximumSize(QSize(16777215, 50));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);

        gridLayout_8->addWidget(frame_3, 2, 0, 1, 1);

        frame1 = new QFrame(frame_main);
        frame1->setObjectName("frame1");
        frame1->setMaximumSize(QSize(16777215, 100));
        horizontalLayout = new QHBoxLayout(frame1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_hospital = new QLabel(frame1);
        label_hospital->setObjectName("label_hospital");
        label_hospital->setMinimumSize(QSize(300, 100));
        label_hospital->setMaximumSize(QSize(16777215, 100));
        label_hospital->setFont(font);
        label_hospital->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout->addWidget(label_hospital);

        label_currenttime = new QLabel(frame1);
        label_currenttime->setObjectName("label_currenttime");
        label_currenttime->setMinimumSize(QSize(300, 100));
        label_currenttime->setMaximumSize(QSize(16777215, 100));
        label_currenttime->setFont(font);
        label_currenttime->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout->addWidget(label_currenttime);


        gridLayout_8->addWidget(frame1, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame_main, 0, 0, 1, 1);


        gridLayout->addWidget(frame_vtkrender, 0, 1, 1, 1);

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
        pushButton_opendicoms->setText(QCoreApplication::translate("MainWindow_UI", "\346\211\223\345\274\200DICOM\346\226\207\344\273\266\345\244\271", nullptr));
        pushButton_rawcompany->setText(QCoreApplication::translate("MainWindow_UI", "\346\211\223\345\274\200\345\205\254\345\217\270raw\346\226\207\344\273\266", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow_UI", "\346\250\252\346\226\255\351\235\242", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow_UI", "\345\206\240\347\212\266\351\235\242", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow_UI", "\347\237\242\347\212\266\351\235\242", nullptr));

        label_showthreadnum->setText(QCoreApplication::translate("MainWindow_UI", "0", nullptr));
        pushButton_ti->setText(QCoreApplication::translate("MainWindow_UI", "\344\275\223\347\273\230\345\210\266", nullptr));
        pushButton_mian->setText(QCoreApplication::translate("MainWindow_UI", "\351\235\242\347\273\230\345\210\266", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow_UI", "\346\202\243\350\200\205\344\277\241\346\201\257", nullptr));
        groupBox_Pannel3D->setTitle(QCoreApplication::translate("MainWindow_UI", "3D\344\272\244\344\272\222", nullptr));
        label_bone_full_opacity->setText(QCoreApplication::translate("MainWindow_UI", "\351\252\250\351\252\274\345\256\214\345\205\250\351\200\217\346\230\216\345\272\246", nullptr));
        label_object_cubeAxes->setText(QCoreApplication::translate("MainWindow_UI", "\345\235\220\346\240\207\350\275\264", nullptr));
        label_fat_opacity->setText(QCoreApplication::translate("MainWindow_UI", "\350\204\202\350\202\252\351\200\217\346\230\216\345\272\246", nullptr));
        label_soft_tissue_opacity->setText(QCoreApplication::translate("MainWindow_UI", "\350\275\257\347\273\204\347\273\207\351\200\217\346\230\216\345\272\246", nullptr));
        label__bone_transition_opacity->setText(QCoreApplication::translate("MainWindow_UI", "\351\252\250\351\252\274\350\277\207\346\270\241\351\200\217\346\230\216\345\272\246", nullptr));
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
        pushButton_opencvtest->setText(QCoreApplication::translate("MainWindow_UI", "OpenCVtest", nullptr));
        pushButton_shutdown->setText(QCoreApplication::translate("MainWindow_UI", "shutdown", nullptr));
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
        label_hospital->setText(QCoreApplication::translate("MainWindow_UI", "TextLabel", nullptr));
        label_currenttime->setText(QCoreApplication::translate("MainWindow_UI", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_UI: public Ui_MainWindow_UI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_2D_UI_H
