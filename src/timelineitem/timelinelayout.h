#ifndef TIMELINELAYOUT_H
#define TIMELINELAYOUT_H

#include "timelineitem.h"
class QGraphicsLinearLayout;
class TimelineRuler;
class TimelineLayout : public TimelineItem
{
    Q_OBJECT
public:
    TimelineLayout(TimelineGraphicsScene* scene, TimelineItem* parent = nullptr);
    ~TimelineLayout();

    qreal rulerWidth() const;
    qreal rulerScaling() const;
    qreal rulerDuration() const;
    qreal startFrame() const;
    qreal endFrame() const;
signals:
    void rulerClicked(const QPointF& pos);
    void scaleFactorChanged(int factor);
private:
    QGraphicsLinearLayout* linearLayout_;
    TimelineRuler* ruler_;
};

#endif // TIMELINELAYOUT_H
