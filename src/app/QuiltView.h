#pragma once

#include "QuiltCanvas.h"

#include <QGraphicsView>
#include <QPointer>

class QStateMachine;

class QuiltView : public QGraphicsView
{
    Q_OBJECT
public:
    using ConfigureStateMachineFn = std::function<QPointer<QStateMachine>(QuiltView*)>;
    // Note: Implemented in `QuiltViewConfigureStateMachine.cpp`
    static QPointer<QStateMachine> configureStateMachine(QuiltView* quiltView);

    explicit QuiltView(QWidget* parent = nullptr);

    ~QuiltView();

    void setCanvas(QPointer<QuiltCanvas> canvas);

    void resetView(double scale = 1.0);

signals:
    void coordinatesChanged(const QPoint& point);

private:
    void updateCoordinates(std::optional<QPoint> pos = std::nullopt);

    void zoom(int step);

    void wheelEvent(QWheelEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void leaveEvent(QEvent* event) override;

    QPointer<QuiltCanvas> canvas_{nullptr};

    QPointer<QStateMachine> stateMachine_{nullptr};

    static constexpr double kZoomScaleFactor{1.1};

    bool zoomPinned_{false};
    int zoomLevel_{0};
};
