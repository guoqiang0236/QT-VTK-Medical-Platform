#include "FileManager.h"
#include <unordered_map>
#include <algorithm>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkDICOMImageReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <iostream>
#include <vtkNamedColors.h>
#include <vtkActor2D.h>
#include <vtkInteractorStyleImage.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>

FileManager::FileManager():
	m_filename(""),
	m_filtype(sysconfig::VtkFileType::UNKNOWN),
    m_VTKopenGLWidget(new QVTKOpenGLNativeWidget)
{
    m_viewer = vtkSmartPointer<vtkImageViewer2>::New();
    m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    DICOMreader = vtkSmartPointer<vtkDICOMImageReader>::New();
}

void FileManager::processData() const
{
}

void FileManager::UpdatePlotFile(const std::string fileaddr)
{
	m_filename = fileaddr;
    sysconfig::VtkFileType filetype = getFileTypeByExtension(fileaddr);
    GraphicsRendering(filetype);

}

void FileManager::UpdatePlotFiles(const std::string fileaddr)
{
    m_filename = fileaddr;
    sysconfig::VtkFileType filetype = sysconfig::VtkFileType::DICOMS;
    GraphicsRendering(filetype);
}

sysconfig::VtkFileType FileManager::getFileTypeByExtension(const std::string& extension)
{
    // 统一转换为小写处理
    std::string ext = extension;
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    // 预定义的扩展名映射表
    static const std::unordered_map<std::string, sysconfig::VtkFileType> extensionMap = {
        // 复合扩展名优先匹配
        {".nii.gz",  sysconfig::VtkFileType::NIFTI},
        {".vtk.json", sysconfig::VtkFileType::VTK_JSON},

        // 单个扩展名
        {".vtk",    sysconfig::VtkFileType::VTK_LEGACY},
        {".vti",    sysconfig::VtkFileType::VTK_XML},
        {".vtu",    sysconfig::VtkFileType::VTK_XML},
        {".vtp",    sysconfig::VtkFileType::VTK_XML},
        {".stl",    sysconfig::VtkFileType::STL},
        {".ply",    sysconfig::VtkFileType::PLY},
        {".obj",    sysconfig::VtkFileType::OBJ},
        {".csv",    sysconfig::VtkFileType::CSV},
        {".dcm",    sysconfig::VtkFileType::DICOM},
        {".nii",    sysconfig::VtkFileType::NIFTI},
        {".mhd",    sysconfig::VtkFileType::META_IMAGE},
        {".mha",    sysconfig::VtkFileType::META_IMAGE},
        {".jpg",    sysconfig::VtkFileType::JPEG},
        {".jpeg",   sysconfig::VtkFileType::JPEG},
        {".png",    sysconfig::VtkFileType::PNG},
        {".bmp",    sysconfig::VtkFileType::BMP},
        {".tiff",   sysconfig::VtkFileType::TIFF},
        {".tif",    sysconfig::VtkFileType::TIFF}
    };

    // 优先检查复合扩展名
    if (ext == ".nii.gz" || ext == ".vtk.json") {
        return extensionMap.at(ext);
    }

    // 分离最后一个扩展名
    size_t lastDot = ext.find_last_of('.');
    if (lastDot != std::string::npos) {
        std::string baseExt = ext.substr(lastDot);
        if (extensionMap.count(baseExt)) {
            return extensionMap.at(baseExt);
        }
    }

    return sysconfig::VtkFileType::UNKNOWN; // 需要添加UNKNOWN到枚举
}

void FileManager::GraphicsRendering(sysconfig::VtkFileType filetype)
{
    switch (filetype)
    {
    case sysconfig::VtkFileType::VTK_LEGACY:
        break;
    case sysconfig::VtkFileType::VTK_XML:
        break;
    case sysconfig::VtkFileType::STL:
        break;
    case sysconfig::VtkFileType::PLY:
        break;
    case sysconfig::VtkFileType::OBJ:
        break;
    case sysconfig::VtkFileType::CSV:
        break;
    case sysconfig::VtkFileType::DICOM:
        DicomGraphics();
        break;
    case sysconfig::VtkFileType::DICOMS:
        DicomFilesGraphics();
        break;
    case sysconfig::VtkFileType::NIFTI:
        break;
    case sysconfig::VtkFileType::META_IMAGE:
        break;
    case sysconfig::VtkFileType::JPEG:
        break;
    case sysconfig::VtkFileType::PNG:
        break;
    case sysconfig::VtkFileType::BMP:
        break;
    case sysconfig::VtkFileType::TIFF:
        break;
    case sysconfig::VtkFileType::VTK_JSON:
        break;
    case sysconfig::VtkFileType::UNKNOWN:
        break;
    default:
        break;
    }
}

