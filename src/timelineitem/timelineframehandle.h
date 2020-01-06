#ifndef TIMELINEFRAMEHANDLE_H
#define TIMELINEFRAMEHANDLE_H

#include "timelinemovableitem.h"
#include "timelineitem.h"
#include <QGraphicsRectItem>
#include <QTimer>

class TimelineFrameHandle : public TimelineMovableItem
{
public:
    explicit TimelineFrameHandle(TimelineItem *parent = nullptr);

    void setHeight(int height);
    void setPosition(qreal frame);
    void setPositionInteractive(const QPointF &postion) override;
    void commitPosition(const QPointF &point) override;
    qreal position() const;
    TimelineFrameHandle *asTimelineFrameHandle() override;
protected:
    void scrollOffsetChanged() override;
    QPainterPath shape() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QPointF mapFromGlobal(const QPoint &pos) const;
    int computeScrollSpeed() const;

    void callSetClampedXPosition(double x);
    void scrollOutOfBounds();
    void scrollOutOfBoundsMax();
    void scrollOutOfBoundsMin();

private:
    qreal m_position = 0;
    QTimer m_timer;
};
#endif // TIMELINEFRAMEHANDLE_H
