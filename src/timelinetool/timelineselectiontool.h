#ifndef TIMELINESELECTIONTOOL_H
#define TIMELINESELECTIONTOOL_H

#include "timelineabstracttool.h"
class TimelineSelectionTool : public TimelineAbstractTool
{
public:
    explicit TimelineSelectionTool(TimelineGraphicsScene* scene, TimelineToolDelegate *delegate);
    virtual void mousePressEvent(TimelineMovableAbstractItem       *item, QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(TimelineMovableAbstractItem        *item, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(TimelineMovableAbstractItem     *item, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(TimelineMovableAbstractItem *item, QGraphicsSceneMouseEvent *event);

    virtual void keyPressEvent(QKeyEvent    *keyEvent);
    virtual void keyReleaseEvent(QKeyEvent  *keyEvent);
};

#endif // TIMELINESELECTIONTOOL_H
