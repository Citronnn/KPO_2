#ifndef TEXT_H
#define TEXT_H
#include <string>
#include "headers.h"
#include "shape.h"

class Text : virtual public Shape{
public:
    Text(double x = 0, double y = 0, const std::string& text = "", int fontSize = 0);

    void print(std::ostream& out) override;

protected:
    std::string text;
    std::size_t length;
    int fontSize;
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
#endif
