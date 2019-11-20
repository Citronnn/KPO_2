#include "text.h"

Text::Text(double x, double y, const std::string& text, int fontSize) : Shape(x,y), text(text), fontSize(fontSize){
    length = text.length();
}

void Text::print(std::ostream& out){
    out<<"Длина текста "<< length<<"\n";
    out<<"Размер шрифта "<< fontSize<<"\n";
    out<<"Текст "<< text<<"\n";
}
void Text::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(QColor(col.r, col.g, col.b));

    auto font = painter->font();
    font.setPointSize(11);
    painter->setFont(font);

    painter->drawText(cent.x,cent.y, QString::fromStdString(text));
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
