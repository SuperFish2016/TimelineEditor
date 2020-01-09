#include "timelinewidget.h"
#include <QApplication>
#include "timelinetheme.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimelineWidget w;
    w.show();

    AppTheme::initialPalette();
    QSettings themeSettings(":/themes/design.theme", QSettings::IniFormat);
    AppTheme* appTheme = new AppTheme("id");
    appTheme->readSettings(themeSettings);
    setAppTheme(appTheme);

    w.setStyleSheet(QString("background-color: %1").arg(TimelineTheme::instance()->qmlDesignerBackgroundColorDarker().name()));

    return a.exec();
}
