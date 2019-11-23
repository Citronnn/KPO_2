#include "text.h"

Text::Text(double x, double y, const std::string& text, int fontSize) : Shape(x,y), text(text), fontSize(fontSize){
    length = text.length();
    figureRect = QRectF(-10/1.5,-10/2, (10*1.2)*length, 30);
}
Text::Text(QDataStream &stream)
    : Shape(stream) {
    QString qtext;
    stream >> qtext;
    text = qtext.toStdString();
    stream >> fontSize;
    length = text.length();
}
void Text::saveToStream(QDataStream &stream) const {
    stream << QString::fromStdString("text");
    stream << figureRect;
    stream << QPoint(cent.x, cent.y);
    stream << scenePos();
    stream << QString::fromStdString(text);
    stream << fontSize;
}
void Text::print(std::ostream& out){
    out<<"Длина текста "<< length<<"\n";
    out<<"Размер шрифта "<< fontSize<<"\n";
    out<<"Текст "<< text<<"\n";
}
void Text::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {


    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawRect(figureRect);

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(QColor(col.r, col.g, col.b));
    auto font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);

    painter->drawText(figureRect, QString::fromStdString(text));
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
