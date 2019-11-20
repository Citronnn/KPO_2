#include "figuresscenemdi.h"
#include "ui_figuresscene.h"
#include "shapeview.h"
#include "righttriangle.h"
#include "righttriangleroundedcorners.h"
#include "text.h"
#include "triangletext.h"

FiguresSceneMdi::FiguresSceneMdi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FiguresSceneMdi)
{
    ui->setupUi(this);
    figureScene = new FiguresScene(this);
    ui->graphicsView->setScene(figureScene);
}

FiguresSceneMdi::~FiguresSceneMdi()
{
    delete ui;
}
