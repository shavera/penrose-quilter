from PyQt6.QtCore import QObject
from PyQt6.QtWidgets import QGraphicsScene, QGraphicsView, QWidget


class QuiltCanvas(QGraphicsScene):
    def __init__(self, parent: QObject | None = None):
        super().__init__(parent=parent)


class QuiltView(QGraphicsView):
    def __init__(self, parent: QWidget | None = None, quilt_canvas: QuiltCanvas | None = None):
        super().__init__(parent=parent)
        self.quilt_canvas = quilt_canvas if quilt_canvas else QuiltCanvas(self)