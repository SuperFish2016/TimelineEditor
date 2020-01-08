#include "timelineframehandle.h"
#include "../timelinegraphicsscene.h"
#include "timelineconstants.h"
#include "timelineutils.h"
#include <QApplication>
#include <QPainter>
#include <QCursor>
#include <QGraphicsView>
TimelineFrameHandle::TimelineFrameHandle(TimelineItem *parent)
    : TimelineMovableItem(parent)
{
    static const QColor color = Qt::red;//Theme::getColor(Theme::IconsWarningToolBarColor);
    setBrush(color);
    setPen(color);

    setRect(0, 0, TimelineConstants::rulerHeight, TimelineConstants::rulerHeight);
    setZValue(40);
    setCursor(Qt::ClosedHandCursor);

    m_timer.setSingleShot(true);
    m_timer.setInterval(15);
    QObject::connect(&m_timer, &QTimer::timeout, [this]() {
        if (QApplication::mouseButtons() == Qt::LeftButton)
            scrollOutOfBounds();
    });
}

void TimelineFrameHandle::setHeight(int height)
{
    setRect(rect().x(), rect().y(), rect().width(), height);
}

void TimelineFrameHandle::setPosition(qreal frame)
{
    const qreal scenePos = mapFromFrameToScene(frame);
    QRectF newRect(scenePos - rect().width() / 2, rect().y(), rect().width(), rect().height());

    if (!qFuzzyCompare(newRect.x(), rect().x())) {
        setRect(newRect);
    }
    m_position = frame;
}

void TimelineFrameHandle::setPositionInteractive(const QPointF &position)
{
    const double width = timelineScene()->width();

    if (position.x() > width) {
        callSetClampedXPosition(width - (rect().width() / 2) - 1);
        m_timer.start();
    } else if (position.x() < TimelineConstants::sectionWidth) {
        callSetClampedXPosition(TimelineConstants::sectionWidth);
        m_timer.start();
    } else {
        callSetClampedXPosition(position.x() - rect().width() / 2);
        const qreal frame = std::round(mapFromSceneToFrame(rect().center().x()));
        timelineScene()->commitCurrentFrame(frame);
    }
}

void TimelineFrameHandle::commitPosition(const QPointF &point)
{
    setPositionInteractive(point);
}

qreal TimelineFrameHandle::position() const
{
    return m_position;
}

TimelineFrameHandle *TimelineFrameHandle::asTimelineFrameHandle()
{
    return this;
}

void TimelineFrameHandle::scrollOffsetChanged()
{
    setPosition(position());
}

QPainterPath TimelineFrameHandle::shape() const
{
    QPainterPath path;
    QRectF rect = boundingRect();
    rect.setHeight(TimelineConstants::sectionHeight);
    rect.adjust(-4, 0, 4, 0);
    path.addEllipse(rect);
    return path;
}

static int devicePixelWidth(const QPixmap &pixmap)
{
    return static_cast<int>(pixmap.width() / pixmap.devicePixelRatioF());
}

static int devicePixelHeight(const QPixmap &pixmap)
{
    return static_cast<int>(pixmap.height() / pixmap.devicePixelRatioF());
}

void TimelineFrameHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    static const QPixmap playHead; //= TimelineIcons::PLAYHEAD.pixmap();

    static const int pixmapHeight = devicePixelHeight(playHead);
    static const int pixmapWidth = devicePixelWidth(playHead);

    if (rect().x() < TimelineConstants::sectionWidth - rect().width() / 2)
        return;

    painter->save();
    painter->setOpacity(0.8);
    const qreal center = rect().width() / 2 + rect().x();

    painter->setPen(pen());

    auto offsetTop = pixmapHeight - 7;
    TimelineItem::drawLine(painter, center, offsetTop, center, rect().height() - 1);

    const QPointF pmTopLeft(center - pixmapWidth / 2, -4.);
    painter->drawPixmap(pmTopLeft, playHead);

    painter->restore();
}

