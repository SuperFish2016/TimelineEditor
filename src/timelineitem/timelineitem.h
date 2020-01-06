#ifndef TIMELINEITEM_H
#define TIMELINEITEM_H
#include <QGraphicsWidget>
class TimelineGraphicsScene;

class TimelineItem : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit TimelineItem(TimelineItem *parent = nullptr);
    static void drawLine(QPainter *painter, qreal x1, qreal y1, qreal x2, qreal y2);
    TimelineGraphicsScene *timelineScene() const;
};
#endif // TIMELINEITEM_H
