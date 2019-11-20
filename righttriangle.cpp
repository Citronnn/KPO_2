#include "righttriangle.h"
RightTriangle::RightTriangle(double x, double y, double a) : Shape(x,y), side(a){
    pts.push_back({cent.x,cent.y+a*sqrt(3)/3});
    pts.push_back({cent.x-a/2,cent.y-a*sqrt(3)/6});
    pts.push_back({cent.x+a/2,cent.y-a*sqrt(3)/6});
}
void RightTriangle::print(std::ostream& out){
    out<<"Сторона "<< side<<"\n";
}
void RightTriangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPolygon polygon;   // Используем класс полигона, чтобы отрисовать треугольник
    // Помещаем координаты точек в полигональную модель
    for (Point point: pts) {
        polygon << QPoint(point.x,point.y);
    }

    painter->setBrush(QColor(col.r, col.g, col.b));     // Устанавливаем кисть, которой будем отрисовывать объект
    painter->drawPolygon(polygon);  // Рисуем треугольник по полигональной модели
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
