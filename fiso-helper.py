from PyQt6.QtWidgets import QApplication
from src.app import UiMainWindow


def main():
    app = QApplication([])

    window = UiMainWindow()

    app.exec()


if __name__ == '__main__':
    main()
