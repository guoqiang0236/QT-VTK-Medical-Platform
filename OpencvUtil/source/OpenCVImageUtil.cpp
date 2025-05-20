#include "OpenCVImageUtil.h"
#include <QImage>
#include <QFileInfo>

OpenCVImageUtil::OpenCVImageUtil(QObject* parent)
    : QObject(parent)
{
}

bool OpenCVImageUtil::openImage(const std::string& filePath)
{
    
    m_mat = cv::imread(filePath, cv::IMREAD_UNCHANGED);
    if (m_mat.empty()) {
        return false;
    }
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


// 颜色空间转换实现
bool OpenCVImageUtil::convertColor(int type)
{
    if (m_mat.empty())
        return false;

    // 枚举类型与int的对应
    // 0: Gray, 1: HSV, 2: RGB
    switch (static_cast<ColorConvertType>(type)) {
    case ColorConvertType::Gray:
        if (m_mat.channels() == 3 || m_mat.channels() == 4) {
            cv::Mat gray;
            cv::cvtColor(m_mat, gray, cv::COLOR_BGR2GRAY);
            m_mat = gray;
            return true;
        }
        break;
    case ColorConvertType::HSV:
        if (m_mat.channels() == 3) {
            cv::Mat hsv;
            cv::cvtColor(m_mat, hsv, cv::COLOR_BGR2HSV);
            m_mat = hsv;
            return true;
        }
        break;
    case ColorConvertType::RGB:
        if (m_mat.channels() == 3) {
            cv::Mat rgb;
            cv::cvtColor(m_mat, rgb, cv::COLOR_BGR2RGB);
            m_mat = rgb;
            return true;
        }
        break;
    default:
        break;
    }
    return false;
}