#ifndef SHAPE_H
#define SHAPE_H
#include <QDataStream>
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>

class FiguresScene;
#include "headers.h"
class Shape: public QGraphicsObject{
    friend class FiguresScene;
public:
    Shape(double x = 0, double y = 0);
    Shape(QDataStream& stream);
    static Shape* loadFigure(QDataStream& stream);
    virtual void changePos(double x, double y);
    void virtual saveToStream(QDataStream& stream) const = 0;

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
    Point cent = Point(0,0);
    int ang;
    Colour col = Colour(255,255,0);
    std:: vector<Point> pts;
    QRectF figureRect;
    QRectF boundingRect() const override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};
QDataStream& operator<<(QDataStream& stream, const Shape& shape);
QDataStream& operator<<(QDataStream& stream, const Shape* shape);
#endif
