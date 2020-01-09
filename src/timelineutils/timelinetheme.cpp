#include "timelinetheme.h"

#include <QApplication>
#include <QRegExp>
#include <QScreen>
#include <QPointer>
#include <QMetaEnum>
#include <QDebug>
TimelineTheme::TimelineTheme(AppTheme *originTheme, QObject *parent)
    : AppTheme(originTheme, parent)
{
}

QColor TimelineTheme::evaluateColorAtThemeInstance(const QString &themeColorName)
{
    const QMetaObject &m = *metaObject();
    const QMetaEnum e = m.enumerator(m.indexOfEnumerator("Color"));
    for (int i = 0, total = e.keyCount(); i < total; ++i) {
        if (QString::fromLatin1(e.key(i)) == themeColorName)
            return color(static_cast<AppTheme::Color>(i)).name();
    }

    qWarning() << Q_FUNC_INFO << "error while evaluating" << themeColorName;
    return {};
}

TimelineTheme *TimelineTheme::instance()
{
    static QPointer<TimelineTheme> qmldesignerTheme = new TimelineTheme(appTheme(), nullptr);
    return qmldesignerTheme;
}

QString TimelineTheme::replaceCssColors(const QString &input)
{
    QRegExp rx("creatorTheme\\.(\\w+)");

    int pos = 0;
    QString output = input;

    while ((pos = rx.indexIn(input, pos)) != -1) {
        const QString themeColorName = rx.cap(1);

        if (themeColorName == "smallFontPixelSize") {
            output.replace("creatorTheme." + themeColorName, QString::number(instance()->smallFontPixelSize()) + "px");
        } else if (themeColorName == "captionFontPixelSize") {
            output.replace("creatorTheme." + themeColorName, QString::number(instance()->captionFontPixelSize()) + "px");
        } else {
            const QColor color = instance()->evaluateColorAtThemeInstance(themeColorName);
            output.replace("creatorTheme." + rx.cap(1), color.name());
        }
        pos += rx.matchedLength();
    }

    return output;
}

QColor TimelineTheme::getColor(AppTheme::Color role)
{
    return instance()->color(role);
}

int TimelineTheme::smallFontPixelSize() const
{
    if (highPixelDensity())
        return 13;
    return 9;
}

int TimelineTheme::captionFontPixelSize() const
{
    if (highPixelDensity())
        return 14;
    return 11;
}

bool TimelineTheme::highPixelDensity() const
{
    return qApp->primaryScreen()->logicalDotsPerInch() > 100;
}

QPixmap TimelineTheme::getPixmap(const QString &id)
{
    return AppIconProvider::getPixmap(id);
}

QColor TimelineTheme::qmlDesignerBackgroundColorDarker() const
{
    return getColor(QmlDesigner_BackgroundColorDarker);
}

QColor TimelineTheme::qmlDesignerBackgroundColorDarkAlternate() const
{
    return getColor(QmlDesigner_BackgroundColorDarkAlternate);
}

QColor TimelineTheme::qmlDesignerTabLight() const
{
    return getColor(QmlDesigner_TabLight);
}

QColor TimelineTheme::qmlDesignerTabDark() const
{
    return getColor(QmlDesigner_TabDark);
}

QColor TimelineTheme::qmlDesignerButtonColor() const
{
    return getColor(QmlDesigner_ButtonColor);
}

QColor TimelineTheme::qmlDesignerBorderColor() const
{
    return getColor(QmlDesigner_BorderColor);
}

#include "timelineicon.h"
static QString iconPath()
{
    //return QLatin1String("/qmldesigner/propertyEditorQmlSources/imports/HelperWidgets/images/");
    return QLatin1String(":/images/");
}

QPixmap AppIconProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(requestedSize)
    QPixmap result = getPixmap(id);
    if (size)
        *size = result.size();
    return result;
}

