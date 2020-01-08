#ifndef TIMELINEICON_H
#define TIMELINEICON_H

#include <QIcon>
#include <QPair>
#include <QVector>
#include <QColor>
#include "timelinetheme.h"
using IconMaskAndColor = QPair<QString, QColor>;

// Returns a recolored icon with shadow and custom disabled state for a
// series of grayscalemask|Theme::Color mask pairs
class Icon : public QVector<IconMaskAndColor>
{
public:
    enum IconStyleOption {
        None = 0,
        Tint = 1,
        DropShadow = 2,
        PunchEdges = 4,

        ToolBarStyle = Tint | DropShadow | PunchEdges,
        MenuTintedStyle = Tint | PunchEdges
    };

    Q_DECLARE_FLAGS(IconStyleOptions, IconStyleOption)

    Icon();
    Icon(std::initializer_list<IconMaskAndColor> args, IconStyleOptions style = ToolBarStyle);
    Icon(const QString &imageFileName);
    Icon(const Icon &other) = default;

    QIcon icon() const;
    // Same as icon() but without disabled state.
    QPixmap pixmap(QIcon::Mode iconMode = QIcon::Normal) const;


    // Combined icon pixmaps in Normal and Disabled states from several Icons
    static QIcon combinedIcon(const QList<QIcon> &icons);

private:
    IconStyleOptions m_style = None;
};

namespace TimelineIcons {

// Icons on the timeline ruler
const Icon WORK_AREA_HANDLE_LEFT(":/images/work_area_handle_left.png");
const Icon WORK_AREA_HANDLE_RIGHT(":/images/work_area_handle_right.png");
const Icon PLAYHEAD(":/images/playhead.png");

// Icons on the timeline tracks
const Icon KEYFRAME_LINEAR_INACTIVE(":/images/keyframe_linear_inactive.png");
const Icon KEYFRAME_LINEAR_ACTIVE(":/images/keyframe_linear_active.png");
const Icon KEYFRAME_LINEAR_SELECTED(":/images/keyframe_linear_selected.png");
const Icon KEYFRAME_MANUALBEZIER_INACTIVE(":/images/keyframe_manualbezier_inactive.png");
const Icon KEYFRAME_MANUALBEZIER_ACTIVE(":/images/keyframe_manualbezier_active.png");
const Icon KEYFRAME_MANUALBEZIER_SELECTED(":/images/keyframe_manualbezier_selected.png");
const Icon KEYFRAME_AUTOBEZIER_INACTIVE(":/images/keyframe_autobezier_inactive.png");
const Icon KEYFRAME_AUTOBEZIER_ACTIVE(":/images/keyframe_autobezier_active.png");
const Icon KEYFRAME_AUTOBEZIER_SELECTED(":/images/keyframe_autobezier_selected.png");
const Icon KEYFRAME_LINEARTOBEZIER_INACTIVE(":/images/keyframe_lineartobezier_inactive.png");
const Icon KEYFRAME_LINEARTOBEZIER_ACTIVE(":/images/keyframe_lineartobezier_active.png");
const Icon KEYFRAME_LINEARTOBEZIER_SELECTED(":/images/keyframe_lineartobezier_selected.png");

// Icons on the "section"
const Icon KEYFRAME(":/images/keyframe.png");
const Icon IS_KEYFRAME(":/images/is_keyframe.png");
const Icon NEXT_KEYFRAME({{":/images/next_keyframe.png", AppTheme::IconsBaseColor}});
const Icon PREVIOUS_KEYFRAME({{":/images/previous_keyframe.png", AppTheme::IconsBaseColor}});
const Icon LOCAL_RECORD_KEYFRAMES({{":/images/local_record_keyframes.png", AppTheme::IconsStopToolBarColor}});
const Icon ADD_TIMELINE({{":/images/add_timeline.png",  AppTheme::PanelTextColorDark}}, Icon::Tint);
const Icon ADD_TIMELINE_TOOLBAR({ {":/images/add_timeline.png",AppTheme::IconsBaseColor}});
const Icon REMOVE_TIMELINE({ {":/images/remove_timeline.png", AppTheme::PanelTextColorDark}},Icon::Tint);

// Icons on the toolbars
const Icon ANIMATION({{":/images/animation.png", AppTheme::IconsBaseColor}});
const Icon CURVE_EDITORDIALOG({{":/images/curveGraphIcon.png", AppTheme::IconsBaseColor}});
const Icon TO_FIRST_FRAME({{":/images/to_first_frame.png", AppTheme::IconsBaseColor}});
const Icon BACK_ONE_FRAME({{":/images/back_one_frame.png", AppTheme::IconsBaseColor}});
const Icon START_PLAYBACK({{":/images/start_playback.png", AppTheme::IconsRunToolBarColor}});
const Icon PAUSE_PLAYBACK({{":/images/pause_playback.png", AppTheme::IconsInterruptToolBarColor}});
const Icon FORWARD_ONE_FRAME({{":/images/forward_one_frame.png", AppTheme::IconsBaseColor}});
const Icon TO_LAST_FRAME({{":/images/to_last_frame.png", AppTheme::IconsBaseColor}});
const Icon LOOP_PLAYBACK({{":/images/loop_playback.png", AppTheme::IconsBaseColor}});
const Icon CURVE_PICKER({{":/images/curve_picker.png", AppTheme::IconsBaseColor}});
const Icon CURVE_EDITOR({{":/images/curve_editor.png", AppTheme::IconsBaseColor}});
const Icon GLOBAL_RECORD_KEYFRAMES({{":/images/global_record_keyframes.png", AppTheme::IconsStopToolBarColor}});
const Icon GLOBAL_RECORD_KEYFRAMES_OFF({{":/images/global_record_keyframes.png", AppTheme::IconsBaseColor}});
const Icon ZOOM_SMALL({{":/images/zoom_small.png", AppTheme::IconsBaseColor}});
const Icon ZOOM_BIG({{":/images/zoom_big.png", AppTheme::IconsBaseColor}});

} // namespace TimelineIcons

#endif // TIMELINEICON_H
