#include "shape.h"
#include "righttriangle.h"
#include "righttriangleroundedcorners.h"
#include "text.h"
#include "triangletext.h"
#include <QGraphicsSceneEvent>
#include <QCursor>

Shape::Shape(double x, double y): ang(0), cent(x,y), col(255,255,0){
    this->setPos(x,y);
}
Shape::Shape(QDataStream& stream) {
    stream >> figureRect;
    QPoint qcent;
    stream >> qcent;
    cent = Point(qcent.x(),qcent.y());
    QPointF pos;
    stream >> pos;

    setPos(pos);
}
void Shape::changePos(double x, double y){
    for(auto& it: pts){
        it.x+=x - cent.x;
        it.y+=y - cent.y;
    }
    this->setPos(x,y);
    cent.x=x;
    cent.y=y;
}

Shape* Shape::loadFigure(QDataStream &stream) {
    QString type;
    stream >> type;
    if (type == "triangle") {
        return new RightTriangle(stream);
    } else if (type == "triangleWithCorners") {
        return new RightTriangleRoundedCorners(stream);
    } else if (type == "text") {
        return new Text(stream);
    } else {
        return new TriangleText(stream);
    }
}
Point Shape::getCentCoords() const {
    return cent;
}
QRectF Shape::boundingRect() const {
    return figureRect;
}
void Shape::changeColour(short r, short g, short b){
    col={r,g,b};
}

void Shape::forPrint(std::ostream& out){
    out<<"Центр. коорд. "<<cent.x<<" "<<cent.y<<std::endl;
    out<<"Угол поворота "<<ang<<std::endl;
    out<<"Точки "<<std::endl;
    int count=0;
    for(const auto& it: pts){
        count++;
        out<<count<<") ("<<it.x<<", "<<it.y<<")\n";
    }
    out<<"Цвет "<<col.r<<" "<<col.g<<" "<<col.b<<std::endl;
}
void Shape::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    this->setPos(mapToScene(event->pos()));
    this->cent.x = mapToScene(event->pos()).x();
    this->cent.y = mapToScene(event->pos()).y();
}

void Shape::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    Q_UNUSED(event)
}
void Shape::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ArrowCursor));

    Q_UNUSED(event)
}
QDataStream& operator<<(QDataStream& stream, const Shape& shape) {
    shape.saveToStream(stream);
    return stream;
}

QDataStream& operator<<(QDataStream& stream, const Shape* shape) {
    shape->saveToStream(stream);
    return stream;
}
