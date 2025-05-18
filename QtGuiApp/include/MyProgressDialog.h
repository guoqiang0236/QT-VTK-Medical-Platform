#pragma once

#include "pch.h"
#include <QProgressDialog>

class MyProgressDialog : public QProgressDialog
{
    Q_OBJECT
public:
    explicit MyProgressDialog(const QString& labelText, QWidget* parent = nullptr);

    // 设置进度值
    void setProgress(int value);

    // 设置最大值
    void setMaximumValue(int max);

    // 设置提示文本
    void setLabelText(const QString& text);

signals:
    void canceledByUser();

private slots:
    void onCanceled();
};
