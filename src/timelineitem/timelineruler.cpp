#include "timelineruler.h"
#include "../timelineutils/timelineconstants.h"
#include "../timelineutils/timelineutils.h"
TimelineRuler::TimelineRuler(TimelineItem* parent)
    :TimelineItem(parent)
{
    setPreferredHeight(TimelineConstants::rulerHeight);
    setMinimumHeight(TimelineConstants::rulerHeight);
    setMaximumHeight(TimelineConstants::rulerHeight);
    setZValue(10);
}

TimelineRuler* TimelineRuler::create(QGraphicsScene *scene, TimelineItem *parent)
{
    TimelineRuler* ruler = new TimelineRuler(parent);
    ruler->setMaximumHeight(TimelineConstants::rulerHeight);
   // ruler->createLeftTimecodeWidget(scene);
    return ruler;
}

void TimelineRuler::setRulerScaleFactor(int scaling)
{
    qreal blend = qreal(scaling) / 100.0;
    qreal width = size().width() - qreal(TimelineConstants::sectionWidth);
    qreal duration = rulerDuration();
    qreal offset = duration * 0.1;
    qreal maxCount = duration + offset;
    qreal minCount = width / qreal(TimelineConstants::keyFrameSize + 2 * TimelineConstants::keyFrameMargin);
    qreal count = maxCount < minCount ? maxCount : TimelineUtils::lerp(blend, minCount, maxCount);
    if(count > std::numeric_limits<qreal>::min() && count <= maxCount)
        scaling_ = width / count;
    else
        scaling_ = 1.0;
    update();
}

int TimelineRuler::rulerScaleFactor() const
{
    qreal width = size().width() - qreal(TimelineConstants::sectionWidth);
    qreal duraion = rulerDuration();
    qreal offset = duraion * 0.1;
    qreal maxCount = duraion + offset;
    qreal minCount = width / qreal(TimelineConstants::keyFrameSize + 2 * TimelineConstants::keyFrameMargin);
    if(maxCount < minCount) return -1;
    qreal rcount = width / scaling_;
    qreal rblend = TimelineUtils::reverseLerp(rcount, minCount, maxCount);
    int rfactor = std::round(rblend * 100);
    return TimelineUtils::clamp(rfactor, 0, 100);
}

void TimelineRuler::invalidateRulerSize()
{

}


qreal TimelineRuler::rulerScaling() const
{
    return scaling_;
}

qreal TimelineRuler::rulerDuration() const
{
    return duration_;
}

qreal TimelineRuler::durationViewportLength() const
{
    return duration_ * scaling_;
}

qreal TimelineRuler::startFrame() const
{
    return startFrame_;
}

qreal TimelineRuler::endFrame() const
{
    return endFrame_;
}

void TimelineRuler::setSizeHint(int width)
{
    const int rulerWidth = width;
    setPreferredWidth(rulerWidth);
    setMinimumWidth(rulerWidth);
    setMaximumWidth(rulerWidth);
}
