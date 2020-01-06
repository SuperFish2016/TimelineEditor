#include "timelineitem.h"
#include "../timelinegraphicsscene.h"
#include <QPainter>
TimelineItem::TimelineItem(TimelineItem *parent)
    : QGraphicsWidget(parent)
{

}

TimelineGraphicsScene *TimelineItem::timelineScene() const
{
    return static_cast<TimelineGraphicsScene *>(scene());
}

void TimelineItem::drawLine(QPainter *painter, qreal x1, qreal y1, qreal x2, qreal y2)
{
    painter->drawLine(QPointF(x1 + 0.5, y1 + 0.5), QPointF(x2 + 0.5, y2 + 0.5));
}
