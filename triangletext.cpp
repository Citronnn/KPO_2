#include "triangletext.h"

TriangleText::TriangleText(double x, double y, double a, const std::string& newText, int newFontSize) : Shape(x,y){
    side = a;
    pts.clear();
    pts.push_back({cent.x,cent.y+a*sqrt(3)/3});
    pts.push_back({cent.x-a/2,cent.y-a*sqrt(3)/6});
    pts.push_back({cent.x+a/2,cent.y-a*sqrt(3)/6});
    text = newText;
    fontSize = newFontSize;
    length = text.length();
}

void TriangleText::print(std::ostream& out){
    out << "Сторона треугольника " << side<<"\n";
    out<<"Длина текста "<< length<<"\n";
    out<<"Размер шрифта "<< fontSize<<"\n";
    out<<"Текст "<< text<<"\n";
}

void TriangleText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(QColor(col.r, col.g, col.b));
    QPolygon polygon;   // Используем класс полигона, чтобы отрисовать треугольник
    // Помещаем координаты точек в полигональную модель
    for (Point point: pts) {
        polygon << QPoint(point.x,point.y);
    }
    painter->drawPolygon(polygon);
    auto font = painter->font();
    font.setPointSize(11);
    painter->setFont(font);

    painter->drawText(cent.x,cent.y, QString::fromStdString(text));

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

