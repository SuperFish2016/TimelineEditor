#include "timelinegraphicsscene.h"
#include "timelinewidget.h"
TimelineGraphicsScene::TimelineGraphicsScene(TimelineWidget *parent)
    : QGraphicsScene(parent)
{

}

TimelineGraphicsScene::~TimelineGraphicsScene()
{

}

qreal TimelineGraphicsScene::rulerScaling() const
{

}

int TimelineGraphicsScene::rulerWidth() const
{

}

qreal TimelineGraphicsScene::rulerDuration() const
{

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

}

qreal TimelineGraphicsScene::endFrame() const
{

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
