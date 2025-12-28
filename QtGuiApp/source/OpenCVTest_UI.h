/********************************************************************************
** Form generated from reading UI file 'OpenCVTest_UI.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef OPENCVTEST_UI_H
#define OPENCVTEST_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_OpenCVDialog
{
public:
    QGridLayout *gridLayout_2;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout;
    QPushButton *pushButton_openimage;
    QFrame *frame_4;
    QPushButton *pushButton_SCU;
    QFrame *frame_3;
    QGridLayout *gridLayout_4;
    QGraphicsView *graphicsView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OpenCVDialog)
    {
        if (OpenCVDialog->objectName().isEmpty())
            OpenCVDialog->setObjectName("OpenCVDialog");
        OpenCVDialog->resize(800, 580);
        gridLayout_2 = new QGridLayout(OpenCVDialog);
        gridLayout_2->setObjectName("gridLayout_2");
        frame_2 = new QFrame(OpenCVDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName("gridLayout_3");
        frame = new QFrame(frame_2);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(150, 16777215));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        pushButton_openimage = new QPushButton(frame);
        pushButton_openimage->setObjectName("pushButton_openimage");

        gridLayout->addWidget(pushButton_openimage, 0, 0, 1, 1);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName("frame_4");
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);

        gridLayout->addWidget(frame_4, 2, 0, 1, 1);

        pushButton_SCU = new QPushButton(frame);
        pushButton_SCU->setObjectName("pushButton_SCU");

        gridLayout->addWidget(pushButton_SCU, 1, 0, 1, 1);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);

        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_4 = new QGridLayout(frame_3);
        gridLayout_4->setObjectName("gridLayout_4");
        graphicsView = new QGraphicsView(frame_3);
        graphicsView->setObjectName("graphicsView");

        gridLayout_4->addWidget(graphicsView, 0, 0, 1, 1);


        gridLayout_3->addWidget(frame_3, 0, 1, 1, 1);


        gridLayout_2->addWidget(frame_2, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(OpenCVDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        gridLayout_2->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(OpenCVDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, OpenCVDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, OpenCVDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(OpenCVDialog);
    } // setupUi

    void retranslateUi(QDialog *OpenCVDialog)
    {
        OpenCVDialog->setWindowTitle(QCoreApplication::translate("OpenCVDialog", "Dialog", nullptr));
        pushButton_openimage->setText(QCoreApplication::translate("OpenCVDialog", "\346\211\223\345\274\200\345\233\276\347\211\207", nullptr));
        pushButton_SCU->setText(QCoreApplication::translate("OpenCVDialog", "\345\274\200\345\247\213\347\233\221\345\220\254DCMTK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OpenCVDialog: public Ui_OpenCVDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // OPENCVTEST_UI_H
