#include "mainwindow.h"
#include "headers.h"
#include "Point.h"
#include "Colour.h"
#include "shape.h"
#include "righttriangle.h"
#include "righttriangleroundedcorners.h"
#include "text.h"
#include "triangletext.h"
#include "priorityQueueExceptions.h"
#include "priorityQueueContainer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
