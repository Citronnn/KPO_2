#include "figuresscene.h"
#include "righttriangle.h"
#include "righttriangleroundedcorners.h"
#include "text.h"
#include "triangletext.h"
#include <QMouseEvent>
#include <QGraphicsSceneEvent>

FiguresScene::FiguresScene(QObject *parent)
    : QGraphicsScene(parent) {
    setItemIndexMethod(QGraphicsScene::NoIndex);
//    ui->setupUi(this);
//    this->setFixedSize(QSize(this->width(), this->height()));

//    scene = new QGraphicsScene();   // Инициализируем графическую сцену
//    //shape = new RightTriangle(0,0,50);      // Инициализируем треугольник

//    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
//    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
//    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
//    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали
//    //shape = new RightTriangleRoundedCorners(50,60,150,35);
//    //shape = new Text(0,0,"qqqq", 12);
//    shape = new TriangleText(0,0,150,"qqwq",12);
//    scene->setSceneRect(-30,-30,40,40); // Устанавливае область графической сцены

//    scene->addItem(shape);   // Добавляем на сцену треугольник
//    shape->setPos(shape->getCentCoords().x,shape->getCentCoords().y);      // Устанавливаем треугольник в центр сцены
}

FiguresScene::~FiguresScene(){
}

void FiguresScene::setFigureType(QString newFigureType) {
     typeFigure = newFigureType;
}
void FiguresScene::setFigureRoundedRadius(int newRadius) {
    if (newRadius < 0) {
        newRadius = 0;
    }
    figureRoundedRadius = newRadius;
}
void FiguresScene::setFigureSideLength(int newLength) {
    if (newLength <= 0) {
        newLength = 1;
    }
    figureSideLength = newLength;
}
void FiguresScene::setFigureText(QString newText) {
    if (!newText.size()) {
        newText = "\"\"";
    }
    figureText = newText;
}
void FiguresScene::popFigure() {
    try {
        std::cout<<figuresQueue.top()->getCentCoords().x<<" ~ "<<figuresQueue.top()->getCentCoords().y<<std::endl;
        auto item = this->itemAt(figuresQueue.top()->getCentCoords().x, figuresQueue.top()->getCentCoords().y, QTransform::fromScale(1, 1));
        this->removeItem(item);
        figuresQueue.pop();
        figuresCount--;
    } catch (QueueException& e) {
        std::cout<<"kek"<<std::endl;
    }

}

QString FiguresScene::getFigureType() const {
    return typeFigure;
}
void FiguresScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    auto item = this->itemAt(event->scenePos(), QTransform::fromScale(1, 1));
    if(!item) {
        auto type = this->getFigureType().toStdString();
        if (type == "triangle") {
            shape = new RightTriangle(event->scenePos().rx(),event->scenePos().ry(),this->figureSideLength);
        } else if (type == "triangleWithCorners") {
            shape = new RightTriangleRoundedCorners(event->scenePos().rx(),event->scenePos().ry(),this->figureSideLength,this->figureRoundedRadius);
        } else if (type == "text") {
            shape = new Text(event->scenePos().rx(),event->scenePos().ry(),this->figureText.toStdString(),15);
        } else {
            shape = new TriangleText(event->scenePos().rx(),event->scenePos().ry(),this->figureSideLength,this->figureText.toStdString(),12);
        }
        shape->setPos(event->scenePos());
        this->addItem(shape);
        std::cout << event->scenePos().rx() << " \\ " << event->scenePos().ry()<<std::endl;
        std::cout << shape->getCentCoords().x << " * " << shape->getCentCoords().y<<std::endl;
        figuresCount ++;
        figuresQueue.push(shape, figuresCount);
    } else {
        std::cout << "qqqqqqqqqqqqqqqq"<<std::endl;
    }
}
