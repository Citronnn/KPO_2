#include "figuresscene.h"
#include "righttriangle.h"
#include "righttriangleroundedcorners.h"
#include "text.h"
#include "shape.h"
#include "triangletext.h"
#include <QMouseEvent>
#include <QGraphicsSceneEvent>

FiguresScene::FiguresScene(QObject *parent)
    : QGraphicsScene(parent) {
    setItemIndexMethod(QGraphicsScene::NoIndex);
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
        auto item = this->itemAt(figuresQueue.top()->getCentCoords().x, figuresQueue.top()->getCentCoords().y, QTransform::fromScale(1, 1));
        this->removeItem(item);
        figuresQueue.pop();
        figuresCount--;
    } catch (QueueException& e) {
        std::cout<<"Exception"<<std::endl;
    }

}
void FiguresScene::serialize(QDataStream &stream) {
    stream << figuresQueue.size();
    while (figuresQueue.size()) {
        stream << *(figuresQueue.top());
        popFigure();
    }

}
void FiguresScene::clearSFiguresScene() {
    this->clear();

    while (figuresQueue.size()) {
        figuresQueue.pop();
    };
}
void FiguresScene::deserialize(QDataStream &stream) {
    std::size_t figuresToLoadCount;
    stream >> figuresToLoadCount;

    if (figuresToLoadCount > 0) {
        clearSFiguresScene();
    } else {
        return;
    }

    for (size_t i = 0; i < figuresToLoadCount; i++) {
       Shape* figure = Shape::loadFigure(stream);

        if (figure) {
            this->addItem(figure);
            figuresCount ++;
            figuresQueue.push(figure, figuresCount);
        }
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
        figuresCount ++;
        figuresQueue.push(shape, figuresCount);
    }
}
