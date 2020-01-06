#include "timelinemovableitem.h"
#include "../timelinegraphicsscene.h"
#include <QGraphicsSceneMouseEvent>
TimelineMovableItem::TimelineMovableItem(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{

}

void TimelineMovableItem::setPositionInteractive(const QPointF &) {}

void TimelineMovableItem::commitPosition(const QPointF &) {}

void TimelineMovableItem::itemMoved(const QPointF & /*start*/, const QPointF &end)
{
    setPositionInteractive(end);
}

void TimelineMovableItem::itemDoubleClicked()
{
    // to be overridden by child classes if needed
}

int TimelineMovableItem::scrollOffset() const
{
    return timelineScene()->scrollOffset();
}

int TimelineMovableItem::xPosScrollOffset(int x) const
{
    return x + scrollOffset();
}

qreal TimelineMovableItem::mapFromFrameToScene(qreal x) const
{
    return TimelineConstants::sectionWidth + (x - timelineScene()->startFrame()) * rulerScaling() -
                              scrollOffset() + TimelineConstants::timelineLeftOffset;
}

qreal TimelineMovableItem::mapFromSceneToFrame(qreal x) const
{
    qreal x_no_offset = x - TimelineConstants::sectionWidth - TimelineConstants::timelineLeftOffset;
    return xPosScrollOffset(static_cast<int>(x_no_offset)) / timelineScene()->rulerScaling() + timelineScene()->startFrame();
}

void TimelineMovableItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void TimelineMovableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void TimelineMovableItem::setClampedXPosition(qreal x, qreal minimumWidth, qreal maximumWidth)
{
    if (x > minimumWidth) {
        if (x < maximumWidth)
            setRect(x, rect().y(), rect().width(), rect().height());
        else
            setRect(maximumWidth, rect().y(), rect().width(), rect().height());
    } else {
        setRect(minimumWidth, rect().y(), rect().width(), rect().height());
    }
}

TimelineMovableItem *TimelineMovableItem::cast(QGraphicsItem *item)
{
    return qgraphicsitem_cast<TimelineMovableItem *>(item);
}

TimelineMovableItem *TimelineMovableItem::topMoveableItem(
    const QList<QGraphicsItem *> &items)
{
    for (auto item : items)
        if (auto castedItem = TimelineMovableItem::cast(item))
            return castedItem;

    return nullptr;
}

void TimelineMovableItem::emitScrollOffsetChanged(QGraphicsItem *item)
{
    auto movableItem = TimelineMovableItem::cast(item);
    if (movableItem)
        movableItem->scrollOffsetChanged();
}

TimelineKeyframeItem *TimelineMovableItem::asTimelineKeyframeItem(QGraphicsItem *item)
{
    auto movableItem = TimelineMovableItem::cast(item);

    if (movableItem)
        return movableItem->asTimelineKeyframeItem();

    return nullptr;
}

qreal TimelineMovableItem::rulerScaling() const
{
    return static_cast<TimelineGraphicsScene *>(scene())->rulerScaling();
}

int TimelineMovableItem::type() const
{
    return Type;
}

TimelineGraphicsScene *TimelineMovableItem::timelineScene() const
{
    return static_cast<TimelineGraphicsScene *>(scene());
}

TimelineKeyframeItem *TimelineMovableItem::asTimelineKeyframeItem()
{
    return nullptr;
}

TimelineFrameHandle *TimelineMovableItem::asTimelineFrameHandle()
{
    return nullptr;
}
