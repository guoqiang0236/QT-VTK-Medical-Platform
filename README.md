# QT-medical
QT-medical

### 主要功能

- 支持 2D 和 3D DICOM 图像的加载与显示
- 自定义启动画面（Custom Splash Screen）
- 图像文件类型检测
- 全局配置管理
- 基于 Qt 的现代化用户界面

## 快速开始

### 环境要求

- Qt 5.x 或更高版本
- CMake 3.15 或更高版本
- VTK 库

### 构建步骤

1. 克隆项目到本地：

   ```bash
   git clone <repository-url>
   cd QT-medical

2. 创建构建目录并运行 CMake
mkdir build
cd build
cmake ..

3. 编译项目：
cmake --build .

4. 运行应用程序：
./QtGuiApp


文件说明
QtGuiApp/include/：包含主要的头文件，例如 MainWindow.h、DicomViewer2D.h 等。
QtGuiApp/source/：实现文件，例如 customsplashscreen.cpp、DicomViewer2D.cpp 等。
QtGuiApp/res/：资源文件，包括图标、图片、QSS 样式表等。
QtGuiApp/ui/：Qt Designer 生成的 UI 文件。