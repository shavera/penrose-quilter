import math

from PyQt6.QtCore import QObject, QPointF
from PyQt6.QtGui import QPolygonF
from PyQt6.QtWidgets import QGraphicsScene, QGraphicsView, QWidget

LENGTH_SCALE = 64

class Rhomb(QPolygonF):
    def __init__(self, narrow_angle_deg: float, length_scale: float = LENGTH_SCALE):
        narrow_angle_rad = narrow_angle_deg * math.pi / 180.0
        x_offset = length_scale * math.cos(narrow_angle_rad)
        y_offset = length_scale * math.sin(narrow_angle_rad)
        points = [
            QPointF(0, 0),
            QPointF(length_scale, 0),
            QPointF(length_scale + x_offset, y_offset),
            QPointF(x_offset, y_offset),
            QPointF(0, 0)
        ]
        super().__init__(points)

class ThinRhomb(Rhomb):
    def __init__(self, length_scale: float = LENGTH_SCALE):
        super().__init__(narrow_angle_deg=36.0, length_scale=length_scale)


class WideRhomb(Rhomb):
    def __init__(self, length_scale: float = LENGTH_SCALE):
        super().__init__(narrow_angle_deg=72.0, length_scale=length_scale)


class QuiltCanvas(QGraphicsScene):
    def __init__(self, parent: QObject | None = None):
        super().__init__(parent=parent)


class QuiltView(QGraphicsView):
    def __init__(self, parent: QWidget | None = None, quilt_canvas: QuiltCanvas | None = None):
        super().__init__(parent=parent)
        self.quilt_canvas = quilt_canvas if quilt_canvas else QuiltCanvas(self)
