// Viewer2D.cpp
#include "Viewer2D.h"
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkActor2D.h>
#include <vtkErrorCode.h>
#include <stdexcept>

Viewer2D::Viewer2D(QVTKOpenGLNativeWidget* widget)
    : ViewerBase(widget) 
{
    m_orientation = 0;
    m_imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    m_interactor = vtkSmartPointer< vtkRenderWindowInteractor>::New();
    m_interactorStyle = vtkSmartPointer<myVtkInteractorStyleImage>::New();
    m_interactorStyle->SetSliceChangedCallback([this](int slice) 
        {
            emit sliceChanged(slice);
        });
	m_reslice = vtkSmartPointer<vtkImageReslice>::New();
	m_matrix = vtkSmartPointer<vtkMatrix4x4>::New();
    message = "";
}

Viewer2D::~Viewer2D()
{
}

void Viewer2D::loadDicomFile(const std::string& path) {
    cleanup();
    initializeReader(path);
    setupViewer();
    resetCamera();
}

void Viewer2D::loadDicomDirectory(const std::string& path)
{
    try {
        cleanup();
        initializeReader(path);
        setViewOrientation(static_cast<SliceOrientation>(m_orientation));
        setupViewer();
        setupAnnotations();
        setupInteractor();
        resetCamera();
       
        m_vtkWidget->renderWindow()->Render();
        //m_vtkWidget->renderWindow()->GetInteractor()->Start();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        throw std::runtime_error("2D DICOM series loading failed: " + std::string(e.what()));
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        throw std::runtime_error("An error occurred: " + std::string(e.what()));
    }
}

void Viewer2D::loadRawData()
{
    try {
        cleanup();
        //setrawdataViewOrientation(static_cast<SliceOrientation>(m_orientation));
        
        setuprawviewer();
        setViewOrientation(static_cast<SliceOrientation>(m_orientation));
        setupAnnotations();
        setupInteractor();
        resetCamera();

        m_vtkWidget->renderWindow()->Render();
        //m_vtkWidget->renderWindow()->GetInteractor()->Start();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        throw std::runtime_error("2D rawdata loading failed: " + std::string(e.what()));
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        throw std::runtime_error("An error occurred: " + std::string(e.what()));
    }
}


void Viewer2D::setupViewer() {
    if (!m_dicomreader || m_dicomreader->GetErrorCode() != vtkErrorCode::NoError) {
        throw std::runtime_error("Invalid DICOM data");
    }
    m_imageViewer->SetRenderWindow(m_vtkWidget->renderWindow());
    m_imageViewer->SetInputConnection(m_dicomreader->GetOutputPort());
    m_interactorStyle = vtkSmartPointer<myVtkInteractorStyleImage>::New();
    m_interactorStyle->SetImageViewer(m_imageViewer);
    m_interactorStyle->SetSliceChangedCallback([this](int slice) {
        emit sliceChanged(slice);
        });
    m_interactor->SetInteractorStyle(m_interactorStyle);
    m_imageViewer->GetRenderWindow()->SetInteractor(m_interactor);
    m_imageViewer->Render();
}

void Viewer2D::setuprawviewer()
{
    if (!m_imagereader || m_imagereader->GetErrorCode() != vtkErrorCode::NoError) {
        throw std::runtime_error("Invalid raw data");
    }
    m_reslice->SetInputConnection(m_imagereader->GetOutputPort());
    m_matrix->Identity(); // 单位矩阵表示 XY 平面
    m_matrix->SetElement(1, 1, -1); // 设置切片位置
    m_reslice->SetResliceAxes(m_matrix);
    m_reslice->SetInterpolationModeToLinear();
    m_reslice->Update();

    m_imageViewer->SetRenderWindow(m_vtkWidget->renderWindow());
    m_imageViewer->SetInputConnection(m_reslice->GetOutputPort());
    m_interactorStyle = vtkSmartPointer<myVtkInteractorStyleImage>::New();
    m_interactorStyle->SetImageViewer(m_imageViewer);
    m_interactorStyle->SetSliceChangedCallback([this](int slice) {
        emit sliceChanged(slice);
        });
    m_interactor->SetInteractorStyle(m_interactorStyle);
    m_imageViewer->GetRenderWindow()->SetInteractor(m_interactor);
    m_imageViewer->Render();
}

void Viewer2D::setupAnnotations()
{
    // 创建切片信息文本
    vtkNew<vtkTextProperty> textProp;
    textProp->SetFontFamilyToCourier();
    textProp->SetFontSize(20);
    textProp->SetColor(1, 1, 1); // 白色文本
   

    vtkNew<vtkTextMapper> sliceTextMapper;
    std::string msg = StatusMessage::Format(m_imageViewer->GetSliceMin(),
        m_imageViewer->GetSliceMax()+1);
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(textProp);
    
    vtkNew<vtkActor2D> sliceTextActor;
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(20, 30);
    m_interactorStyle->SetStatusMapper(sliceTextMapper);
    // Usage hint message.
    vtkNew<vtkTextProperty> usageTextProp;
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> usageTextMapper;
    usageTextMapper->SetInput(
        message.c_str());
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkNew<vtkActor2D> usageTextActor;
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // Sdd slice status message and usage hint message to the renderer.
    m_imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    m_imageViewer->GetRenderer()->AddActor2D(usageTextActor);
}
void Viewer2D::setupInteractor() {
    // 配置自定义交互风格
    if (!m_imageViewer)
        return;
    m_imageViewer->SetupInteractor(m_interactor);
    
    if (!m_interactorStyle)
        return;
    m_interactor->SetInteractorStyle(m_interactorStyle);
   
}

