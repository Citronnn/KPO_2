#ifndef FIGURESSCENE_H
#define FIGURESSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include "shape.h"
#include "priorityQueueContainer.h"

namespace Ui {
class FiguresScene;
}

class FiguresScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit FiguresScene(QObject *parent = nullptr);
    void setFigureType(QString newFigureType);
    void setFigureSideLength(int newLength);
    void setFigureRoundedRadius(int newRadius);
    void setFigureText(QString newText);
    void popFigure();
    QString getFigureType() const;
    ~FiguresScene();

private:
    Ui::FiguresScene *ui;
    QGraphicsScene *scene;     // Объявляем графическую сцену
    QString typeFigure = "triangle";
    int figureSideLength = 150;
    int figureRoundedRadius = 40;
    QString figureText = "\"\"";
    Shape* shape;
    PriorityQueue<Shape*> figuresQueue;
    int figuresCount = 0;

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // FIGURESSCENE_H
