#include "timelinetooldelegate.h"
#include "../timelineconstants.h"
TimelineToolDelegate::TimelineToolDelegate(TimelineGraphicsScene *scene)
    : scene_(scene), start_(),
      move_tool_(new TimelineMoveTool(scene, this)),
      select_tool_(new TimelineSelectionTool(scene, this))
{

}

void TimelineToolDelegate::mousePressEvent(TimelineMovableAbstractItem *item, QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton && hitCanvas(event)) {
        start_ = event->scenePos();
        if (item)
        {
            setItem(item, event->modifiers());
            current_tool_ = move_tool_.get();
        }
        else
        {
            current_tool_ = select_tool_.get();
        }
    }
    else {
        current_tool_ = nullptr;
    }
    if (current_tool_)
        current_tool_->mousePressEvent(item, event);
}

void TimelineToolDelegate::mouseMoveEvent(TimelineMovableAbstractItem *item, QGraphicsSceneMouseEvent *event)
{
    if (current_tool_)
        current_tool_->mouseMoveEvent(item, event);
}

void TimelineToolDelegate::mouseReleaseEvent(TimelineMovableAbstractItem *item, QGraphicsSceneMouseEvent *event)
{
    if (current_tool_)
        current_tool_->mouseReleaseEvent(item, event);
    reset();
}

void TimelineToolDelegate::mouseDoubleClickEvent(TimelineMovableAbstractItem *item, QGraphicsSceneMouseEvent *event)
{
    if (hitCanvas(event)) {
        current_tool_ = select_tool_.get();
        current_tool_->mouseDoubleClickEvent(item, event);
    }
    reset();
}

void TimelineToolDelegate::clearSelection()
{
//    if (auto *keyframe = TimelineMovableAbstractItem::asTimelineKeyframeItem(m_item))
//        keyframe->setHighlighted(false);
    current_item_ = nullptr;
}

void TimelineToolDelegate::setItem(TimelineMovableAbstractItem *item, const Qt::KeyboardModifiers &modifiers)
{
    if (item) {
        setItem(nullptr);
//        if (auto *keyframe = TimelineMovableAbstractItem::asTimelineKeyframeItem(item)) {
//            if (modifiers.testFlag(Qt::ControlModifier)) {
//                if (scene_->isKeyframeSelected(keyframe))
//                    scene_->selectKeyframes(SelectionMode::Remove, {keyframe});
//                else
//                    scene_->selectKeyframes(SelectionMode::Add, {keyframe});
//            } else {
//                if (!scene_->isKeyframeSelected(keyframe))
//                    scene_->selectKeyframes(SelectionMode::New, {keyframe});
//            }
//        }

    } else if (current_item_) {
//        if (auto *keyframe = TimelineMovableAbstractItem::asTimelineKeyframeItem(current_item_))
//            if (!scene_->isKeyframeSelected(keyframe))
//                keyframe->setHighlighted(false);
    }
    current_item_ = item;
}

bool TimelineToolDelegate::hitCanvas(QGraphicsSceneMouseEvent *event)
{
    return event->scenePos().x() > TimelineConstants::sectionWidth;
}

void TimelineToolDelegate::reset()
{
    setItem(nullptr);
    current_tool_ = nullptr;
    start_ = QPointF();
}
