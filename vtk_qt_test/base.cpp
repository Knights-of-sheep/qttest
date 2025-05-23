#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QScreen>
#include <QGuiApplication>
#include <vtkSmartPointer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <QVTKOpenGLNativeWidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建主窗口
    QWidget mainWindow;
    mainWindow.setWindowTitle("VTK in Qt");

    // 获取屏幕尺寸
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    int x = 200;
    int y = 200;
    int width = 1920;
    int height = 1080;

    // 确保窗口在屏幕范围内
    if (x + width > screenGeometry.width()) {
        x = screenGeometry.width() - width;
    }
    if (y + height > screenGeometry.height()) {
        y = screenGeometry.height() - height;
    }

    mainWindow.setGeometry(x, y, width, height);

    // 创建 vtkGenericOpenGLRenderWindow
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow =
        vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    // 创建 QVTKOpenGLNativeWidget 并设置渲染窗口
    QVTKOpenGLNativeWidget* vtkWidget = new QVTKOpenGLNativeWidget(&mainWindow);
    vtkWidget->setRenderWindow(renderWindow);

    // 创建渲染器并添加到渲染窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    // 创建一个简单的 VTK 物体（例如一个球体）
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
    sphereActor->SetMapper(sphereMapper);

    // 将物体添加到渲染器
    renderer->AddActor(sphereActor);

    // 设置布局
    QVBoxLayout* layout = new QVBoxLayout(&mainWindow);
    layout->addWidget(vtkWidget);
    mainWindow.setLayout(layout);

    // 显示主窗口
    mainWindow.show();

    return a.exec();
}    