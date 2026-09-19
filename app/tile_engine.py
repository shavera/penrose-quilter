from PyQt6.QtWidgets import QGraphicsItem, QGraphicsPolygonItem


class ActiveTile(QGraphicsPolygonItem):
  def __init__(self, parent: QGraphicsItem | None = None):
    super().__init__(parent=parent)
    


class Blob(QGraphicsPolygonItem):
  def __init__(self, parent: QGraphicsItem | None = None):
    super().__init__(parent=parent)
    self.internal_items: list[QGraphicsPolygonItem] = []
