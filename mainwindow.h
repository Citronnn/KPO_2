#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "figuresscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_radioButtonTriangle_clicked();

    void on_radioButtonTriangleWithCorners_clicked();

    void on_radioButtonText_clicked();

    void on_radioButtonTriangleText_clicked();

    void on_lineEditLength_textChanged(const QString &arg1);

    void on_lineEditText_textChanged(const QString &arg1);

    void on_lineEditRadius_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_newSceneButton_clicked();

    void on_openAction_triggered();

    void on_saveAction_triggered();

private:
    Ui::MainWindow *ui;
    FiguresScene* getCurrentScene();
    QList<FiguresScene*> getAllScenes();
};
#endif // MAINWINDOW_H
