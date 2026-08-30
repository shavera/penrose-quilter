import math

from PyQt6.QtCore import QObject, QPoint, QPointF, QRectF, QSizeF, Qt, pyqtSignal
from PyQt6.QtGui import QCursor, QKeyEvent, QMouseEvent, QPolygonF
from PyQt6.QtWidgets import QGraphicsScene, QGraphicsView, QWidget

PX_TO_IN_SCALE = 64.0


class Rhomb(QPolygonF):
    def __init__(self, narrow_angle_deg: float, length_scale_px: float):
        narrow_angle_rad = narrow_angle_deg * math.pi / 180.0
        x_offset = length_scale_px * math.cos(narrow_angle_rad)
        y_offset = length_scale_px * math.sin(narrow_angle_rad)
        points = [
            QPointF(0, 0),
            QPointF(length_scale_px, 0),
            QPointF(length_scale_px + x_offset, y_offset),
            QPointF(x_offset, y_offset),
            QPointF(0, 0),
        ]
        super().__init__(points)


class ThinRhomb(Rhomb):
    def __init__(self, length_scale_in: float):
        super().__init__(
            narrow_angle_deg=36.0, length_scale_px=length_scale_in * PX_TO_IN_SCALE
        )


class WideRhomb(Rhomb):
    def __init__(self, length_scale_in: float):
        super().__init__(
            narrow_angle_deg=72.0, length_scale_px=length_scale_in * PX_TO_IN_SCALE
        )


class QuiltCanvas(QGraphicsScene):
    def __init__(
        self,
        tile_scale_in: float,
        quilt_width_in: float,
        quilt_height_in: float,
        parent: QObject | None = None,
    ):
        super().__init__(parent=parent)
        self.tile_scale_px = PX_TO_IN_SCALE * tile_scale_in
        self.quilt_width_px = PX_TO_IN_SCALE * quilt_width_in
        self.quilt_height_px = PX_TO_IN_SCALE * quilt_height_in

        border_rect = self._quilt_border_rect()
        self.quilt_border = self.addRect(border_rect)

        self.setSceneRect(self._scene_border_rect(border_rect.topLeft()))

    def _scene_border_rect(self, quilt_top_left: QPointF) -> QRectF:
        scene_top_left = QPointF(
            quilt_top_left.x() - self.tile_scale_px,
            quilt_top_left.y() - self.tile_scale_px,
        )
        return QRectF(
            scene_top_left,
            (
                QSizeF(
                    self.quilt_width_px + self.tile_scale_px * 2,
                    self.quilt_height_px + self.tile_scale_px * 2,
                )
            ),
        )

    def _quilt_border_rect(self) -> QRectF:
        quilt_top_left = QPointF(-self.quilt_width_px / 2, -self.quilt_height_px / 2)
        return QRectF(
            quilt_top_left,
            (QSizeF(self.quilt_width_px, self.quilt_height_px)),
        )

    def _update_boundaries(self):
        quilt_rect = self._quilt_border_rect()
        self.quilt_border.setRect(quilt_rect)
        self.setSceneRect(self._scene_border_rect(quilt_rect.topLeft()))

    def add_tile(self, tile: Rhomb):
        self.addPolygon(tile)

    def set_tile_scale(self, scale_in: float):
        self.tile_scale_px = PX_TO_IN_SCALE * scale_in
        self._update_boundaries()

    def set_quilt_width(self, width_in: float):
        self.quilt_width_px = PX_TO_IN_SCALE * width_in
        self._update_boundaries()

    def set_quilt_height(self, height_in: float):
        self.quilt_height_px = PX_TO_IN_SCALE * height_in
        self._update_boundaries()


class QuiltView(QGraphicsView):
    coordinates_changed = pyqtSignal(QPoint)
    ZOOM_SCALE_FACTOR = 1.1

    def __init__(self, quilt_canvas: QuiltCanvas, parent: QWidget | None = None):
        super().__init__(quilt_canvas, parent=parent)
        self.quilt_canvas = quilt_canvas
        self._zoom = 0
        self._pinned = False
        self.setTransformationAnchor(QGraphicsView.ViewportAnchor.AnchorUnderMouse)
        self.setResizeAnchor(QGraphicsView.ViewportAnchor.AnchorUnderMouse)
        self.setVerticalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)

    def reset_view(self, scale: float = 1.0):
        rect = self.quilt_canvas.sceneRect()
        self.setSceneRect(rect)
        if (scale := max(1.0, scale)) == 1:
            self._zoom = 0
        unity = self.transform().mapRect(QRectF(0, 0, 1, 1))
        self.scale(1 / unity.width(), 1 / unity.height())
        view_rect = self.viewport().rect()
        scene_rect = self.transform().mapRect(rect)
        factor = (
            min(
                view_rect.width() / scene_rect.width(),
                view_rect.height() / scene_rect.height(),
            )
            * scale
        )
        self.scale(factor, factor)
        if not self.zoom_pinned():
            self.centerOn(scene_rect.center())
        self.update_coordinates()

    def zoom_level(self):
        return self._zoom

    def zoom_pinned(self):
        return self._pinned

    def set_zoom_pinned(self, enable):
        self._pinned = bool(enable)

    def zoom(self, step):
        zoom = max(0, self._zoom + (step := int(step)))
        if zoom != self._zoom:
            self._zoom = zoom
            if self._zoom > 0:
                if step > 0:
                    factor = self.ZOOM_SCALE_FACTOR**step
                else:
                    factor = 1 / self.ZOOM_SCALE_FACTOR ** abs(step)
                self.scale(factor, factor)
            else:
                self.reset_view()

    def wheelEvent(self, event):
        delta = event.angleDelta().y()
        self.zoom(delta and delta // abs(delta))

    def resizeEvent(self, event):
        super().resizeEvent(event)
        self.reset_view()

    def toggle_drag_mode(self):
        if self.dragMode() == QGraphicsView.DragMode.ScrollHandDrag:
            self.setDragMode(QGraphicsView.DragMode.NoDrag)
        else:
            self.setDragMode(QGraphicsView.DragMode.ScrollHandDrag)

    def update_coordinates(self, pos=None):
        if pos is None:
            pos = self.mapFromGlobal(QCursor.pos())
        point = self.mapToScene(pos).toPoint()
        self.coordinates_changed.emit(point)

    def mouseMoveEvent(self, event: QMouseEvent):
        self.update_coordinates(event.position().toPoint())
        super().mouseMoveEvent(event)

    def leaveEvent(self, event):
        self.coordinates_changed.emit(QPoint())
        super().leaveEvent(event)

    def keyPressEvent(self, event: QKeyEvent):
        if event.key() == Qt.Key.Key_Alt:
            self.setDragMode(QGraphicsView.DragMode.ScrollHandDrag)
        elif event.key() == Qt.Key.Key_Shift:
            self.setDragMode(QGraphicsView.DragMode.RubberBandDrag)
        super().keyPressEvent(event)

    def keyReleaseEvent(self, event: QKeyEvent):
        if event.key() == Qt.Key.Key_Alt:
            self.setDragMode(QGraphicsView.DragMode.NoDrag)
        elif event.key() == Qt.Key.Key_Shift:
            self.setDragMode(QGraphicsView.DragMode.RubberBandDrag)
        super().keyReleaseEvent(event)
