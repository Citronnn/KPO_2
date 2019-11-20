#ifndef SHAPE_H
#define SHAPE_H
#include <QDataStream>
#include <QGraphicsItem>

class ShapeScene;
#include "headers.h"
class Shape: public QGraphicsItem{
    friend class ShapeScene;
public:
    Shape(double x = 0, double y = 0);

    virtual void changePos(double x, double y);

    virtual void forPrint(std::ostream& out);
    virtual void changeColour(short r, short g, short b);
    Point getCentCoords() const;
    virtual void print(std::ostream& out) = 0;

    friend std::ostream& operator<<(std::ostream& out, Shape& sh){
        sh.forPrint(out);
        sh.print(out);
        return out;
    }
    virtual ~Shape(){}

protected:
    Point cent;
    int ang;
    Colour col;
    std:: vector<Point> pts;
    QRectF figureRect;
    QRectF boundingRect() const override;
};
#endif
