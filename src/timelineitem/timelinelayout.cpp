#include "timelinelayout.h"
#include "timelineruler.h"
#include <QGraphicsLinearLayout>
TimelineLayout::TimelineLayout(TimelineGraphicsScene *scene, TimelineItem *parent)
{

}

TimelineLayout::~TimelineLayout()
{

}

qreal TimelineLayout::rulerWidth() const
{
    return ruler_->preferredWidth();
}

qreal TimelineLayout::rulerScaling() const
{
    return ruler_->rulerScaling();
}

qreal TimelineLayout::rulerDuration() const
{
    return ruler_->rulerDuration();
}

qreal TimelineLayout::startFrame() const
{
    return ruler_->startFrame();
}

qreal TimelineLayout::endFrame() const
{
    return ruler_->endFrame();
}
