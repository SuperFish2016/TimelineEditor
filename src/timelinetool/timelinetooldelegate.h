#ifndef TIMELINETOOLDELEGATE_H
#define TIMELINETOOLDELEGATE_H
#include <memory>
#include <QGraphicsSceneMouseEvent>
#include "timelinemovetool.h"
#include "timelineselectiontool.h"
class TimelineGraphicsScene;
class TimelineMovableAbstractItem;

class TimelineToolDelegate
{
public:
    TimelineToolDelegate(TimelineGraphicsScene* scene);
    QPointF startPoint() const{return start_;}
    TimelineMovableAbstractItem* item() const{return current_item_;}

public:
    void mousePressEvent(TimelineMovableAbstractItem        *item, QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(TimelineMovableAbstractItem         *item, QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(TimelineMovableAbstractItem      *item, QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(TimelineMovableAbstractItem  *item, QGraphicsSceneMouseEvent *event);
    void clearSelection();
private:
    bool hitCanvas(QGraphicsSceneMouseEvent *event);
    void reset();
    void setItem(TimelineMovableAbstractItem *item, const Qt::KeyboardModifiers& modifiers = Qt::NoModifier);
private:
    static const int dragDistance = 20;
    TimelineGraphicsScene* scene_;
    QPointF start_;
    std::unique_ptr< TimelineMoveTool >      move_tool_;
    std::unique_ptr< TimelineSelectionTool > select_tool_;

    TimelineAbstractTool *current_tool_ = nullptr;
    TimelineMovableAbstractItem *current_item_ = nullptr;
};


#endif // TIMELINETOOLDELEGATE_H
