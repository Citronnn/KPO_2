#include "righttriangle.h"
#include <QTextOption>
RightTriangle::RightTriangle(double x, double y, double a) : Shape(x,y), side(a){
    pts.push_back({cent.x,cent.y+a*sqrt(3)/3});
    pts.push_back({cent.x-a/2,cent.y-a*sqrt(3)/6});
    pts.push_back({cent.x+a/2,cent.y-a*sqrt(3)/6});
    figureRect = QRectF(-(a*cos(M_PI/12))/2, -(a*cos(M_PI/12)) / 2, a*cos(M_PI/12),a*cos(M_PI/12));
}
RightTriangle::RightTriangle(QDataStream &stream)
    : Shape(stream) {
    stream >> side;
}
void RightTriangle::saveToStream(QDataStream &stream) const {
    stream << QString::fromStdString("triangle");
    stream << figureRect;
    stream << QPoint(cent.x, cent.y);
    stream << scenePos();
    stream << side;
}

void RightTriangle::print(std::ostream& out){
    out<<"Сторона "<< side<<"\n";
}
void RightTriangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPolygon polygon;   // Используем класс полигона, чтобы отрисовать треугольник
    // Помещаем координаты точек в полигональную модель
//    for (Point point: pts) {
//        polygon << QPoint(point.x,point.y);
//    }
    auto firstPoint = figureRect.topLeft().toPoint();
    auto secondPoint = QPoint(figureRect.bottomLeft().toPoint().rx() + side*sin(M_PI/12),figureRect.bottomRight().toPoint().ry());
    auto thirdPoint = QPoint(figureRect.topRight().toPoint().rx(),figureRect.topRight().toPoint().ry() + side*sin(M_PI/12));
    polygon << firstPoint << secondPoint << thirdPoint;
    painter->drawPolygon(polygon);
    painter->setBrush(QColor(col.r, col.g, col.b));     // Устанавливаем кисть, которой будем отрисовывать объект
    painter->drawPolygon(polygon);  // Рисуем треугольник по полигональной модели
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