QPixmap AppIconProvider::getPixmap(const QString &id)
{
    QPixmap result;

    if (id == "close")
        result = TimelineIcons::CLOSE_TOOLBAR.pixmap();
    else if (id == "plus")
        result = TimelineIcons::PLUS_TOOLBAR.pixmap();
    else if (id == "expression")
        result = Icon({{ iconPath() + QLatin1String("expression.png"), AppTheme::QmlDesigner_HighlightColor}}).pixmap();
    else if (id == "placeholder")
        result = Icon(iconPath() + "placeholder.png").pixmap();
    else if (id == "submenu")
        result = Icon(iconPath() + "submenu.png").pixmap();
    else if (id == "up-arrow")
        result = Icon({
                { iconPath() + QLatin1String("up-arrow.png"), AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "down-arrow")
        result = Icon({
                { iconPath() + QLatin1String("down-arrow.png"), AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "checkbox-indicator")
        result = Icon({
                { ":/qmldesigner/images/checkbox_indicator.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "tr")
        result = Icon({
                { ":/qmldesigner/images/tr.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "ok")
        result = Icon({
                { ":/utils/images/ok.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "error")
        result = Icon({
                { ":/utils/images/broken.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "anchor-top")
        result = Icon({
                { ":/qmldesigner/images/anchor_top.png", AppTheme::IconsBaseColor},
                { ":/qmldesigner/images/anchoreditem.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "anchor-right")
        result = Icon({
                { ":/qmldesigner/images/anchor_right.png", AppTheme::IconsBaseColor},
                { ":/qmldesigner/images/anchoreditem.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "anchor-bottom")
        result = Icon({
                { ":/qmldesigner/images/anchor_bottom.png", AppTheme::IconsBaseColor},
                { ":/qmldesigner/images/anchoreditem.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "anchor-left")
        result = Icon({
                { ":/qmldesigner/images/anchor_left.png", AppTheme::IconsBaseColor},
                { ":/qmldesigner/images/anchoreditem.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "anchor-horizontal")
        result = Icon({
                { ":/qmldesigner/images/anchor_horizontal.png", AppTheme::IconsBaseColor},
                { ":/qmldesigner/images/anchoreditem.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "anchor-vertical")
        result = Icon({
                { ":/qmldesigner/images/anchor_vertical.png", AppTheme::IconsBaseColor},
                { ":/qmldesigner/images/anchoreditem.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "anchor-fill")
        result = Icon({
                { ":/qmldesigner/images/anchor_fill.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "alignment-left")
        result = Icon({
                { ":/qmldesigner/images/alignment_left.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "alignment-left-h")
        result = Icon({
                { ":/qmldesigner/images/alignment_left.png", AppTheme::QmlDesigner_HighlightColor}}, Icon::Tint).pixmap();
    else if (id == "alignment-center")
        result = Icon({
                { ":/qmldesigner/images/alignment_center.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "alignment-center-h")
        result = Icon({
                { ":/qmldesigner/images/alignment_center.png", AppTheme::QmlDesigner_HighlightColor}}, Icon::Tint).pixmap();
    else if (id == "alignment-right")
        result = Icon({
                { ":/qmldesigner/images/alignment_right.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "alignment-right-h")
        result = Icon({
                { ":/qmldesigner/images/alignment_right.png", AppTheme::QmlDesigner_HighlightColor}}, Icon::Tint).pixmap();
    else if (id == "alignment-top")
        result = Icon({
                { ":/qmldesigner/images/alignment_top.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "alignment-top-h")
        result = Icon({
                { ":/qmldesigner/images/alignment_top.png", AppTheme::QmlDesigner_HighlightColor}}, Icon::Tint).pixmap();
    else if (id == "alignment-middle")
        result = Icon({
                { ":/qmldesigner/images/alignment_middle.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "alignment-middle-h")
        result = Icon({
                { ":/qmldesigner/images/alignment_middle.png", AppTheme::QmlDesigner_HighlightColor}}, Icon::Tint).pixmap();
    else if (id == "alignment-bottom")
        result = Icon({
                { ":/qmldesigner/images/alignment_bottom.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "alignment-bottom-h")
        result = Icon({
                { ":/qmldesigner/images/alignment_bottom.png", AppTheme::QmlDesigner_HighlightColor}}, Icon::Tint).pixmap();
    else if (id == "style-bold")
        result = Icon({
                { ":/qmldesigner/images/style_bold.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "style-bold-h")
        result = Icon({
                { ":/qmldesigner/images/style_bold.png", AppTheme::QmlDesigner_HighlightColor}}, Icon::Tint).pixmap();
    else if (id == "style-italic")
        result = Icon({
                { ":/qmldesigner/images/style_italic.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "style-italic-h")
        result = Icon({
                { ":/qmldesigner/images/style_italic.png", AppTheme::QmlDesigner_HighlightColor}}, Icon::Tint).pixmap();
    else if (id == "style-underline")
        result = Icon({
                { ":/qmldesigner/images/style_underline.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "style-underline-h")
        result = Icon({
                { ":/qmldesigner/images/style_underline.png", AppTheme::QmlDesigner_HighlightColor}}, Icon::Tint).pixmap();
    else if (id == "style-strikeout")
        result = Icon({
                { ":/qmldesigner/images/style_strikeout.png", AppTheme::IconsBaseColor}}, Icon::Tint).pixmap();
    else if (id == "style-strikeout-h")
        result = Icon({
                { ":/qmldesigner/images/style_strikeout.png", AppTheme::QmlDesigner_HighlightColor}}, Icon::Tint).pixmap();
    else
        qWarning() << Q_FUNC_INFO << "Image not found:" << id;

    return result;
}
