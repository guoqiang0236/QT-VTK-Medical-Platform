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
#include <vtkErrorCode.h>
#include "vtkMarchingCubes.h"
#include "vtkStripper.h"
#include "vtkProperty.h"
#include "vtkBoxWidget.h" 
#include "vtkTriangleFilter.h"
#include "vtkMassProperties.h"
#include "vtkSmoothPolyDataFilter.h"
#include "vtkPolyDataNormals.h"
#include "vtkContourFilter.h"
#include "vtkRecursiveDividingCubes.h"
#include "vtkRendererCollection.h"
#include <vtkAutoInit.h>  // ��ӱ�Ҫ�ĳ�ʼ��ͷ�ļ�
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);  // ����õ�������Ⱦ
FileManager::FileManager():
	m_filename(""),
	m_filtype(sysconfig::VtkFileType::UNKNOWN)
    //
{

    m_viewer = vtkSmartPointer<vtkImageViewer2>::New();
    m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    DICOMreader = vtkSmartPointer<vtkDICOMImageReader>::New();
    m_VTKopenGLWidget = new QVTKOpenGLNativeWidget;
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

void FileManager::UpdatePlotFiles3D(const std::string fileaddr)
{
    m_filename = fileaddr;
    sysconfig::VtkFileType filetype = sysconfig::VtkFileType::DICOMS3D;
    GraphicsRendering(filetype);
}

sysconfig::VtkFileType FileManager::getFileTypeByExtension(const std::string& extension)
{
    // ͳһת��ΪСд����
    std::string ext = extension;
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    // Ԥ�������չ��ӳ���
    static const std::unordered_map<std::string, sysconfig::VtkFileType> extensionMap = {
        // ������չ������ƥ��
        {".nii.gz",  sysconfig::VtkFileType::NIFTI},
        {".vtk.json", sysconfig::VtkFileType::VTK_JSON},

        // ������չ��
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

    // ���ȼ�鸴����չ��
    if (ext == ".nii.gz" || ext == ".vtk.json") {
        return extensionMap.at(ext);
    }

    // �������һ����չ��
    size_t lastDot = ext.find_last_of('.');
    if (lastDot != std::string::npos) {
        std::string baseExt = ext.substr(lastDot);
        if (extensionMap.count(baseExt)) {
            return extensionMap.at(baseExt);
        }
    }

    return sysconfig::VtkFileType::UNKNOWN; // ��Ҫ���UNKNOWN��ö��
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
    case sysconfig::VtkFileType::DICOMS3D:
        DicomFilesGraphics3D();
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
    // ����֮ǰ����Դ
    CleanupVTKResources();

    // �����µ�DICOM��ȡ��
    DICOMreader = vtkSmartPointer<vtkDICOMImageReader>::New();
    DICOMreader->SetFileName(m_filename.c_str());
    DICOMreader->Update();
    // ��������
    if (DICOMreader->GetErrorCode() != vtkErrorCode::NoError) {
        std::cerr << "DICOM ��ȡʧ�ܣ������룺" << DICOMreader->GetErrorCode() << std::endl;
        return;
    }
    vtkImageData* imageData = DICOMreader->GetOutput();
    if (!imageData) {
        std::cerr << "����DICOM ����Ϊ�գ�" << std::endl;
        return;
    }
    // ��ʼ���µ�Viewer��Interactor
    vtkNew<vtkNamedColors> colors;
    m_viewer = vtkSmartPointer<vtkImageViewer2>::New();
    m_viewer->SetRenderWindow(m_VTKopenGLWidget->renderWindow());
    m_viewer->SetInputConnection(DICOMreader->GetOutputPort());

    // ���ý�����
    m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    m_viewer->SetupInteractor(m_interactor);

    // ��Ⱦ������
    // �������������Ӧ����
    vtkCamera* camera = m_viewer->GetRenderer()->GetActiveCamera();
    camera->ParallelProjectionOn(); // ����ƽ��ͶӰ��������ҽѧͼ��
    m_viewer->GetRenderer()->ResetCamera();

    // ����ͼ���߱Ȳ���������ӿ�
    int* dims = DICOMreader->GetOutput()->GetDimensions();
    double aspectRatio = static_cast<double>(dims[0]) / dims[1];
    camera->SetViewAngle(30.0); // ��ʼ�ӽǽǶȣ��������������
    camera->SetParallelScale(0.5 * dims[1]); // ����Ӧ����
    m_viewer->Render();
    m_viewer->GetRenderer()->SetBackground(colors->GetColor3d("Black").GetData());
    m_viewer->GetRenderWindow()->SetWindowName("ReadDICOM");
   
    m_interactor->Start();
}

// ������Դ�ĸ�������
void FileManager::CleanupVTKResources() {
    if (m_viewer) {
        m_viewer->GetRenderWindow()->Finalize(); // ��ֹ��Ⱦ����
        m_viewer = nullptr; // ��������ָ��
        m_viewer = vtkSmartPointer<vtkImageViewer2>::New();
    }
    if (m_interactor) {
        m_interactor->TerminateApp(); // ��ֹ������
        m_interactor = nullptr;
        m_interactor = vtkSmartPointer <vtkRenderWindowInteractor>::New();
    }
    DICOMreader = nullptr; // ����DICOM��ȡ��
  /*  if(m_VTKopenGLWidget->renderWindow()->has)
    m_VTKopenGLWidget->renderWindow()->RemoveAllObservers();*/
    //m_VTKopenGLWidget->renderWindow()->RemoveAllObservers(); // �Ƴ����й۲���
    //m_VTKopenGLWidget->renderWindow()->Render(); // ǿ����մ���
}
void FileManager::DicomFilesGraphics()
{
    // ====== ��ά��Ƭ�ļ�����Ⱦ���� ======
    
    CleanupVTKResources();
    DICOMreader = vtkSmartPointer<vtkDICOMImageReader>::New();
    DICOMreader->SetDirectoryName(m_filename.c_str());
    DICOMreader->Update();
    // ��������
    if (DICOMreader->GetErrorCode() != vtkErrorCode::NoError) {
        std::cerr << "DICOM ��ȡʧ�ܣ������룺" << DICOMreader->GetErrorCode() << std::endl;
        return;
    }
    vtkImageData* imageData = DICOMreader->GetOutput();
    if (!imageData) {
        std::cerr << "����DICOM ����Ϊ�գ�" << std::endl;
        return;
    }
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
    // �������������Ӧ����
    vtkCamera* camera = m_viewer->GetRenderer()->GetActiveCamera();
    camera->ParallelProjectionOn(); // ����ƽ��ͶӰ��������ҽѧͼ��
    m_viewer->GetRenderer()->ResetCamera();

    // ����ͼ���߱Ȳ���������ӿ�
    int* dims = DICOMreader->GetOutput()->GetDimensions();
    double aspectRatio = static_cast<double>(dims[0]) / dims[1];
    camera->SetViewAngle(30.0); // ��ʼ�ӽǽǶȣ��������������
    camera->SetParallelScale(0.5 * dims[1]); // ����Ӧ����
    m_viewer->Render();
    m_viewer->GetRenderer()->SetBackground(
        colors->GetColor3d("Black").GetData());
    m_viewer->GetRenderWindow()->SetWindowName("ReadDICOMSeries");
    m_viewer->Render();
    m_interactor->Start();
}

void FileManager::DicomFilesGraphics3D()
{
    CleanupVTKResources();
    DICOMreader = vtkSmartPointer<vtkDICOMImageReader>::New();
    DICOMreader->SetDirectoryName(m_filename.c_str());
    DICOMreader->Update();
    // ��������
    if (DICOMreader->GetErrorCode() != vtkErrorCode::NoError) {
        std::cerr << "DICOM ��ȡʧ�ܣ������룺" << DICOMreader->GetErrorCode() << std::endl;
        return;
    }
    vtkImageData* imageData = DICOMreader->GetOutput();
    if (!imageData) {
        std::cerr << "����DICOM ����Ϊ�գ�" << std::endl;
        return;
    }

    // 4. ��ȡ��ֵ�棨������ֵ�ǹؼ�����
    vtkSmartPointer<vtkMarchingCubes> boneExtractor =
        vtkSmartPointer<vtkMarchingCubes>::New();
    boneExtractor->SetInputConnection(DICOMreader->GetOutputPort());
    boneExtractor->SetValue(0, 70);  // ����CT������ֵԼ300-2000����Ҫ�������ݵ���
    boneExtractor->Update();

    // 5. ƽ������
    vtkSmartPointer<vtkSmoothPolyDataFilter> smoother =
        vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    smoother->SetInputConnection(boneExtractor->GetOutputPort());
    smoother->SetNumberOfIterations(50);
    smoother->SetRelaxationFactor(0.1);
    smoother->Update();

    // 6. ����Mapper��Actor
    m_mapper =vtkSmartPointer<vtkPolyDataMapper>::New();
    m_mapper->SetInputConnection(smoother->GetOutputPort());
    m_mapper->ScalarVisibilityOff();

    m_actor =vtkSmartPointer<vtkActor>::New();
    m_actor->SetMapper(m_mapper);
    m_actor->GetProperty()->SetColor(1, 1, 1);  // ����ģ����ɫ

    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    m_renderer->SetBackground(0,0,0);  // ��ɫ����
    m_renderer = m_VTKopenGLWidget->renderWindow()->GetRenderers()->GetFirstRenderer();
    if (!m_renderer) {
        m_renderer = vtkSmartPointer<vtkRenderer>::New();
        m_VTKopenGLWidget->renderWindow()->AddRenderer(m_renderer);
    }

    m_renderer->AddActor(m_actor);
    
    // 8. ��������ӽ�
    vtkCamera* camera = m_viewer->GetRenderer()->GetActiveCamera();
    camera->SetPosition(0, 1, 0);   // �������λ��
    camera->SetFocalPoint(1, 0, 0);
    camera->SetViewUp(0, 1, 0);
    m_renderer->SetActiveCamera(camera);
    m_renderer->ResetCamera();


    //m_renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    //m_VTKopenGLWidget->setRenderWindow(m_renderWindow);
   
    m_VTKopenGLWidget->renderWindow()->AddRenderer(m_renderer);
    
    // 6. ���ý������
    m_interactor = vtkSmartPointer <vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
        vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    m_interactor->SetInteractorStyle(style);

    // 7. ��ʼ������������
    m_VTKopenGLWidget->renderWindow()->SetInteractor(m_interactor);
    m_interactor->Initialize();  // ������ã�
    m_VTKopenGLWidget->renderWindow()->Render();
    m_interactor->Start();
}

void FileManager::ViewChanged(const std::string viewport)
{
    int view = std::stoi(viewport);
    if (m_viewer)
    {
        m_viewer->SetSliceOrientation(view);
        m_viewer->Render();
    }
}

QVTKOpenGLNativeWidget* FileManager::GetVTKopenGLWidget()
{
    return m_VTKopenGLWidget;
}

void FileManager::testVTK()
{
    // ========== VTK ��ʼ�� =====

    // 3. ������Ⱦ��
    m_VTKopenGLWidget->renderWindow()->AddRenderer(m_renderer);

    // 4. ������Ⱦ������ɫ
    m_renderer->SetBackground(0.2, 0.3, 0.4);

    // ===== ���һ��ʾ����ά�������壩=====
    // 1. ��������Դ
    auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(2.0);

    // 2. ����ӳ����
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    // 3. ������Ա
    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // 4. ����Ա��ӵ���Ⱦ��
    m_renderer->AddActor(actor);

    // 5. ��������ӽ�
    m_renderer->ResetCamera();

    // 6. ������Ⱦ
    m_VTKopenGLWidget->renderWindow()->Render();
}
