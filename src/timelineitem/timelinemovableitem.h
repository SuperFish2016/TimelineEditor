#ifndef TIMELINEMOVABLEABSTRACTITEM_H
#define TIMELINEMOVABLEABSTRACTITEM_H

#include <QCoreApplication>
#include <QGraphicsRectItem>
#include "timelineconstants.h"

class TimelineGraphicsScene;
class TimelineKeyframeItem;
class TimelineFrameHandle;

class TimelineMovableItem : public QGraphicsRectItem
{
public:
    enum { Type = TimelineConstants::moveableAbstractItemUserType };
public:
    explicit TimelineMovableItem(QGraphicsItem *item);

    int type() const override;

    static TimelineMovableItem *cast(QGraphicsItem *item);
    static TimelineMovableItem *topMoveableItem(const QList<QGraphicsItem *> &items);
    static void emitScrollOffsetChanged(QGraphicsItem *item);
    static TimelineKeyframeItem *asTimelineKeyframeItem(QGraphicsItem *item);

    qreal rulerScaling() const;

    virtual void setPositionInteractive(const QPointF &point);
    virtual void commitPosition(const QPointF &point);
    virtual void itemMoved(const QPointF &start, const QPointF &end);
    virtual void itemDoubleClicked();

    int xPosScrollOffset(int x) const;

    qreal mapFromFrameToScene(qreal x) const;
    qreal mapFromSceneToFrame(qreal x) const;

    virtual void scrollOffsetChanged() = 0;

    virtual TimelineKeyframeItem *asTimelineKeyframeItem();
    virtual TimelineFrameHandle *asTimelineFrameHandle();

protected:
    int scrollOffset() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void setClampedXPosition(qreal x, qreal min, qreal max);
    TimelineGraphicsScene *timelineScene() const;
};
#endif // TIMELINEMOVABLEABSTRACTITEM_H
