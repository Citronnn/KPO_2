#ifndef FIGURESSCENEMDI_H
#define FIGURESSCENEMDI_H

#include "figuresscene.h"
#include "mainwindow.h"
#include <QWidget>

namespace Ui {
class FiguresSceneMdi;
}

class FiguresSceneMdi : public QWidget
{
    Q_OBJECT

    friend class MainWindow;

public:
    explicit FiguresSceneMdi(QWidget *parent = nullptr);
    ~FiguresSceneMdi();

private:
    Ui::FiguresSceneMdi *ui;
    FiguresScene* figureScene;
};

#endif // FIGURESSCENEMDI_H
