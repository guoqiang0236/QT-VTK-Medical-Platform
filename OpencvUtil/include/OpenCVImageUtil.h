#pragma once
#include "OpencvUtil_Export.h"
#include "pch.h"
#include <QObject>
#include <QString>
#include <QImage>
#include <opencv2/opencv.hpp>

class OPENCVUTIL_API OpenCVImageUtil : public QObject
{
    Q_OBJECT
public:
    explicit OpenCVImageUtil(QObject* parent = nullptr);

    // 打开图片，成功返回true
    bool openImage(const QString& filePath);

    // 获取当前图片（QImage格式，便于Qt界面显示）
    QImage getCurrentImage() const;

    // 获取当前图片（cv::Mat格式，便于OpenCV处理）
    cv::Mat getCurrentMat() const;

signals:
    // 打开图片成功时触发
    void imageOpened(const QImage& image);

    // 打开图片失败时触发
    void imageOpenFailed(const QString& error);

private:
    cv::Mat m_mat;
};
