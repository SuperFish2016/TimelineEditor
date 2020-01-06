#ifndef TIMELINEABSTRACTTOOL_H
#define TIMELINEABSTRACTTOOL_H
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

class TimelineGraphicsScene;
class TimelineToolDelegate;
class TimelineMovableItem;

class TimelineAbstractTool
{
public:
    enum class ToolType{MOVE, SELECT};
public:
    explicit TimelineAbstractTool(TimelineGraphicsScene* scene);
    explicit TimelineAbstractTool(TimelineGraphicsScene* scene, TimelineToolDelegate* delegate);
    virtual ~TimelineAbstractTool();

    virtual void mousePressEvent(TimelineMovableItem       *item, QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseMoveEvent(TimelineMovableItem        *item, QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(TimelineMovableItem     *item, QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseDoubleClickEvent(TimelineMovableItem *item, QGraphicsSceneMouseEvent *event) = 0;

    virtual void keyPressEvent(QKeyEvent    *keyEvent) = 0;
    virtual void keyReleaseEvent(QKeyEvent  *keyEvent) = 0;

    TimelineGraphicsScene* scene()    const;
    TimelineToolDelegate*  delegate() const;
    TimelineMovableItem *currentItem() const;
    QPointF startPosition() const;
private:
    TimelineGraphicsScene* scene_;
    TimelineToolDelegate*  tool_delegate_;
};

#endif // TIMELINEABSTRACTTOOL_H
