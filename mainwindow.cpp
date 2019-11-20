#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figuresscene.h"
#include "figuresscenemdi.h"

#include <QMdiSubWindow>
#include <QMdiArea>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(this->width(), this->height()));
    auto newWindow = new FiguresSceneMdi(ui->mdiArea);
    auto newFiguresScene = ui->mdiArea->addSubWindow(newWindow);
    newFiguresScene->setWindowTitle("Сцена");
}

FiguresScene *MainWindow::getCurrentScene() {
    auto current_subwindow = ui->mdiArea->currentSubWindow();
    if (current_subwindow) {
        auto cur_scene_as_widget = current_subwindow->widget();
        auto cur_scene_window = dynamic_cast<FiguresSceneMdi*>(cur_scene_as_widget);

        return cur_scene_window->figureScene;
    } else {
        return nullptr;
    }
}
QList<FiguresScene *> MainWindow::getAllScenes() {
    auto scenes = ui->mdiArea->subWindowList();
    QList<FiguresScene*> result;

    for (auto scene : scenes) {
        auto scene_as_widget = scene->widget();
        auto shape_scene_mdi_window = dynamic_cast<FiguresSceneMdi*>(scene_as_widget);

        result.push_back(shape_scene_mdi_window->figureScene);
    }

    return result;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_radioButtonTriangle_clicked()
{
    auto scenes = getAllScenes();
    for (auto scene : scenes) {
        scene->setFigureType("triangle");
    }
}

void MainWindow::on_radioButtonTriangleWithCorners_clicked()
{
    auto scenes = getAllScenes();
    for (auto scene : scenes) {
        scene->setFigureType("triangleWithCorners");
    }
}

void MainWindow::on_radioButtonText_clicked()
{
    auto scenes = getAllScenes();
    for (auto scene : scenes) {
        scene->setFigureType("text");
    }
}

void MainWindow::on_radioButtonTriangleText_clicked()
{
    auto scenes = getAllScenes();
    for (auto scene : scenes) {
        scene->setFigureType("triangleText");
    }
}

void MainWindow::on_lineEditLength_textChanged(const QString &arg1)
{
    auto scenes = getAllScenes();
    for (auto scene : scenes) {
        scene->setFigureSideLength(arg1.toInt());
    }
}

void MainWindow::on_lineEditText_textChanged(const QString &arg1)
{
    auto scenes = getAllScenes();
    for (auto scene : scenes) {
        scene->setFigureText(arg1);
    }
}

void MainWindow::on_lineEditRadius_textChanged(const QString &arg1)
{
    auto scenes = getAllScenes();
    for (auto scene : scenes) {
        scene->setFigureRoundedRadius(arg1.toInt());
    }
}

void MainWindow::on_pushButton_clicked()
{
    auto scene = getCurrentScene();
    scene->popFigure();
}

void MainWindow::on_newSceneButton_clicked()
{
    auto newWindow = new FiguresSceneMdi(ui->mdiArea);
    auto newFiguresScene = ui->mdiArea->addSubWindow(newWindow);
    newFiguresScene->setWindowTitle("Сцена");
    newWindow->show();
}
