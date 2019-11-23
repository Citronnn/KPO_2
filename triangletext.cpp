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
    figureRect = QRectF(-(a*cos(M_PI/12))/2, -(a*cos(M_PI/12)) / 2, a*cos(M_PI/12),a*cos(M_PI/12));
}
TriangleText::TriangleText(QDataStream &stream)
    : Shape(stream) {
    stream >> side;
    QString qtext;
    stream >> qtext;
    text = qtext.toStdString();
    stream >> fontSize;
    length = text.length();
}
void TriangleText::saveToStream(QDataStream &stream) const {
    stream << QString::fromStdString("triangleText");
    stream << figureRect;
    stream << QPoint(cent.x, cent.y);
    stream << scenePos();
    stream << side;
    stream << QString::fromStdString(text);
    stream << fontSize;
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
    auto firstPoint = figureRect.topLeft().toPoint();
    auto secondPoint = QPoint(figureRect.bottomLeft().toPoint().rx() + side*sin(M_PI/12),figureRect.bottomRight().toPoint().ry());
    auto thirdPoint = QPoint(figureRect.topRight().toPoint().rx(),figureRect.topRight().toPoint().ry() + side*sin(M_PI/12));
    polygon << firstPoint << secondPoint << thirdPoint;
    painter->drawPolygon(polygon);
    painter->drawPolygon(polygon);
    auto font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);

    painter->drawText(figureRect.topLeft().x() + (side*cos(M_PI/12))/6,figureRect.topLeft().y() + (side*cos(M_PI/12))/2, QString::fromStdString(text));

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

