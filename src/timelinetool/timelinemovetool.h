#ifndef TIMELINEMOVETOOL_H
#define TIMELINEMOVETOOL_H
#include "timelineabstracttool.h"
class TimelineMovableItem;
class TimelineMoveTool : public TimelineAbstractTool
{
public:
    explicit TimelineMoveTool(TimelineGraphicsScene* scene, TimelineToolDelegate *delegate);
    virtual void mousePressEvent(TimelineMovableItem       *item, QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(TimelineMovableItem        *item, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(TimelineMovableItem     *item, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(TimelineMovableItem *item, QGraphicsSceneMouseEvent *event);

    virtual void keyPressEvent(QKeyEvent    *keyEvent);
    virtual void keyReleaseEvent(QKeyEvent  *keyEvent);
};

#endif // TIMELINEMOVETOOL_H
