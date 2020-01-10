#include "timelinewidget.h"
#include <QApplication>
#include "timelinetheme.h"
#include "timelinetoolbar.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppTheme::initialPalette();
    QSettings themeSettings(":/themes/design.theme", QSettings::IniFormat);
    AppTheme* appTheme = new AppTheme("id");
    appTheme->readSettings(themeSettings);
    setAppTheme(appTheme);

    TimelineWidget w;
    TimelineToolBar tb(&w);
    w.show();

    return a.exec();
}
