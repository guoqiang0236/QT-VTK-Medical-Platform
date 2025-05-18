#include "MyProgressDialog.h"

MyProgressDialog::MyProgressDialog(const QString& labelText, QWidget* parent)
    : QProgressDialog(labelText, tr("取消"), 0, 100, parent)
{
    setWindowModality(Qt::WindowModal);
    setMinimumDuration(0);
    setAutoClose(false);
    setAutoReset(false);
    setValue(0);

    connect(this, &QProgressDialog::canceled, this, &MyProgressDialog::onCanceled);
}

void MyProgressDialog::setProgress(int value)
{
    setValue(value);
}

void MyProgressDialog::setMaximumValue(int max)
{
    setMaximum(max);
}

void MyProgressDialog::setLabelText(const QString& text)
{
    QProgressDialog::setLabelText(text);
}

void MyProgressDialog::onCanceled()
{
    emit canceledByUser();
}
