#ifndef TIMELINEICON_H
#define TIMELINEICON_H

#include <QIcon>
#include <QPair>
#include <QVector>
#include <QColor>
#include "apptheme.h"
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
const Icon HOME({{QLatin1String(":/utils/images/home.png"), AppTheme::PanelTextColorDark}}, Icon::Tint);
const Icon HOME_TOOLBAR({
        {QLatin1String(":/utils/images/home.png"), AppTheme::IconsBaseColor}});
const Icon EDIT_CLEAR({
        {QLatin1String(":/utils/images/editclear.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon EDIT_CLEAR_TOOLBAR({
        {QLatin1String(":/utils/images/editclear.png"), AppTheme::IconsBaseColor}});
const Icon LOCKED_TOOLBAR({
        {QLatin1String(":/utils/images/locked.png"), AppTheme::IconsBaseColor}});
const Icon LOCKED({
        {QLatin1String(":/utils/images/locked.png"), AppTheme::PanelTextColorDark}}, Icon::Tint);
const Icon UNLOCKED_TOOLBAR({
        {QLatin1String(":/utils/images/unlocked.png"), AppTheme::IconsBaseColor}});
const Icon PINNED({
        {QLatin1String(":/utils/images/pinned.png"), AppTheme::PanelTextColorDark}}, Icon::Tint);
const Icon NEXT({
        {QLatin1String(":/utils/images/next.png"), AppTheme::IconsWarningColor}}, Icon::MenuTintedStyle);
const Icon NEXT_TOOLBAR({
        {QLatin1String(":/utils/images/next.png"), AppTheme::IconsNavigationArrowsColor}});
const Icon PREV({
        {QLatin1String(":/utils/images/prev.png"), AppTheme::IconsWarningColor}}, Icon::MenuTintedStyle);
const Icon PREV_TOOLBAR({
        {QLatin1String(":/utils/images/prev.png"), AppTheme::IconsNavigationArrowsColor}});
const Icon PROJECT({
        {QLatin1String(":/utils/images/project.png"), AppTheme::PanelTextColorDark}}, Icon::Tint);
const Icon ZOOM({
        {QLatin1String(":/utils/images/zoom.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon ZOOM_TOOLBAR({
        {QLatin1String(":/utils/images/zoom.png"), AppTheme::IconsBaseColor}});
const Icon ZOOMIN_TOOLBAR({
        {QLatin1String(":/utils/images/zoom.png"), AppTheme::IconsBaseColor},
        {QLatin1String(":/utils/images/zoomin_overlay.png"), AppTheme::IconsBaseColor}});
const Icon ZOOMOUT_TOOLBAR({
        {QLatin1String(":/utils/images/zoom.png"), AppTheme::IconsBaseColor},
        {QLatin1String(":/utils/images/zoomout_overlay.png"), AppTheme::IconsBaseColor}});
const Icon FITTOVIEW_TOOLBAR({
        {QLatin1String(":/utils/images/fittoview.png"), AppTheme::IconsBaseColor}});
const Icon OK({
        {QLatin1String(":/utils/images/ok.png"), AppTheme::IconsRunToolBarColor}}, Icon::Tint);
const Icon NOTLOADED({
        {QLatin1String(":/utils/images/notloaded.png"), AppTheme::IconsErrorColor}}, Icon::Tint);
const Icon BROKEN({
        {QLatin1String(":/utils/images/broken.png"), AppTheme::IconsErrorColor}}, Icon::Tint);
const Icon CRITICAL({
        {QLatin1String(":/utils/images/warningfill.png"), AppTheme::BackgroundColorNormal},
        {QLatin1String(":/utils/images/error.png"), AppTheme::IconsErrorColor}}, Icon::Tint);
const Icon BOOKMARK({
        {QLatin1String(":/utils/images/bookmark.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon BOOKMARK_TOOLBAR({
        {QLatin1String(":/utils/images/bookmark.png"), AppTheme::IconsBaseColor}});
const Icon BOOKMARK_TEXTEDITOR({
        {QLatin1String(":/utils/images/bookmark.png"), AppTheme::Bookmarks_TextMarkColor}}, Icon::Tint);
const Icon SNAPSHOT_TOOLBAR({
        {QLatin1String(":/utils/images/snapshot.png"), AppTheme::IconsBaseColor}});
const Icon NEWSEARCH_TOOLBAR({
        {QLatin1String(":/utils/images/zoom.png"), AppTheme::IconsBaseColor},
        {QLatin1String(":/utils/images/iconoverlay_add_small.png"), AppTheme::IconsRunColor}});
const Icon SETTINGS_TOOLBAR({
    {QLatin1String(":/utils/images/settings.png"), AppTheme::IconsBaseColor}});

const Icon NEWFILE({
        {QLatin1String(":/utils/images/filenew.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon OPENFILE({
        {QLatin1String(":/utils/images/fileopen.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon OPENFILE_TOOLBAR({
        {QLatin1String(":/utils/images/fileopen.png"), AppTheme::IconsBaseColor}});
const Icon SAVEFILE({
        {QLatin1String(":/utils/images/filesave.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon SAVEFILE_TOOLBAR({
        {QLatin1String(":/utils/images/filesave.png"), AppTheme::IconsBaseColor}});

const Icon EXPORTFILE_TOOLBAR({
        {QLatin1String(":/utils/images/fileexport.png"), AppTheme::IconsBaseColor}});
const Icon MULTIEXPORTFILE_TOOLBAR({
        {QLatin1String(":/utils/images/filemultiexport.png"), AppTheme::IconsBaseColor}});

const Icon UNKNOWN_FILE({
        {QLatin1String(":/utils/images/unknownfile.png"), AppTheme::IconsBaseColor}});
const Icon DIR({
        {QLatin1String(":/utils/images/dir.png"), AppTheme::IconsBaseColor}});

const Icon UNDO({
        {QLatin1String(":/utils/images/undo.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon UNDO_TOOLBAR({
        {QLatin1String(":/utils/images/undo.png"), AppTheme::IconsBaseColor}});
const Icon REDO({
        {QLatin1String(":/utils/images/redo.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon REDO_TOOLBAR({
        {QLatin1String(":/utils/images/redo.png"), AppTheme::IconsBaseColor}});
const Icon COPY({
        {QLatin1String(":/utils/images/editcopy.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon COPY_TOOLBAR({
        {QLatin1String(":/utils/images/editcopy.png"), AppTheme::IconsBaseColor}});
const Icon PASTE({
        {QLatin1String(":/utils/images/editpaste.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon PASTE_TOOLBAR({
        {QLatin1String(":/utils/images/editpaste.png"), AppTheme::IconsBaseColor}});
const Icon CUT({
        {QLatin1String(":/utils/images/editcut.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon CUT_TOOLBAR({
        {QLatin1String(":/utils/images/editcut.png"), AppTheme::IconsBaseColor}});
const Icon RESET({
        {QLatin1String(":/utils/images/reset.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon RESET_TOOLBAR({
        {QLatin1String(":/utils/images/reset.png"), AppTheme::IconsBaseColor}});

const Icon ARROW_UP({
        {QLatin1String(":/utils/images/arrowup.png"), AppTheme::IconsBaseColor}});
const Icon ARROW_DOWN({
        {QLatin1String(":/utils/images/arrowdown.png"), AppTheme::IconsBaseColor}});
const Icon MINUS({
        {QLatin1String(":/utils/images/minus.png"), AppTheme::IconsBaseColor}});
const Icon PLUS_TOOLBAR({
        {QLatin1String(":/utils/images/plus.png"), AppTheme::IconsBaseColor}});
const Icon PLUS({
        {QLatin1String(":/utils/images/plus.png"), AppTheme::PaletteText}}, Icon::Tint);
const Icon MAGNIFIER({
        {QLatin1String(":/utils/images/magnifier.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon CLEAN({
        {QLatin1String(":/utils/images/clean_pane_small.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon CLEAN_TOOLBAR({
        {QLatin1String(":/utils/images/clean_pane_small.png"), AppTheme::IconsBaseColor}});
const Icon RELOAD({
        {QLatin1String(":/utils/images/reload_gray.png"), AppTheme::IconsBaseColor}});
const Icon TOGGLE_LEFT_SIDEBAR({
        {QLatin1String(":/utils/images/leftsidebaricon.png"), AppTheme::PanelTextColorMid}}, Icon::MenuTintedStyle);
const Icon TOGGLE_LEFT_SIDEBAR_TOOLBAR({
        {QLatin1String(":/utils/images/leftsidebaricon.png"), AppTheme::IconsBaseColor}});
const Icon TOGGLE_RIGHT_SIDEBAR({
        {QLatin1String(":/utils/images/rightsidebaricon.png"), AppTheme::PanelTextColorMid}}, Icon::MenuTintedStyle);
const Icon TOGGLE_RIGHT_SIDEBAR_TOOLBAR({
        {QLatin1String(":/utils/images/rightsidebaricon.png"), AppTheme::IconsBaseColor}});
const Icon CLOSE_TOOLBAR({
        {QLatin1String(":/utils/images/close.png"), AppTheme::IconsBaseColor}});
const Icon CLOSE_FOREGROUND({
        {QLatin1String(":/utils/images/close.png"), AppTheme::PanelTextColorDark}}, Icon::Tint);
const Icon CLOSE_BACKGROUND({
        {QLatin1String(":/utils/images/close.png"), AppTheme::PanelTextColorLight}}, Icon::Tint);
const Icon SPLIT_HORIZONTAL({
        {QLatin1String(":/utils/images/splitbutton_horizontal.png"), AppTheme::PanelTextColorMid}}, Icon::MenuTintedStyle);
const Icon SPLIT_HORIZONTAL_TOOLBAR({
        {QLatin1String(":/utils/images/splitbutton_horizontal.png"), AppTheme::IconsBaseColor}});
const Icon SPLIT_VERTICAL({
        {QLatin1String(":/utils/images/splitbutton_vertical.png"), AppTheme::PanelTextColorMid}}, Icon::MenuTintedStyle);
const Icon SPLIT_VERTICAL_TOOLBAR({
        {QLatin1String(":/utils/images/splitbutton_vertical.png"), AppTheme::IconsBaseColor}});
const Icon CLOSE_SPLIT_TOP({
        {QLatin1String(":/utils/images/splitbutton_closetop.png"), AppTheme::IconsBaseColor}});
const Icon CLOSE_SPLIT_BOTTOM({
        {QLatin1String(":/utils/images/splitbutton_closebottom.png"), AppTheme::IconsBaseColor}});
const Icon CLOSE_SPLIT_LEFT({
        {QLatin1String(":/utils/images/splitbutton_closeleft.png"), AppTheme::IconsBaseColor}});
const Icon CLOSE_SPLIT_RIGHT({
        {QLatin1String(":/utils/images/splitbutton_closeright.png"), AppTheme::IconsBaseColor}});
const Icon FILTER({
        {QLatin1String(":/utils/images/filtericon.png"), AppTheme::IconsBaseColor},
        {QLatin1String(":/utils/images/toolbuttonexpandarrow.png"), AppTheme::IconsBaseColor}});
const Icon LINK({
        {QLatin1String(":/utils/images/linkicon.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon LINK_TOOLBAR({
        {QLatin1String(":/utils/images/linkicon.png"), AppTheme::IconsBaseColor}});
const Icon SORT_ALPHABETICALLY_TOOLBAR({
        {QLatin1String(":/utils/images/sort_alphabetically.png"), AppTheme::IconsBaseColor}});
const Icon TOGGLE_PROGRESSDETAILS_TOOLBAR({
    {QLatin1String(":/utils/images/toggleprogressdetails.png"), AppTheme::IconsBaseColor}});
const Icon ONLINE_TOOLBAR({
        {QLatin1String(":/utils/images/online.png"), AppTheme::IconsBaseColor}});
const Icon DOWNLOAD({
        {QLatin1String(":/utils/images/download_arrow.png"), AppTheme::IconsRunColor},
        {QLatin1String(":/utils/images/download_base.png"), AppTheme::PanelTextColorDark}}, Icon::Tint);

const Icon WARNING({
        {QLatin1String(":/utils/images/warningfill.png"), AppTheme::BackgroundColorNormal},
        {QLatin1String(":/utils/images/warning.png"), AppTheme::IconsWarningColor}}, Icon::Tint);
const Icon WARNING_TOOLBAR({
        {QLatin1String(":/utils/images/warning.png"), AppTheme::IconsWarningToolBarColor}});
const Icon CRITICAL_TOOLBAR({
        {QLatin1String(":/utils/images/error.png"), AppTheme::IconsErrorToolBarColor}});
const Icon ERROR_TASKBAR({
        {QLatin1String(":/utils/images/compile_error_taskbar.png"), AppTheme::IconsErrorColor}}, Icon::Tint);
const Icon INFO({
        {QLatin1String(":/utils/images/warningfill.png"), AppTheme::BackgroundColorNormal},
        {QLatin1String(":/utils/images/info.png"), AppTheme::IconsInfoColor}}, Icon::Tint);
const Icon INFO_TOOLBAR({
        {QLatin1String(":/utils/images/info.png"), AppTheme::IconsInfoToolBarColor}});
const Icon EXPAND_ALL_TOOLBAR({
        {QLatin1String(":/find/images/expand.png"), AppTheme::IconsBaseColor}});
const Icon TOOLBAR_EXTENSION({
        {QLatin1String(":/utils/images/extension.png"), AppTheme::IconsBaseColor}});
const Icon RUN_SMALL({
        {QLatin1String(":/utils/images/run_small.png"), AppTheme::IconsRunColor}}, Icon::MenuTintedStyle);
const Icon RUN_SMALL_TOOLBAR({
        {QLatin1String(":/utils/images/run_small.png"), AppTheme::IconsRunToolBarColor}});
const Icon STOP_SMALL({
        {QLatin1String(":/utils/images/stop_small.png"), AppTheme::IconsStopColor}}, Icon::MenuTintedStyle);
const Icon STOP_SMALL_TOOLBAR({
        {QLatin1String(":/utils/images/stop_small.png"), AppTheme::IconsStopToolBarColor}});
const Icon INTERRUPT_SMALL({
        {QLatin1String(":/utils/images/interrupt_small.png"), AppTheme::IconsInterruptColor}}, Icon::MenuTintedStyle);
const Icon INTERRUPT_SMALL_TOOLBAR({{QLatin1String(":/utils/images/interrupt_small.png"), AppTheme::IconsInterruptToolBarColor}});
const Icon BOUNDING_RECT({{QLatin1String(":/utils/images/boundingrect.png"), AppTheme::IconsBaseColor}});
const Icon EYE_OPEN_TOOLBAR({{QLatin1String(":/utils/images/eye_open.png"), AppTheme::IconsBaseColor}});
const Icon EYE_CLOSED_TOOLBAR({ {QLatin1String(":/utils/images/eye_closed.png"), AppTheme::IconsBaseColor}});
const Icon REPLACE({{QLatin1String(":/utils/images/replace_a.png"), AppTheme::PanelTextColorMid},{QLatin1String(":/utils/images/replace_b.png"), AppTheme::IconsInfoColor}}, Icon::Tint);
const Icon EXPAND({{QLatin1String(":/utils/images/expand.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon EXPAND_TOOLBAR({{QLatin1String(":/utils/images/expand.png"), AppTheme::IconsBaseColor}});
const Icon COLLAPSE({{QLatin1String(":/utils/images/collapse.png"), AppTheme::PanelTextColorMid}}, Icon::Tint);
const Icon COLLAPSE_TOOLBAR({{QLatin1String(":/utils/images/collapse.png"), AppTheme::IconsBaseColor}});
const Icon PAN_TOOLBAR({{QLatin1String(":/utils/images/pan.png"), AppTheme::IconsBaseColor}});
const Icon EMPTY14(":/utils/images/empty14.png");
const Icon EMPTY16(":/utils/images/empty16.png");
const Icon OVERLAY_ADD({
        {":/utils/images/iconoverlay_add_background.png", AppTheme::BackgroundColorNormal},
        {":/utils/images/iconoverlay_add.png", AppTheme::IconsRunColor}}, Icon::Tint);
const Icon OVERLAY_WARNING({
        {":/utils/images/iconoverlay_warning_background.png", AppTheme::BackgroundColorNormal},
        {":/utils/images/iconoverlay_warning.png", AppTheme::IconsWarningColor}}, Icon::Tint);
const Icon OVERLAY_ERROR({
        {":/utils/images/iconoverlay_error_background.png", AppTheme::BackgroundColorNormal},
        {":/utils/images/iconoverlay_error.png", AppTheme::IconsErrorColor}}, Icon::Tint);

const Icon CODEMODEL_ERROR({
        {":/utils/images/codemodelerror.png", AppTheme::IconsErrorColor}}, Icon::Tint);
const Icon CODEMODEL_WARNING({
        {":/utils/images/codemodelwarning.png", AppTheme::IconsWarningColor}}, Icon::Tint);
const Icon CODEMODEL_DISABLED_ERROR({
        {":/utils/images/codemodelerror.png", AppTheme::IconsDisabledColor}}, Icon::Tint);
const Icon CODEMODEL_DISABLED_WARNING({{":/utils/images/codemodelwarning.png", AppTheme::IconsDisabledColor}}, Icon::Tint);
const Icon CODEMODEL_FIXIT({
        {":/utils/images/lightbulbcap.png", AppTheme::PanelTextColorMid},
        {":/utils/images/lightbulb.png", AppTheme::IconsWarningColor}}, Icon::Tint);

const Icon MACOS_TOUCHBAR_BOOKMARK(":/utils/images/macos_touchbar_bookmark.png");
const Icon MACOS_TOUCHBAR_CLEAR(":/utils/images/macos_touchbar_clear.png");

} // namespace TimelineIcons

#endif // TIMELINEICON_H
