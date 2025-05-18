#include "OpenCVImageUtil.h"
#include <QImage>
#include <QFileInfo>

OpenCVImageUtil::OpenCVImageUtil(QObject* parent)
    : QObject(parent)
{
}

bool OpenCVImageUtil::openImage(const QString& filePath)
{
    QFileInfo fi(filePath);
    if (!fi.exists() || !fi.isFile()) {
        emit imageOpenFailed("文件不存在: " + filePath);
        return false;
    }

    m_mat = cv::imread(filePath.toStdString(), cv::IMREAD_UNCHANGED);
    if (m_mat.empty()) {
        emit imageOpenFailed("无法打开图片: " + filePath);
        return false;
    }

    // 转换为QImage
    QImage img;
    if (m_mat.channels() == 3) {
        cv::Mat rgb;
        cv::cvtColor(m_mat, rgb, cv::COLOR_BGR2RGB);
        img = QImage(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888).copy();
    } else if (m_mat.channels() == 1) {
        img = QImage(m_mat.data, m_mat.cols, m_mat.rows, m_mat.step, QImage::Format_Grayscale8).copy();
    } else if (m_mat.channels() == 4) {
        cv::Mat rgba;
        cv::cvtColor(m_mat, rgba, cv::COLOR_BGRA2RGBA);
        img = QImage(rgba.data, rgba.cols, rgba.rows, rgba.step, QImage::Format_RGBA8888).copy();
    } else {
        emit imageOpenFailed("不支持的图片通道数: " + QString::number(m_mat.channels()));
        return false;
    }

    emit imageOpened(img);
    return true;
}

QImage OpenCVImageUtil::getCurrentImage() const
{
    if (m_mat.empty())
        return QImage();

    if (m_mat.channels() == 3) {
        cv::Mat rgb;
        cv::cvtColor(m_mat, rgb, cv::COLOR_BGR2RGB);
        return QImage(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888).copy();
    } else if (m_mat.channels() == 1) {
        return QImage(m_mat.data, m_mat.cols, m_mat.rows, m_mat.step, QImage::Format_Grayscale8).copy();
    } else if (m_mat.channels() == 4) {
        cv::Mat rgba;
        cv::cvtColor(m_mat, rgba, cv::COLOR_BGRA2RGBA);
        return QImage(rgba.data, rgba.cols, rgba.rows, rgba.step, QImage::Format_RGBA8888).copy();
    }
    return QImage();
}

cv::Mat OpenCVImageUtil::getCurrentMat() const
{
    return m_mat;
}
