#pragma once

#include "QuiltCanvas.h"

#include <QGraphicsView>
#include <QPointer>

class QuiltView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QuiltView(QWidget* parent = nullptr);

    void setCanvas(QPointer<QuiltCanvas> canvas);

    void resetView(double scale = 1.0);

signals:
    void coordinatesChanged(const QPoint& point);

private:
    void updateCoordinates(std::optional<QPoint> pos = std::nullopt);

    void zoom(int step);

    void wheelEvent(QWheelEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;

    void toggleDragMode();

    void mouseMoveEvent(QMouseEvent* event) override;

    void leaveEvent(QEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;

    void keyReleaseEvent(QKeyEvent* event) override;

    QPointer<QuiltCanvas> canvas_{nullptr};

    static constexpr double kZoomScaleFactor{1.1};

    bool zoomPinned_{false};
    int zoomLevel_{0};
};
