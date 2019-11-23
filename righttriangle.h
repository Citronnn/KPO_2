#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H
#include "shape.h"

class RightTriangle : virtual public Shape{
public:
    RightTriangle(double x = 0, double y = 0, double a = 0);
    RightTriangle(QDataStream& stream);
    void saveToStream(QDataStream& stream) const override;

    void print(std::ostream& out) override;

protected:
    double side;
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
#endif
