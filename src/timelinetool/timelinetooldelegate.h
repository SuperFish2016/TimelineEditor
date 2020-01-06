#ifndef TIMELINETOOLDELEGATE_H
#define TIMELINETOOLDELEGATE_H
#include <memory>
#include <QGraphicsSceneMouseEvent>
#include "timelinemovetool.h"
#include "timelineselectiontool.h"
class TimelineGraphicsScene;
class TimelineMovableItem;

class TimelineToolDelegate
{
public:
    TimelineToolDelegate(TimelineGraphicsScene* scene);
    QPointF startPoint() const{return start_;}
    TimelineMovableItem* item() const{return current_item_;}

public:
    void mousePressEvent(TimelineMovableItem        *item, QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(TimelineMovableItem         *item, QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(TimelineMovableItem      *item, QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(TimelineMovableItem  *item, QGraphicsSceneMouseEvent *event);
    void clearSelection();
private:
    bool hitCanvas(QGraphicsSceneMouseEvent *event);
    void reset();
    void setItem(TimelineMovableItem *item, const Qt::KeyboardModifiers& modifiers = Qt::NoModifier);
private:
    static const int dragDistance = 20;
    TimelineGraphicsScene* scene_;
    QPointF start_;
    std::unique_ptr< TimelineMoveTool >      move_tool_;
    std::unique_ptr< TimelineSelectionTool > select_tool_;

    TimelineAbstractTool *current_tool_ = nullptr;
    TimelineMovableItem *current_item_ = nullptr;
};


#endif // TIMELINETOOLDELEGATE_H
