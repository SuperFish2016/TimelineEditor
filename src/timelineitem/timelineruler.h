#ifndef TIMELINERULER_H
#define TIMELINERULER_H
#include "timelineitem.h"

class TimelineRuler : public TimelineItem
{
    Q_OBJECT
public:
    static TimelineRuler* create(QGraphicsScene* scene, TimelineItem* parent);

    void setRulerScaleFactor(int scaling);
    int  rulerScaleFactor() const;
    void invalidateRulerSize();

    qreal rulerScaling() const;
    qreal rulerDuration() const;
    qreal durationViewportLength() const;
    qreal startFrame() const;
    qreal endFrame() const;
    void  setSizeHint(int width);
signals:
    void rulerClicked(const QPointF& pos);
    void scaleFactorChanged(int scale);
private:
    TimelineRuler(TimelineItem* parent = nullptr);
    qreal duration_ = 1500;
    qreal scaling_ = 1;
    qreal startFrame_ = 0;
    qreal endFrame_ = 2000;
};

#endif // TIMELINERULER_H
