#include "QuiltView.h"
#include "ViewStateMachine.h"

#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QWheelEvent>


QuiltView::QuiltView(QWidget* parent)
    : QGraphicsView{parent}
    , stateMachine_{new ViewStateMachine(this)}
{
    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(AnchorUnderMouse);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

QuiltView::~QuiltView() = default;

void QuiltView::setCanvas(QPointer<QuiltCanvas> canvas)
{
    canvas_ = canvas;
    setScene(canvas);
}

void QuiltView::resetView(double scale)
{
    const auto& rect = canvas_->sceneRect();
    setSceneRect(rect);
    scale = fmax(1.0, scale);
    if (scale == 1){
        zoomLevel_ = 0;
    }
    const auto unity = transform().mapRect(QRectF{0,0,1,1});
    this->scale(1/unity.width(), 1/unity.height());
    const auto& viewRect = viewport()->rect();
    const auto& sceneRect = transform().mapRect(rect);
    const auto factor = fmin(viewRect.width()/sceneRect.width(), viewRect.height()/sceneRect.height()) + scale;
    this->scale(factor, factor);
    if(!zoomPinned_){
        centerOn(sceneRect.center());
    }
    updateCoordinates();
}

void QuiltView::updateCoordinates(std::optional<QPoint> pos)
{
    if(std::nullopt == pos){
        pos = mapFromGlobal(QCursor::pos());
    }
    const auto& point = this->mapToScene(*pos).toPoint();
    emit coordinatesChanged(point);
}

void QuiltView::zoom(int step)
{
    // TODO: Come back to this section and see if it makes any sense.
    // Just copied from python script
    // Wheel event reports integer steps in 1/8 degree increments;
    // 120 steps to a 15 degree 'click'
    // why can't zoom be negative, maybe it's okay if it is?
    const int zoom = std::max(0, zoomLevel_ + step);
    if(zoom == zoomLevel_){
        return;
    }
    zoomLevel_ = zoom;
    if (zoomLevel_ <= 0){
        resetView();
        return;
    }
    const double factor = std::pow(kZoomScaleFactor, step);
    scale(factor, factor);
}

void QuiltView::wheelEvent(QWheelEvent* event)
{
    const auto delta = event->angleDelta().y();
    if(delta == 0){
        return;
    }
    static constexpr int kWheelDeltaToStep{120};
    const int step = delta / kWheelDeltaToStep;
    zoom(step);
    QGraphicsView::wheelEvent(event);
}

void QuiltView::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);
    resetView();
}

void QuiltView::mouseMoveEvent(QMouseEvent *event)
{
    updateCoordinates(event->position().toPoint());
    QGraphicsView::mouseMoveEvent(event);
}

void QuiltView::leaveEvent(QEvent *event)
{
    emit coordinatesChanged(QPoint{});
    QGraphicsView::leaveEvent(event);
}
