#include "timelinegraphicsscene.h"
#include "timelinewidget.h"
#include "../timelineitem/timelinelayout.h"
TimelineGraphicsScene::TimelineGraphicsScene(TimelineWidget *parent)
    : QGraphicsScene(parent)
{

}

TimelineGraphicsScene::~TimelineGraphicsScene()
{

}

qreal TimelineGraphicsScene::rulerScaling() const
{
    return layout_->rulerScaling();
}

int TimelineGraphicsScene::rulerWidth() const
{
    return layout_->rulerWidth();
}

qreal TimelineGraphicsScene::rulerDuration() const
{
    return layout_->rulerDuration();
}

int TimelineGraphicsScene::scrollOffset() const
{
    return 24;
}

void TimelineGraphicsScene::setScrollOffset(int offset)
{
//    m_scrollOffset = offset;
//    emitScrollOffsetChanged();
//    update();
}

qreal TimelineGraphicsScene::startFrame() const
{
    return layout_->startFrame();
}

qreal TimelineGraphicsScene::endFrame() const
{
    return layout_->endFrame();
}

void TimelineGraphicsScene::commitCurrentFrame(qreal frame)
{

//    QmlTimeline timeline(timelineModelNode());

//    if (timeline.isValid()) {
//        frame = setCurrenFrame(timeline, qRound(frame));
//        timeline.modelNode().setAuxiliaryData("currentFrame@NodeInstance", qRound(frame));
//        invalidateCurrentValues();
//    }
}

void TimelineGraphicsScene::invalidateScrollbar()
{

}
