#include "timelineabstracttool.h"
#include "timelinetooldelegate.h"
TimelineAbstractTool::TimelineAbstractTool(TimelineGraphicsScene *scene)
    : scene_(scene), tool_delegate_(nullptr)
{

}

TimelineAbstractTool::TimelineAbstractTool(TimelineGraphicsScene *scene, TimelineToolDelegate *delegate)
    : scene_(scene), tool_delegate_(delegate)
{

}

TimelineAbstractTool::~TimelineAbstractTool() = default;

TimelineGraphicsScene *TimelineAbstractTool::scene() const
{
    return scene_;
}

TimelineToolDelegate *TimelineAbstractTool::delegate() const
{
    return tool_delegate_;
}

QPointF TimelineAbstractTool::startPosition() const
{
    return tool_delegate_->startPoint();
}

TimelineMovableAbstractItem *TimelineAbstractTool::currentItem() const
{
    return tool_delegate_->item();
}
