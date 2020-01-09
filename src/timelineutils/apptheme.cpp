#include "apptheme.h"
#include <QMetaEnum>
#include <QApplication>
#include <QPalette>
static AppTheme *m_appTheme = nullptr;

AppThemePrivate::AppThemePrivate()
{
    const QMetaObject &m = AppTheme::staticMetaObject;
    colors.resize        (m.enumerator(m.indexOfEnumerator("Color")).keyCount());
    imageFiles.resize    (m.enumerator(m.indexOfEnumerator("ImageFile")).keyCount());
    gradients.resize     (m.enumerator(m.indexOfEnumerator("Gradient")).keyCount());
    flags.resize         (m.enumerator(m.indexOfEnumerator("Flag")).keyCount());
}

AppTheme *appTheme()
{
    return m_appTheme;
}

AppTheme *proxyTheme()
{
    return new AppTheme(m_appTheme);
}

void setThemeApplicationPalette()
{
    if (m_appTheme && m_appTheme->flag(AppTheme::ApplyThemePaletteGlobally))
        QApplication::setPalette(m_appTheme->palette());
}

void setAppTheme(AppTheme *theme)
{
    if (m_appTheme == theme)
        return;
    delete m_appTheme;
    m_appTheme = theme;
    setThemeApplicationPalette();
}

AppTheme::AppTheme(const QString &id, QObject *parent)
  : QObject(parent), d(new AppThemePrivate())
{
    d->id = id;
}

AppTheme::AppTheme(AppTheme *originTheme, QObject *parent)
    : QObject(parent)
    , d(new AppThemePrivate(*(originTheme->d)))
{
}

AppTheme::~AppTheme()
{
    delete d;
}

QStringList AppTheme::preferredStyles() const
{
    return d->preferredStyles;
}

QString AppTheme::defaultTextEditorColorScheme() const
{
    return d->defaultTextEditorColorScheme;
}

QString AppTheme::id() const
{
    return d->id;
}

bool AppTheme::flag(AppTheme::Flag f) const
{
    return d->flags[f];
}

QColor AppTheme::color(AppTheme::Color role) const
{
    return d->colors[role].first;
}

QString AppTheme::imageFile(AppTheme::ImageFile imageFile, const QString &fallBack) const
{
    const QString &file = d->imageFiles.at(imageFile);
    return file.isEmpty() ? fallBack : file;
}

QGradientStops AppTheme::gradient(AppTheme::Gradient role) const
{
    return d->gradients[role];
}

QPair<QColor, QString> AppTheme::readNamedColor(const QString &color) const
{
    if (d->palette.contains(color))
        return qMakePair(d->palette[color], color);
    if (color == QLatin1String("style"))
        return qMakePair(QColor(), QString());

    const QColor col('#' + color);
    if (!col.isValid()) {
        qWarning("Color \"%s\" is neither a named color nor a valid color", qPrintable(color));
        return qMakePair(Qt::black, QString());
    }
    return qMakePair(col, QString());
}

QString AppTheme::filePath() const
{
    return d->fileName;
}

QString AppTheme::displayName() const
{
    return d->displayName;
}

void AppTheme::setDisplayName(const QString &name)
{
    d->displayName = name;
}

void AppTheme::readSettings(QSettings &settings)
{
    d->fileName = settings.fileName();
    const QMetaObject &m = *metaObject();

    {
        d->displayName = settings.value(QLatin1String("ThemeName"), QLatin1String("unnamed")).toString();
        d->preferredStyles = settings.value(QLatin1String("PreferredStyles")).toStringList();
        d->preferredStyles.removeAll(QString());
        d->defaultTextEditorColorScheme =
                settings.value(QLatin1String("DefaultTextEditorColorScheme")).toString();
    }
    {
        settings.beginGroup(QLatin1String("Palette"));
        foreach (const QString &key, settings.allKeys())
            d->palette[key] = readNamedColor(settings.value(key).toString()).first;
        settings.endGroup();
    }
    {
        settings.beginGroup(QLatin1String("Colors"));
        QMetaEnum e = m.enumerator(m.indexOfEnumerator("Color"));
        for (int i = 0, total = e.keyCount(); i < total; ++i) {
            const QString key = QLatin1String(e.key(i));
            if (!settings.contains(key)) {
                if (i < PaletteWindow || i > PaletteShadowDisabled)
                    qWarning("Theme \"%s\" misses color setting for key \"%s\".",
                             qPrintable(d->fileName), qPrintable(key));
                continue;
            }
            d->colors[i] = readNamedColor(settings.value(key).toString());
        }
        settings.endGroup();
    }
    {
        settings.beginGroup(QLatin1String("ImageFiles"));
        QMetaEnum e = m.enumerator(m.indexOfEnumerator("ImageFile"));
        for (int i = 0, total = e.keyCount(); i < total; ++i) {
            const QString key = QLatin1String(e.key(i));
            d->imageFiles[i] = settings.value(key).toString();
        }
        settings.endGroup();
    }
    {
        settings.beginGroup(QLatin1String("Gradients"));
        QMetaEnum e = m.enumerator(m.indexOfEnumerator("Gradient"));
        for (int i = 0, total = e.keyCount(); i < total; ++i) {
            const QString key = QLatin1String(e.key(i));
            QGradientStops stops;
            int size = settings.beginReadArray(key);
            for (int j = 0; j < size; ++j) {
                settings.setArrayIndex(j);
                if(settings.contains(QLatin1String("pos")))
                     return;
                const double pos = settings.value(QLatin1String("pos")).toDouble();
                if(settings.contains(QLatin1String("color")))
                    return;
                const QColor c('#' + settings.value(QLatin1String("color")).toString());
                stops.append(qMakePair(pos, c));
            }
            settings.endArray();
            d->gradients[i] = stops;
        }
        settings.endGroup();
    }
    {
        settings.beginGroup(QLatin1String("Flags"));
        QMetaEnum e = m.enumerator(m.indexOfEnumerator("Flag"));
        for (int i = 0, total = e.keyCount(); i < total; ++i) {
            const QString key = QLatin1String(e.key(i));
            if(settings.contains(key))
                return;
            d->flags[i] = settings.value(key).toBool();
        }
        settings.endGroup();
    }
}

