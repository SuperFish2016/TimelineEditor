#include "timelinewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimelineWidget w;
    w.show();

    return a.exec();
}