QPointF TimelineFrameHandle::mapFromGlobal(const QPoint &pos) const
{
    for (auto *view : timelineScene()->views()) {
        if (view->objectName() == "SceneView") {
            auto graphicsViewCoords = view->mapFromGlobal(pos);
            auto sceneCoords = view->mapToScene(graphicsViewCoords);
            return sceneCoords;
        }
    }
    return {};
}

int TimelineFrameHandle::computeScrollSpeed() const
{
    const double mouse = mapFromGlobal(QCursor::pos()).x();
    const double width = timelineScene()->width();

    const double acc = mouse > width ? mouse - width
                                     : double(TimelineConstants::sectionWidth) - mouse;
    const double delta = TimelineUtils::clamp<double>(acc, 0., 200.);
    const double blend = TimelineUtils::reverseLerp(delta, 0., 200.);
    const double factor = TimelineUtils::lerp<double>(blend, 5, 20);

    if (mouse > width)
        return scrollOffset() + std::round(factor);
    else
        return scrollOffset() - std::round(factor);

    return 0;
}

void TimelineFrameHandle::callSetClampedXPosition(double x)
{
    const int minimumWidth = TimelineConstants::sectionWidth + TimelineConstants::timelineLeftOffset
                             - rect().width() / 2;
    const int maximumWidth = minimumWidth
                             + timelineScene()->rulerDuration() * timelineScene()->rulerScaling()
                             - scrollOffset();

    setClampedXPosition(x, minimumWidth, maximumWidth);
}

// Auto scroll when dragging playhead out of bounds.
void TimelineFrameHandle::scrollOutOfBounds()
{
    const double width = timelineScene()->width();
    const double mouse = mapFromGlobal(QCursor::pos()).x();

    if (mouse > width)
        scrollOutOfBoundsMax();
    else if (mouse < TimelineConstants::sectionWidth)
        scrollOutOfBoundsMin();
}

void TimelineFrameHandle::scrollOutOfBoundsMax()
{
    const double width = timelineScene()->width();
    if (QApplication::mouseButtons() == Qt::LeftButton) {
        const double frameWidth = timelineScene()->rulerScaling();
        const double upperThreshold = width - frameWidth;

        if (rect().center().x() > upperThreshold) {
            timelineScene()->setScrollOffset(computeScrollSpeed());
            timelineScene()->invalidateScrollbar();
        }

        callSetClampedXPosition(width - (rect().width() / 2) - 1);
        m_timer.start();
    } else {
        // Mouse release
        callSetClampedXPosition(width - (rect().width() / 2) - 1);

        const int frame = std::floor(mapFromSceneToFrame(rect().center().x()));
        const int ef = timelineScene()->endFrame();
        timelineScene()->commitCurrentFrame(frame <= ef ? frame : ef);
    }
}

void TimelineFrameHandle::scrollOutOfBoundsMin()
{
    if (QApplication::mouseButtons() == Qt::LeftButton) {
        auto offset = computeScrollSpeed();

        if (offset >= 0)
            timelineScene()->setScrollOffset(offset);
        else
            timelineScene()->setScrollOffset(0);

        timelineScene()->invalidateScrollbar();

        callSetClampedXPosition(TimelineConstants::sectionWidth);
        m_timer.start();
    } else {
        // Mouse release
        callSetClampedXPosition(TimelineConstants::sectionWidth);

        int frame = mapFromSceneToFrame(rect().center().x());

        const int sframe = timelineScene()->startFrame();
        if (frame != sframe) {
            const qreal framePos = mapFromFrameToScene(frame);

            if (framePos
                <= (TimelineConstants::sectionWidth + TimelineConstants::timelineLeftOffset))
                frame++;
        }

        timelineScene()->commitCurrentFrame(frame >= sframe ? frame : sframe);
    }
}
