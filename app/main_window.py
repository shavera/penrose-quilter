import sys

from PyQt6.QtCore import QPoint, pyqtSignal
from PyQt6.QtGui import QDoubleValidator
from PyQt6.QtWidgets import (
    QApplication,
    QFormLayout,
    QGridLayout,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QMainWindow,
    QPushButton,
    QWidget,
)
from quilt_canvas import QuiltCanvas, QuiltView, WideRhomb

INITIAL_TILE_SIZE = 2.0
INITIAL_QUILT_WIDTH = 8.5
INITIAL_QUILT_HEIGHT = 11


class TileSelector(QWidget):
    """
    Widget to select which tile shape will be added to the canvas.

    Note, this is largely a placeholder for now.
    """

    def __init__(self, parent: QWidget | None = None):
        super().__init__(parent)
        self.tile_btn: list[QPushButton] = []
        self.layout = QHBoxLayout()
        self.setLayout(self.layout)
        self.tile_btn.append(QPushButton("Tile 1"))
        self.tile_btn.append(QPushButton("Tile 2"))
        self.layout.addWidget(self.tile_btn[0])
        self.layout.addWidget(self.tile_btn[1])


class SizeWidget(QWidget):
    """Widget to determine physical length scales"""

    tile_size_changed = pyqtSignal(float)
    quilt_height_changed = pyqtSignal(float)
    quilt_width_changed = pyqtSignal(float)

    class FloatEditor(QLineEdit):
        """A line edit that only accepts floats within some limits"""

        value_changed = pyqtSignal(float)

        def __init__(
            self,
            initial_value: float,
            min_val: float,
            max_val: float,
            decimals: int,
            parent: QWidget | None = None,
        ):
            super().__init__(parent)
            self.setValidator(
                QDoubleValidator(bottom=min_val, top=max_val, decimals=decimals)
            )
            self.setText(str(initial_value))
            self.editingFinished.connect(self.on_editing_finished)

        def value(self) -> float | None:
            return float(self.text()) if self.hasAcceptableInput() else None

        def on_editing_finished(self):
            self.value_changed.emit(self.value())

    def __init__(self, parent: QWidget | None = None):
        super().__init__(parent)
        self.layout = QFormLayout()
        self.setLayout(self.layout)

        self.tile_edit = SizeWidget.FloatEditor(INITIAL_TILE_SIZE, 0.0, 12.0, 4)
        self.tile_edit.value_changed.connect(self.tile_size_changed)
        self.layout.addRow(QLabel("Tile Size"), self.tile_edit)

        self.width_edit = SizeWidget.FloatEditor(INITIAL_QUILT_WIDTH, 0.0, 1200.0, 4)
        self.width_edit.value_changed.connect(self.quilt_width_changed)
        self.layout.addRow(QLabel("Quilt Width"), self.width_edit)

        self.height_edit = SizeWidget.FloatEditor(INITIAL_QUILT_HEIGHT, 0.0, 1200.0, 4)
        self.height_edit.value_changed.connect(self.quilt_height_changed)
        self.layout.addRow(QLabel("Quilt Height"), self.height_edit)

    def tile_size(self) -> float | None:
        return self.tile_edit.value()

    def quilt_width(self) -> float | None:
        return self.width_edit.value()

    def quilt_height(self) -> float | None:
        return self.height_edit.value()


class MainWindow(QMainWindow):
    """
    Main window of the application

    Laid out in a 2x2 grid.
    The upper left (main widget) view will be the quilt and pattern itself.
    Upper right will have some size selection. In the future, color selection will also
    likely go in this space.
    Lower left will enable a user to select tiles they will place.
    The lower right doesn't have an explicit purpose but is being used to track
    debug statements we may want to make.
    """

    def __init__(self):
        super().__init__()
        self.layout = QGridLayout()
        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)
        self.central_widget.setLayout(self.layout)

        # initialize widgets
        self.size_widget = SizeWidget()
        self.tile_selector = TileSelector()
        self.quilt_canvas = QuiltCanvas(
            tile_scale_in=self.size_widget.tile_size(),
            quilt_width_in=self.size_widget.quilt_width(),
            quilt_height_in=self.size_widget.quilt_height(),
        )
        self.quilt_view = QuiltView(self.quilt_canvas)

        self.coords_debug_label = QLabel()

        # add widgets to layout
        self.layout.addWidget(self.quilt_view, 0, 0)
        self.layout.addWidget(self.size_widget, 0, 1)
        self.layout.addWidget(self.tile_selector, 1, 0)
        self.layout.addWidget(self.coords_debug_label, 1, 1)

        # connect widgets
        self.size_widget.tile_size_changed.connect(self.quilt_canvas.set_tile_scale)
        self.size_widget.quilt_height_changed.connect(
            self.quilt_canvas.set_quilt_height
        )
        self.size_widget.quilt_width_changed.connect(self.quilt_canvas.set_quilt_width)

        # other initializations
        self.quilt_canvas.add_tile(
            WideRhomb(length_scale_in=self.size_widget.tile_size())
        )
        self.quilt_view.coordinates_changed.connect(self.update_debug_coords)

    def update_debug_coords(self, point: QPoint):
        self.coords_debug_label.setText(f"({point.x()}, {point.y()})")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    main_window = MainWindow()
    main_window.show()
    app.exec()
