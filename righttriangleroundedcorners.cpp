#include "righttriangleroundedcorners.h"

double getPt( int n1 , int n2 , float perc )
{
    double diff = n2 - n1;

    return n1 + ( diff * perc );
}

RightTriangleRoundedCorners::RightTriangleRoundedCorners(double x, double y, double a, double r) : RightTriangle(x,y,a), radiusCircle(r){
    pts.clear();
    if (r < a*sqrt(3)/3) {
        float x1 = cent.x + r*sqrt(3)/2;
        float x2 = cent.x;
        float x3 = cent.x - r*sqrt(3)/2;
        float y1 = cent.y + a*sqrt(3)/3 - 3*r/2;
        float y2 = cent.y+a*sqrt(3)/3;
        float y3 = cent.y + a*sqrt(3)/3 - 3*r/2;
        for( float i = 0 ; i < 1 ; i += 0.01 )
        {
            pts.push_back({getPt( getPt( x1 , x2 , i ) , getPt( x2 , x3 , i ) , i ), getPt(getPt( y1 , y2 , i ) , getPt( y2 , y3 , i ) , i)});
        }
        //лево низ
        x1 = cent.x - a/2 + r*sqrt(3)/2;
        x2 = cent.x-a/2;
        x3 = cent.x - a/2 + r*sqrt(3);
        y1 =  cent.y - a*sqrt(3)/6 + 3*r/2;
        y2 = cent.y-a*sqrt(3)/6;
        y3 = cent.y - a*sqrt(3)/6;
        for( float i = 0 ; i < 1 ; i += 0.01 )
        {
            pts.push_back({getPt( getPt( x1 , x2 , i ) , getPt( x2 , x3 , i ) , i ), getPt(getPt( y1 , y2 , i ) , getPt( y2 , y3 , i ) , i)});
        }
        //право низ
        x1 = cent.x + a/2 - r*sqrt(3);
        x2 = cent.x+a/2;
        x3 = cent.x + a/2 - r*sqrt(3)/2;
        y1 = cent.y - a*sqrt(3)/6;
        y2 = cent.y-a*sqrt(3)/6;
        y3 = cent.y - a*sqrt(3)/6 + 3*r/2;
        for( float i = 0 ; i < 1 ; i += 0.01 )
        {
            pts.push_back({getPt( getPt( x1 , x2 , i ) , getPt( x2 , x3 , i ) , i ), getPt(getPt( y1 , y2 , i ) , getPt( y2 , y3 , i ) , i)});
        }
    }
    else {
        pts.push_back({cent.x - r*sqrt(3)/2, cent.y + r/2});
        pts.push_back({cent.x + r*sqrt(3)/2, cent.y + r/2});
        pts.push_back({cent.x, cent.y - r});
    }

    figureRect = QRectF(-(a*cos(M_PI/12))/2, -(a*cos(M_PI/12)) / 2, a*cos(M_PI/12),a*cos(M_PI/12));
}
void RightTriangleRoundedCorners::saveToStream(QDataStream &stream) const {
    stream << QString::fromStdString("triangleWithCorners");
    stream << figureRect;
    stream << QPoint(cent.x, cent.y);
    stream << scenePos();
    stream << side;
    stream << radiusCircle;
}
RightTriangleRoundedCorners::RightTriangleRoundedCorners(QDataStream &stream)
    : RightTriangle(stream) {
    stream >> radiusCircle;
    if (radiusCircle < side*sqrt(3)/3) {
        float x1 = cent.x + radiusCircle*sqrt(3)/2;
        float x2 = cent.x;
        float x3 = cent.x - radiusCircle*sqrt(3)/2;
        float y1 = cent.y + side*sqrt(3)/3 ;
        float y2 = cent.y + side*sqrt(3)/3 - 3*radiusCircle/2;
        float y3 = cent.y + side*sqrt(3)/3 ;
        for( float i = 0 ; i < 1 ; i += 0.01 )
        {
            pts.push_back({getPt( getPt( x1 , x2 , i ) , getPt( x2 , x3 , i ) , i ), getPt(getPt( y1 , y2 , i ) , getPt( y2 , y3 , i ) , i)});
        }
        //верх
        //pts.push_back({cent.x + r*sqrt(3)/2, cent.y + a*sqrt(3)/3 - 3*r/2});
        //pts.push_back({cent.x, cent.y + a*sqrt(3)/3 - r});
        //pts.push_back({cent.x - r*sqrt(3)/2, cent.y + a*sqrt(3)/3 - 3*r/2});
        //лево низ
        x1 = cent.x + side/2 - radiusCircle*sqrt(3)/2;
        x2 = cent.x+side/2;
        x3 = cent.x + side/2 - radiusCircle*sqrt(3);
        y1 =  cent.y - side*sqrt(3)/6 ;
        y2 = cent.y-side*sqrt(3)/6+ 3*radiusCircle/2;
        y3 = cent.y - side*sqrt(3)/6+ 3*radiusCircle/2;
        for( float i = 0 ; i < 1 ; i += 0.01 )
        {
            pts.push_back({getPt( getPt( x1 , x2 , i ) , getPt( x2 , x3 , i ) , i ), getPt(getPt( y1 , y2 , i ) , getPt( y2 , y3 , i ) , i)});
        }
        //pts.push_back({cent.x - a/2 + r*sqrt(3)/2, cent.y - a*sqrt(3)/6 + 3*r/2});
       // pts.push_back({cent.x - a/2 + r*sqrt(3)/2, cent.y - a*sqrt(3)/6 + r/2});
        //pts.push_back({cent.x - a/2 + r*sqrt(3), cent.y - a*sqrt(3)/6});
        //право низ
        x1 = cent.x - side/2+ radiusCircle*sqrt(3);
        x2 = cent.x-side/2;
        x3 = cent.x - side/2 + radiusCircle*sqrt(3)/2;
        y1 = cent.y - side*sqrt(3)/6+ 3*radiusCircle/2;
        y2 = cent.y-side*sqrt(3)/6+ 3*radiusCircle/2;
        y3 = cent.y - side*sqrt(3)/6 ;
        for( float i = 0 ; i < 1 ; i += 0.01 )
        {
            pts.push_back({getPt( getPt( x1 , x2 , i ) , getPt( x2 , x3 , i ) , i ), getPt(getPt( y1 , y2 , i ) , getPt( y2 , y3 , i ) , i)});
        }
        //pts.push_back({cent.x + a/2 - r*sqrt(3), cent.y - a*sqrt(3)/6});
        //pts.push_back({cent.x + a/2 - r*sqrt(3)/2, cent.y - a*sqrt(3)/6 + r/2});
        //pts.push_back({cent.x + a/2 - r*sqrt(3)/2, cent.y - a*sqrt(3)/6 + 3*r/2});
    }
    else {
        pts.push_back({cent.x - radiusCircle*sqrt(3)/2, cent.y + radiusCircle/2});
        pts.push_back({cent.x + radiusCircle*sqrt(3)/2, cent.y + radiusCircle/2});
        pts.push_back({cent.x, cent.y - radiusCircle});
    }
}
void RightTriangleRoundedCorners::print(std::ostream& out){
    out<<"Радиус окружности сглаживания "<< radiusCircle<<"\n";
}
void RightTriangleRoundedCorners::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPolygon polygon;   // Используем класс полигона, чтобы отрисовать треугольник
    // Помещаем координаты точек в полигональную модель
    for (Point point: pts) {
        polygon << QPoint(point.x,point.y);
    }

    painter->drawPolygon(polygon);
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(QColor(col.r, col.g, col.b));     // Устанавливаем кисть, которой будем отрисовывать объект
    painter->drawPolygon(polygon);  // Рисуем треугольник по полигональной модели
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
