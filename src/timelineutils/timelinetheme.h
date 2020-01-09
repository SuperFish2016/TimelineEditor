#ifndef TIMELINETHEME_H
#define TIMELINETHEME_H
#include "apptheme.h"
class TimelineTheme : public AppTheme
{
    Q_OBJECT
public:
    static TimelineTheme* instance();
    static QString replaceCssColors(const QString &input);
    static QColor getColor(Color role);
    static QPixmap getPixmap(const QString &id);

    Q_INVOKABLE QColor qmlDesignerBackgroundColorDarker() const;
    Q_INVOKABLE QColor qmlDesignerBackgroundColorDarkAlternate() const;
    Q_INVOKABLE QColor qmlDesignerTabLight() const;
    Q_INVOKABLE QColor qmlDesignerTabDark() const;
    Q_INVOKABLE QColor qmlDesignerButtonColor() const;
    Q_INVOKABLE QColor qmlDesignerBorderColor() const;

    Q_INVOKABLE int smallFontPixelSize() const;
    Q_INVOKABLE int captionFontPixelSize() const;
    Q_INVOKABLE bool highPixelDensity() const;
private:
    TimelineTheme(AppTheme *originTheme, QObject *parent);
    QColor evaluateColorAtThemeInstance(const QString &themeColorName);
};

class AppIconProvider
{
public:
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    static QPixmap getPixmap(const QString &id);
};

#endif


