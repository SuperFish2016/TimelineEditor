#ifndef TIMELINEGRAPHICSSCENE_H
#define TIMELINEGRAPHICSSCENE_H

#include <QGraphicsScene>
class TimelineWidget;
class TimelineLayout;
class TimelineGraphicsScene : public QGraphicsScene
{
public:
    TimelineGraphicsScene(TimelineWidget* parent);
    ~TimelineGraphicsScene() override;

    qreal rulerScaling() const;
    int rulerWidth() const;
    qreal rulerDuration() const;

    int scrollOffset() const;
    void setScrollOffset(int offset);

    qreal startFrame() const;
    qreal endFrame() const;

    void commitCurrentFrame(qreal frame);

    void invalidateScrollbar();
private:
    TimelineLayout* layout_;
};

#endif // TIMELINEGRAPHICSSCENE_H
