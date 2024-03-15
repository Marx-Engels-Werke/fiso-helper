# -*- coding: utf-8 -*-

from PyQt6.QtCore import QSize, Qt, QRect
from PyQt6.QtGui import QFont, QTextFormat, QColor
from PyQt6.QtWidgets import QMainWindow, QWidget, QGroupBox, QLabel, QFrame, QPushButton, QLineEdit, QListWidget, \
    QListWidgetItem

import logging


class UiMainWindow(QMainWindow):
    """
    Main app window
    """
    def __init__(self):
        super().__init__()

        # speaker list
        # self.speakerList = list()
        # self.presentList = list()

        # set main window title
        self.setWindowTitle("fiso-helper")

        # set main window size
        self.setFixedSize(QSize(200, 380))
        self.sizePolicy().setHorizontalStretch(0)
        self.sizePolicy().setVerticalStretch(0)

        self.setAnimated(True)

        # current speaker group
        self.currentSpeakerGroup = QGroupBox(self)
        self.currentSpeakerGroup.setObjectName("currentSpeakerGroup")
        self.currentSpeakerGroup.setTitle("Aktuelle Redner*in")
        self.currentSpeakerGroup.setGeometry(QRect(10, 10, 140, 80))

        # current speaker name
        self.currentSpeakerList = QListWidget(self)
        self.currentSpeakerList.setObjectName("currentSpeakerItem")
        self.currentSpeakerList.setGeometry(QRect(10, 30, 140, 60))
        current_speaker_font = QFont()
        current_speaker_font.setPointSize(30)
        current_speaker_font.setBold(True)
        _qcurrentSpeakerItem = QListWidgetItem(self.currentSpeakerList)
        _qcurrentSpeakerItem.setTextAlignment(Qt.AlignmentFlag.AlignCenter)
        _qcurrentSpeakerItem.setFont(current_speaker_font)
        _qcurrentSpeakerItem.setFlags(Qt.ItemFlag.NoItemFlags)
        _qcurrentSpeakerItem.setForeground(QColor(255, 255, 255))
        _qcurrentSpeakerItem.setText("")
        self.currentSpeakerList.addItem(_qcurrentSpeakerItem)

        # button to remove the current speaker
        self.removeSpeakerButton = QPushButton(self)
        self.removeSpeakerButton.setObjectName("removeSpeakerButton")
        self.removeSpeakerButton.setGeometry(QRect(160, 45, 30, 30))
        self.removeSpeakerButton.setText("➖")

        self.removeSpeakerButton.clicked.connect(self.remove_current_speaker)

        # group with speaker list
        self.speakerListGroup = QGroupBox(self)
        self.speakerListGroup.setObjectName("speakerListGroup")
        self.speakerListGroup.setTitle("Redeliste")
        self.speakerListGroup.setGeometry(QRect(10, 90, 140, 120))

        # list with next speakers
        self.speakerListWidget = QListWidget(self)
        self.speakerListWidget.setObjectName("speakerListWidget")
        self.speakerListWidget.setGeometry(QRect(10, 110, 140, 100))

        # button to move a speaker up
        self.moveSpeakerUpButton = QPushButton(self)
        self.moveSpeakerUpButton.setObjectName("moveSpeakerUpButton")
        self.moveSpeakerUpButton.setGeometry(QRect(160, 110, 30, 30))
        self.moveSpeakerUpButton.setText("⬆")

        self.moveSpeakerUpButton.clicked.connect(self.move_speaker_up)

        # button to remove a speaker
        self.removeSpeakerButton = QPushButton(self)
        self.removeSpeakerButton.setObjectName("removeSpeakerButton")
        self.removeSpeakerButton.setGeometry(QRect(160, 145, 30, 30))
        self.removeSpeakerButton.setText("➖")

        self.removeSpeakerButton.clicked.connect(self.remove_speaker)

        # button to move a speaker down
        self.moveSpeakerDownButton = QPushButton(self)
        self.moveSpeakerDownButton.setObjectName("moveSpeakerDownButton")
        self.moveSpeakerDownButton.setGeometry(QRect(160, 180, 30, 30))
        self.moveSpeakerDownButton.setText("⬇")

        self.moveSpeakerDownButton.clicked.connect(self.move_speaker_down)

        # group with present-list
        self.presentListGroup = QGroupBox(self)
        self.presentListGroup.setObjectName("presentListGroup")
        self.presentListGroup.setTitle("Anwesend-Liste")
        self.presentListGroup.setGeometry(QRect(10, 210, 140, 120))

        # list with present persons
        self.presentListWidget = QListWidget(self)
        self.presentListWidget.setObjectName("presentListWidget")
        self.presentListWidget.setGeometry(QRect(10, 230, 140, 100))
        self.presentListWidget.setSortingEnabled(True)

        self.presentListWidget.itemDoubleClicked.connect(self.add_speaker)

        # button to remove a present person
        self.removePresentButton = QPushButton(self)
        self.removePresentButton.setObjectName("removeSpeakerButton")
        self.removePresentButton.setGeometry(QRect(160, 265, 30, 30))
        self.removePresentButton.setText("➖")

        self.removePresentButton.clicked.connect(self.remove_present)

        # text field to add a speaker
        self.addSpeakerTextEdit = QLineEdit(self)
        self.addSpeakerTextEdit.setObjectName("addSpeakerTextEdit")
        self.addSpeakerTextEdit.setGeometry(QRect(10, 340, 140, 30))

        # button to add a speaker
        self.addSpeakerButton = QPushButton(self)
        self.addSpeakerButton.setObjectName("addSpeakerButton")
        self.addSpeakerButton.setGeometry(QRect(160, 340, 30, 30))
        self.addSpeakerButton.setText("➕")

        self.addSpeakerButton.clicked.connect(self.add_present)
        self.addSpeakerTextEdit.returnPressed.connect(self.add_present)

        self.show()

    def remove_current_speaker(self):
        if self.speakerListWidget.count() > 0:
            self.currentSpeakerList.item(0).setText(self.speakerListWidget.item(0).text()[0].upper() + self.speakerListWidget.item(0).text()[1].lower())
            self.speakerListWidget.takeItem(0)
        else:
            self.currentSpeakerList.item(0).setText("")

    def add_speaker(self, item):
        text = item.text()
        if self.currentSpeakerList.item(0).text() != "":
            self.speakerListWidget.addItem(text)
        else:
            self.currentSpeakerList.item(0).setText(text[0].upper() + text[1].lower())

    def move_speaker_up(self):
        if self.speakerListWidget.count() > 0:
            item_id = self.speakerListWidget.selectedIndexes()[0]
            if item_id.row() != 0:
                item = self.speakerListWidget.takeItem(item_id.row())
                self.speakerListWidget.insertItem(item_id.row() - 1, item)
                self.speakerListWidget.setCurrentRow(item_id.row() - 1)

    def remove_speaker(self):
        if self.speakerListWidget.count() > 0:
            item_id = self.speakerListWidget.selectedIndexes()[0]
            self.speakerListWidget.takeItem(item_id.row())

    def move_speaker_down(self):
        if self.speakerListWidget.count() > 0:
            item_id = self.speakerListWidget.selectedIndexes()[0]
            if item_id.row() != self.speakerListWidget.count() - 1:
                item = self.speakerListWidget.takeItem(item_id.row())
                self.speakerListWidget.insertItem(item_id.row() + 1, item)
                self.speakerListWidget.setCurrentRow(item_id.row() + 1)

    def remove_present(self):
        if self.presentListWidget.count() > 0:
            item_id = self.presentListWidget.selectedIndexes()[0]
            self.presentListWidget.takeItem(item_id.row())

    def add_present(self):
        text = self.addSpeakerTextEdit.text()
        if len(text) > 1:
            self.addSpeakerTextEdit.setText("")
            self.presentListWidget.addItem(text)
