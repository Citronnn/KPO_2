#ifndef RIGHTTRIANGLEROUNDEDCORNERS_H
#define RIGHTTRIANGLEROUNDEDCORNERS_H

#include "headers.h"
#include "righttriangle.h"

class RightTriangleRoundedCorners: virtual public RightTriangle{
public:
    RightTriangleRoundedCorners(double x=0, double y=0, double a=0, double r=0);

    void print(std::ostream& out) override;

protected:
    double radiusCircle;
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
#endif