void Viewer2D::updateSliceText() {
    
}

void Viewer2D::resetCamera() {
    m_renderer->ResetCamera();
    m_renderer->GetActiveCamera()->Zoom(1.5); // 适当缩放
    m_vtkWidget->renderWindow()->Render();
   
}

void Viewer2D::setViewOrientation(SliceOrientation orientation) {
    switch (orientation) {
    case SliceOrientation::AXIAL:
        m_imageViewer->SetSliceOrientation(vtkImageViewer2::SLICE_ORIENTATION_XY);
        break;
    case SliceOrientation::CORONAL:
        m_imageViewer->SetSliceOrientation(vtkImageViewer2::SLICE_ORIENTATION_YZ);
        break;
    case SliceOrientation::SAGITTAL:
        m_imageViewer->SetSliceOrientation(vtkImageViewer2::SLICE_ORIENTATION_XZ);
        break;
    default:
        m_interactorStyle->EnableMouseWheel(true);
        break;
    }
    resetCamera();
}
void Viewer2D::setrawdataViewOrientation(SliceOrientation orientation)
{
    if (!m_imagereader || m_imagereader->GetErrorCode() != vtkErrorCode::NoError) {
        throw std::runtime_error("Invalid raw data");
    }
    m_reslice->SetInputConnection(m_imagereader->GetOutputPort());
   
    switch (orientation) {
    case SliceOrientation::AXIAL: {
        m_matrix->Identity(); // 单位矩阵表示 XY 平面
        m_matrix->SetElement(1, 1, -1); // 设置切片位置
        break;
    }
    case SliceOrientation::CORONAL: {
        m_matrix->Identity();
        m_matrix->SetElement(0, 0, 0); // X 轴 -> Z
        m_matrix->SetElement(0, 2, 1);
        m_matrix->SetElement(1, 1, 1); // Y 轴保持不变
        m_matrix->SetElement(2, 0, 1); // Z 轴 -> X
        m_matrix->SetElement(2, 2, 0);
        m_matrix->SetElement(1, 1, -1); // 设置切片位置
        break;
    }
    case SliceOrientation::SAGITTAL: {
        m_matrix->Identity();
        m_matrix->SetElement(0, 0, 0); // X 轴 -> Y
        m_matrix->SetElement(0, 1, 1);
        m_matrix->SetElement(1, 1, 0); // Y 轴 -> Z
        m_matrix->SetElement(1, 2, 1);
        m_matrix->SetElement(2, 0, 1); // Z 轴 -> X
        m_matrix->SetElement(2, 2, 0);
        break;
    }
    default:
        m_interactorStyle->EnableMouseWheel(true);
        break;
    }
    m_reslice->SetResliceAxes(m_matrix);
    m_reslice->SetInterpolationModeToLinear();
    m_reslice->Update();
    resetCamera();
}
void Viewer2D::cleanup()
{
    if (m_renderer) {
        m_renderer->RemoveAllViewProps();
        m_vtkWidget->renderWindow()->RemoveRenderer(m_renderer);
        m_renderer->Delete();
        m_renderer = nullptr; // 确保删除后立即重置指针
    }

    if (m_imageViewer) {
        m_imageViewer->GetRenderWindow()->Finalize(); // 终止渲染窗口
        m_imageViewer->GetRenderer()->RemoveAllViewProps(); // 清理渲染器内容
        m_imageViewer = nullptr; // 重置智能指针
    }

    if (m_interactor) {
        m_interactor->TerminateApp(); // 终止交互器
        m_interactor = nullptr; // 重置智能指针
    }

    // 重新分配智能指针
    m_renderer = vtkRenderer::New();
    m_imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    m_dicomreader = nullptr;
}
void Viewer2D::startInteractor()
{
    if (!m_vtkWidget)
        return;
    m_vtkWidget->renderWindow()->GetInteractor()->Start();
}
int Viewer2D::getTotalSlices() const {
    return m_imageViewer->GetSliceMax() - m_imageViewer->GetSliceMin() + 1;
}
void Viewer2D::setSlice(int slice) {
    m_imageViewer->SetSlice(slice);
    if (m_interactorStyle) {
        std::string msg = StatusMessage::Format(slice, m_imageViewer->GetSliceMax()+1);
        m_interactorStyle->SetStatusMapper(msg.c_str());
        //m_interactorStyle->SetCurrentSliceNumberNow(slice);
    }
    m_vtkWidget->renderWindow()->Render();
}