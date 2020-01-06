#ifndef TIMELINEMOVETOOL_H
#define TIMELINEMOVETOOL_H
#include "timelineabstracttool.h"
class TimelineMovableAbstractItem;
class TimelineMoveTool : public TimelineAbstractTool
{
public:
    explicit TimelineMoveTool(TimelineGraphicsScene* scene, TimelineToolDelegate *delegate);
    virtual void mousePressEvent(TimelineMovableAbstractItem       *item, QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(TimelineMovableAbstractItem        *item, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(TimelineMovableAbstractItem     *item, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(TimelineMovableAbstractItem *item, QGraphicsSceneMouseEvent *event);

    virtual void keyPressEvent(QKeyEvent    *keyEvent);
    virtual void keyReleaseEvent(QKeyEvent  *keyEvent);
};

#endif // TIMELINEMOVETOOL_H
