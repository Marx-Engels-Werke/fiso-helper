from PyQt6.QtWidgets import QApplication

from src.app import UiMainWindow

app = QApplication([])

window = UiMainWindow()

app.exec()
