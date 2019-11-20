#include "shape.h"

Shape::Shape(double x, double y): ang(0), cent(x,y), col(255,255,0){
}
void Shape::changePos(double x, double y){
    for(auto& it: pts){
        it.x+=x - cent.x;
        it.y+=y - cent.y;
    }
    setPos(x,y);
    cent.x=x;
    cent.y=y;
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