void FileManager::DicomGraphics() {
    // 清理之前的资源
    CleanupVTKResources();

    // 创建新的DICOM读取器
    DICOMreader = vtkSmartPointer<vtkDICOMImageReader>::New();
    DICOMreader->SetFileName(m_filename.c_str());
    DICOMreader->Update();
  

    // 初始化新的Viewer和Interactor
    vtkNew<vtkNamedColors> colors;
    m_viewer = vtkSmartPointer<vtkImageViewer2>::New();
    m_viewer->SetRenderWindow(m_VTKopenGLWidget->renderWindow());
    m_viewer->SetInputConnection(DICOMreader->GetOutputPort());

    // 配置交互器
    m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    m_viewer->SetupInteractor(m_interactor);

    // 渲染并启动
    // 重置相机并自适应窗口
    vtkCamera* camera = m_viewer->GetRenderer()->GetActiveCamera();
    camera->ParallelProjectionOn(); // 启用平行投影（适用于医学图像）
    m_viewer->GetRenderer()->ResetCamera();

    // 计算图像宽高比并调整相机视口
    int* dims = DICOMreader->GetOutput()->GetDimensions();
    double aspectRatio = static_cast<double>(dims[0]) / dims[1];
    camera->SetViewAngle(30.0); // 初始视角角度（根据需求调整）
    camera->SetParallelScale(0.5 * dims[1]); // 自适应缩放
    m_viewer->Render();
    m_viewer->GetRenderer()->SetBackground(colors->GetColor3d("Black").GetData());
    m_viewer->GetRenderWindow()->SetWindowName("ReadDICOM");
   
    m_interactor->Start();
}

// 清理资源的辅助函数
void FileManager::CleanupVTKResources() {
    if (m_viewer) {
        m_viewer->GetRenderWindow()->Finalize(); // 终止渲染窗口
        m_viewer = nullptr; // 重置智能指针
        m_viewer = vtkSmartPointer<vtkImageViewer2>::New();
    }
    if (m_interactor) {
        m_interactor->TerminateApp(); // 终止交互器
        m_interactor = nullptr;
        m_interactor = vtkSmartPointer <vtkRenderWindowInteractor>::New();
    }
    DICOMreader = nullptr; // 重置DICOM读取器
    //m_VTKopenGLWidget->renderWindow()->RemoveAllObservers(); // 移除所有观察者
    //m_VTKopenGLWidget->renderWindow()->Render(); // 强制清空窗口
}
void FileManager::DicomFilesGraphics()
{
    // ====== 二维切片文件夹渲染部分 ======
    CleanupVTKResources();
    DICOMreader = vtkSmartPointer<vtkDICOMImageReader>::New();
    DICOMreader->SetDirectoryName(m_filename.c_str());
    DICOMreader->Update();
    vtkNew<vtkNamedColors> colors;
    m_viewer = vtkSmartPointer<vtkImageViewer2>::New();
    m_viewer->SetRenderWindow(m_VTKopenGLWidget->renderWindow());
    m_viewer->SetInputConnection(DICOMreader->GetOutputPort());

    // Slice status message.
    vtkNew<vtkTextProperty> sliceTextProp;
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> sliceTextMapper;
    std::string msg = StatusMessage::Format(m_viewer->GetSliceMin(),
        m_viewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkNew<vtkActor2D> sliceTextActor;
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);
    // Usage hint message.
    vtkNew<vtkTextProperty> usageTextProp;
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> usageTextMapper;
    usageTextMapper->SetInput(
        " test dicom\n ");
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkNew<vtkActor2D> usageTextActor;
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    //vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;

    // Make imageviewer2 and sliceTextMapper visible to our interactorstyle
    // to enable slice status message updates when scrolling through the slices.
    myInteractorStyle->SetImageViewer(m_viewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    m_viewer->SetupInteractor(m_interactor);
    // Make the interactor use our own interactorstyle
    // cause SetupInteractor() is defining it's own default interatorstyle
    // this must be called after SetupInteractor().
    m_interactor->SetInteractorStyle(myInteractorStyle);
    // Sdd slice status message and usage hint message to the renderer.
    m_viewer->GetRenderer()->AddActor2D(sliceTextActor);
    m_viewer->GetRenderer()->AddActor2D(usageTextActor);

    // Initialize rendering and interaction.
    // 重置相机并自适应窗口
    vtkCamera* camera = m_viewer->GetRenderer()->GetActiveCamera();
    camera->ParallelProjectionOn(); // 启用平行投影（适用于医学图像）
    m_viewer->GetRenderer()->ResetCamera();

    // 计算图像宽高比并调整相机视口
    int* dims = DICOMreader->GetOutput()->GetDimensions();
    double aspectRatio = static_cast<double>(dims[0]) / dims[1];
    camera->SetViewAngle(30.0); // 初始视角角度（根据需求调整）
    camera->SetParallelScale(0.5 * dims[1]); // 自适应缩放
    m_viewer->Render();
    m_viewer->GetRenderer()->SetBackground(
        colors->GetColor3d("Black").GetData());
    m_viewer->GetRenderWindow()->SetWindowName("ReadDICOMSeries");
    m_viewer->Render();
    m_interactor->Start();
}

QVTKOpenGLNativeWidget* FileManager::GetVTKopenGLWidget()
{
    return m_VTKopenGLWidget;
}

void FileManager::testVTK()
{
    // ========== VTK 初始化 =====

    // 3. 创建渲染器
    m_VTKopenGLWidget->renderWindow()->AddRenderer(m_renderer);

    // 4. 设置渲染器背景色
    m_renderer->SetBackground(0.2, 0.3, 0.4);

    // ===== 添加一个示例三维对象（球体）=====
    // 1. 创建数据源
    auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(2.0);

    // 2. 创建映射器
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    // 3. 创建演员
    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // 4. 将演员添加到渲染器
    m_renderer->AddActor(actor);

    // 5. 重置相机视角
    m_renderer->ResetCamera();

    // 6. 触发渲染
    m_VTKopenGLWidget->renderWindow()->Render();
}