QPalette AppTheme::initialPalette()
{
    static QPalette palette = QApplication::palette();
    return palette;
}

QPalette AppTheme::palette() const
{
    QPalette pal = initialPalette();
    if (!flag(DerivePaletteFromTheme))
        return pal;

    const static struct {
        Color themeColor;
        QPalette::ColorRole paletteColorRole;
        QPalette::ColorGroup paletteColorGroup;
        bool setColorRoleAsBrush;
    } mapping[] = {
        {PaletteWindow,                    QPalette::Window,           QPalette::All,      false},
        {PaletteWindowDisabled,            QPalette::Window,           QPalette::Disabled, false},
        {PaletteWindowText,                QPalette::WindowText,       QPalette::All,      true},
        {PaletteWindowTextDisabled,        QPalette::WindowText,       QPalette::Disabled, true},
        {PaletteBase,                      QPalette::Base,             QPalette::All,      false},
        {PaletteBaseDisabled,              QPalette::Base,             QPalette::Disabled, false},
        {PaletteAlternateBase,             QPalette::AlternateBase,    QPalette::All,      false},
        {PaletteAlternateBaseDisabled,     QPalette::AlternateBase,    QPalette::Disabled, false},
        {PaletteToolTipBase,               QPalette::ToolTipBase,      QPalette::All,      true},
        {PaletteToolTipBaseDisabled,       QPalette::ToolTipBase,      QPalette::Disabled, true},
        {PaletteToolTipText,               QPalette::ToolTipText,      QPalette::All,      false},
        {PaletteToolTipTextDisabled,       QPalette::ToolTipText,      QPalette::Disabled, false},
        {PaletteText,                      QPalette::Text,             QPalette::All,      true},
        {PaletteTextDisabled,              QPalette::Text,             QPalette::Disabled, true},
        {PaletteButton,                    QPalette::Button,           QPalette::All,      false},
        {PaletteButtonDisabled,            QPalette::Button,           QPalette::Disabled, false},
        {PaletteButtonText,                QPalette::ButtonText,       QPalette::All,      true},
        {PaletteButtonTextDisabled,        QPalette::ButtonText,       QPalette::Disabled, true},
        {PaletteBrightText,                QPalette::BrightText,       QPalette::All,      false},
        {PaletteBrightTextDisabled,        QPalette::BrightText,       QPalette::Disabled, false},
        {PaletteHighlight,                 QPalette::Highlight,        QPalette::All,      true},
        {PaletteHighlightDisabled,         QPalette::Highlight,        QPalette::Disabled, true},
        {PaletteHighlightedText,           QPalette::HighlightedText,  QPalette::All,      true},
        {PaletteHighlightedTextDisabled,   QPalette::HighlightedText,  QPalette::Disabled, true},
        {PaletteLink,                      QPalette::Link,             QPalette::All,      false},
        {PaletteLinkDisabled,              QPalette::Link,             QPalette::Disabled, false},
        {PaletteLinkVisited,               QPalette::LinkVisited,      QPalette::All,      false},
        {PaletteLinkVisitedDisabled,       QPalette::LinkVisited,      QPalette::Disabled, false},
        {PaletteLight,                     QPalette::Light,            QPalette::All,      false},
        {PaletteLightDisabled,             QPalette::Light,            QPalette::Disabled, false},
        {PaletteMidlight,                  QPalette::Midlight,         QPalette::All,      false},
        {PaletteMidlightDisabled,          QPalette::Midlight,         QPalette::Disabled, false},
        {PaletteDark,                      QPalette::Dark,             QPalette::All,      false},
        {PaletteDarkDisabled,              QPalette::Dark,             QPalette::Disabled, false},
        {PaletteMid,                       QPalette::Mid,              QPalette::All,      false},
        {PaletteMidDisabled,               QPalette::Mid,              QPalette::Disabled, false},
        {PaletteShadow,                    QPalette::Shadow,           QPalette::All,      false},
        {PaletteShadowDisabled,            QPalette::Shadow,           QPalette::Disabled, false}
    };

    for (auto entry: mapping) {
        const QColor themeColor = color(entry.themeColor);
        // Use original color if color is not defined in theme.
        if (themeColor.isValid()) {
            if (entry.setColorRoleAsBrush)
                // TODO: Find out why sometimes setBrush is used
                pal.setBrush(entry.paletteColorGroup, entry.paletteColorRole, themeColor);
            else
                pal.setColor(entry.paletteColorGroup, entry.paletteColorRole, themeColor);
        }
    }

    return pal;
}
