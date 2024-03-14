# -*- coding: utf-8 -*-

from PyQt6.QtCore import QSize, Qt, QRect
from PyQt6.QtGui import QFont, QTextFormat
from PyQt6.QtWidgets import QMainWindow, QWidget, QGroupBox, QLabel, QFrame, QPushButton, QLineEdit

import logging


class UiMainWindow(QMainWindow):
    """
    Main app window
    """
    def __init__(self):
        super().__init__()

        # speaker list
        self.speakerList = list()

        # set main window title
        self.setWindowTitle("fiso-helper")

        # set main window size
        self.setFixedSize(QSize(200, 140))
        self.sizePolicy().setHorizontalStretch(0)
        self.sizePolicy().setVerticalStretch(0)

        self.setAnimated(True)

        # current speaker group
        self.currentSpeakerGroup = QGroupBox(self)
        self.currentSpeakerGroup.setObjectName("currentSpeakerGroup")
        self.currentSpeakerGroup.setTitle("Aktuelle Redner*in")
        self.currentSpeakerGroup.setGeometry(QRect(10, 10, 140, 80))

        # current speaker text label
        self.currentSpeakerLabel = QLabel(self)
        self.currentSpeakerLabel.setObjectName("currentSpeakerLabel")
        self.currentSpeakerLabel.setGeometry(QRect(10, 30, 140, 60))
        custom_font = QFont()
        custom_font.setPointSize(30)
        custom_font.setBold(True)
        self.currentSpeakerLabel.setFont(custom_font)
        # self.currentSpeakerLabel.setText("Aa")
        self.currentSpeakerLabel.setAlignment(Qt.AlignmentFlag.AlignCenter)

        # button to remove the current speaker
        self.removeSpeakerButton = QPushButton(self)
        self.removeSpeakerButton.setObjectName("removeSpeakerButton")
        self.removeSpeakerButton.setGeometry(QRect(160, 50, 30, 30))
        self.removeSpeakerButton.setText("-")

        self.removeSpeakerButton.clicked.connect(self.remove_speaker)

        # text field to add a speaker
        self.addSpeakerTextEdit = QLineEdit(self)
        self.addSpeakerTextEdit.setObjectName("addSpeakerTextEdit")
        self.addSpeakerTextEdit.setGeometry(QRect(10, 100, 100, 30))

        # button to add a speaker
        self.addSpeakerButton = QPushButton(self)
        self.addSpeakerButton.setObjectName("addSpeakerButton")
        self.addSpeakerButton.setGeometry(QRect(120, 100, 30, 30))
        self.addSpeakerButton.setText("+")

        self.addSpeakerButton.clicked.connect(self.add_speaker)

        self.show()

    def add_speaker(self):
        text = self.addSpeakerTextEdit.text()
        if len(text) > 1:
            self.addSpeakerTextEdit.setText("")
            self.speakerList.append(text[0].upper()+text[1].lower())
            self.currentSpeakerLabel.setText(self.speakerList[0])
        else:
            logging.warning("empty input or too short")

    def remove_speaker(self):
        if len(self.speakerList) > 1:
            self.speakerList.pop(0)
            self.currentSpeakerLabel.setText(self.speakerList[0])
        elif len(self.speakerList) == 1:
            self.speakerList.pop(0)
            self.currentSpeakerLabel.setText("")
        else:
            logging.warning("empty speaker list")
