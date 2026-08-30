import sys

from PyQt6.QtGui import QDoubleValidator
from PyQt6.QtWidgets import (
    QApplication,
    QFormLayout,
    QGridLayout,
    QHBoxLayout,
    QLineEdit,
    QMainWindow,
    QPushButton,
    QWidget,
)
from quilt_canvas import QuiltView


class TileSelector(QWidget):
    def __init__(self, parent: QWidget | None=None):
        super().__init__(parent)
        self.tile_btn: list[QPushButton] = []
        self.layout = QHBoxLayout()
        self.setLayout(self.layout)
        self.tile_btn.append(QPushButton("Tile 1"))
        self.tile_btn.append(QPushButton("Tile 2"))
        self.layout.addWidget(self.tile_btn[0])
        self.layout.addWidget(self.tile_btn[1])


class SizeWidget(QWidget):
    def __init__(self, parent: QWidget | None=None):
        super().__init__(parent)
        self.layout = QFormLayout()
        self.setLayout(self.layout)
        self.double_validator = QDoubleValidator(bottom=0.0, top=1200.0, decimals=4)
        self.tile_edit = QLineEdit()
        self.tile_edit.setValidator(QDoubleValidator(self.double_validator))
        self.height_edit = QLineEdit()
        self.height_edit.setValidator(QDoubleValidator(self.double_validator))
        self.width_edit = QLineEdit()
        self.width_edit.setValidator(QDoubleValidator(self.double_validator))
        self.layout.addRow("Tile Size:", self.tile_edit)
        self.layout.addRow("Quilt Width:", self.height_edit)
        self.layout.addRow("Quilt Height:", self.width_edit)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.layout = QGridLayout()
        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)
        self.central_widget.setLayout(self.layout)

        self.quilt_view = QuiltView()
        self.layout.addWidget(self.quilt_view, 0, 0)

        self.size_widget = SizeWidget()
        self.layout.addWidget(self.size_widget, 0, 1)

        self.tile_selector = TileSelector()
        self.layout.addWidget(self.tile_selector, 1, 0)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    main_window = MainWindow()
    main_window.show()
    app.exec()