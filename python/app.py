# -*- coding: utf-8 -*-
from PyQt6.QtCore import QSize, Qt
from PyQt6.QtGui import QFont
from PyQt6.QtWidgets import (QMainWindow, QWidget, QGroupBox, QLabel, QPushButton, QLineEdit, QListWidget,
                             QHBoxLayout, QVBoxLayout, QSizePolicy)

import logging
import pathlib


class UiMainWindow(QMainWindow):
    """
    Main app window
    """

    def __init__(self):
        super().__init__()

        # main window title
        with open(pathlib.Path(f'./version'), 'r') as ver_file:
            self.version = ver_file.readline()
        self.setWindowTitle(f"fiso-helper v{self.version}")

        # main window size setting
        self.resize(QSize(200, 380))
        self.setMinimumSize(QSize(200, 380))

        # central widget (whole main window)
        self.centralwidget = QWidget(self)

        # central widget layout
        self.centralWidgetHL = QHBoxLayout(self.centralwidget)
        self.centralWidgetHL.setSpacing(5)
        self.centralWidgetHL.setContentsMargins(5, 5, 5, 5)

        # speaker list manager widget
        self.speakerListManager = QWidget(self.centralwidget)

        # speaker list manager layout
        self.speakerListManagerVL = QVBoxLayout(self.speakerListManager)
        self.speakerListManagerVL.setSpacing(5)
        self.speakerListManagerVL.setContentsMargins(0, 0, 0, 0)

        # current speaker widget - position 1
        self.currentSpeakerWidget = QWidget(self.speakerListManager)
        size_policy = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Minimum)
        size_policy.setHorizontalStretch(0)
        size_policy.setVerticalStretch(66)
        size_policy.setHeightForWidth(self.currentSpeakerWidget.sizePolicy().hasHeightForWidth())
        self.currentSpeakerWidget.setSizePolicy(size_policy)
        self.currentSpeakerWidget.setMinimumSize(QSize(0, 80))

        # current speaker widget layout
        self.currentSpeakerWidgetHL = QHBoxLayout(self.currentSpeakerWidget)
        self.currentSpeakerWidgetHL.setSpacing(10)
        self.currentSpeakerWidgetHL.setContentsMargins(0, 0, 0, 0)

        # current speaker group widget
        self.currentSpeakerGroupWidget = QWidget(self.currentSpeakerWidget)

        # current speaker group widget layout
        self.currentSpeakerGroupWidgetVL = QVBoxLayout(self.currentSpeakerGroupWidget)
        self.currentSpeakerGroupWidgetVL.setSpacing(3)
        self.currentSpeakerGroupWidgetVL.setContentsMargins(0, 0, 0, 0)

        # current speaker GroupBox
        self.currentSpeakerGroupBox = QGroupBox(self.currentSpeakerGroupWidget)
        self.currentSpeakerGroupBox.setTitle("Aktuelle Redner*in")

        # current speaker GroupBox layout
        self.currentSpeakerGroupBoxVL = QVBoxLayout(self.currentSpeakerGroupBox)
        self.currentSpeakerGroupBoxVL.setSpacing(0)
        self.currentSpeakerGroupBoxVL.setContentsMargins(0, 0, 0, 0)

        # current speaker label
        self.currentSpeakerLabel = QLabel(self.currentSpeakerGroupBox)
        size_policy1 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Preferred)
        size_policy1.setHorizontalStretch(0)
        size_policy1.setVerticalStretch(0)
        size_policy1.setHeightForWidth(self.currentSpeakerLabel.sizePolicy().hasHeightForWidth())
        self.currentSpeakerLabel.setSizePolicy(size_policy1)
        font = QFont()  # default font for the label
        font.setPointSize(self.currentSpeakerLabel.height() - 25)
        font.setBold(True)
        self.currentSpeakerLabel.setFont(font)
        self.currentSpeakerLabel.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.currentSpeakerLabel.setTextInteractionFlags(Qt.TextInteractionFlag.NoTextInteraction)

        # stack widgets
        self.currentSpeakerGroupBoxVL.addWidget(self.currentSpeakerLabel)
        self.currentSpeakerGroupWidgetVL.addWidget(self.currentSpeakerGroupBox)
        self.currentSpeakerWidgetHL.addWidget(self.currentSpeakerGroupWidget)

        # current speaker controls widgets
        self.currentSpeakerControls = QWidget(self.currentSpeakerWidget)
        size_policy2 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Preferred)
        size_policy2.setHorizontalStretch(0)
        size_policy2.setVerticalStretch(0)
        size_policy2.setHeightForWidth(self.currentSpeakerControls.sizePolicy().hasHeightForWidth())
        self.currentSpeakerControls.setSizePolicy(size_policy2)
        self.currentSpeakerControls.setMinimumSize(QSize(30, 0))

        # current speaker controls layout
        self.currentSpeakerControlsVL = QVBoxLayout(self.currentSpeakerControls)
        self.currentSpeakerControlsVL.setSpacing(3)
        self.currentSpeakerControlsVL.setContentsMargins(0, 0, 0, 0)

        # remove current speaker button
        self.removeCurrentSpeakerButton = QPushButton(self.currentSpeakerControls)
        size_policy3 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        size_policy3.setHorizontalStretch(0)
        size_policy3.setVerticalStretch(0)
        size_policy3.setHeightForWidth(self.removeCurrentSpeakerButton.sizePolicy().hasHeightForWidth())
        self.removeCurrentSpeakerButton.setSizePolicy(size_policy3)
        self.removeCurrentSpeakerButton.setMinimumSize(QSize(30, 30))
        self.removeCurrentSpeakerButton.setMaximumSize(QSize(30, 30))
        self.removeCurrentSpeakerButton.setText("➖")

        self.removeCurrentSpeakerButton.clicked.connect(self.remove_current_speaker)

        # stack widgets
        self.currentSpeakerControlsVL.addWidget(self.removeCurrentSpeakerButton)
        self.currentSpeakerWidgetHL.addWidget(self.currentSpeakerControls)
        self.speakerListManagerVL.addWidget(self.currentSpeakerWidget)

        # speaker list widget
        self.speakerListWidget = QWidget(self.speakerListManager)
        size_policy4 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Minimum)
        size_policy4.setHorizontalStretch(0)
        size_policy4.setVerticalStretch(100)
        size_policy4.setHeightForWidth(self.speakerListWidget.sizePolicy().hasHeightForWidth())
        self.speakerListWidget.setSizePolicy(size_policy4)
        self.speakerListWidget.setMinimumSize(QSize(0, 120))

        # speaker list widget layout
        self.speakerListWidgetHL = QHBoxLayout(self.speakerListWidget)
        self.speakerListWidgetHL.setSpacing(10)
        self.speakerListWidgetHL.setContentsMargins(0, 0, 0, 0)

        # speaker list group widget
        self.speakerListGroupWidget = QWidget(self.speakerListWidget)

        # speaker list group widget layout
        self.speakerListGroupWidgetVL = QVBoxLayout(self.speakerListGroupWidget)
        self.speakerListGroupWidgetVL.setSpacing(3)
        self.speakerListGroupWidgetVL.setContentsMargins(0, 0, 0, 0)

        # speaker list GroupBox
        self.speakerListGroupBox = QGroupBox(self.speakerListGroupWidget)
        self.speakerListGroupBox.setTitle("Redeliste")

        # speaker list GroupBox layout
        self.speakerListGroupBoxVL = QVBoxLayout(self.speakerListGroupBox)
        self.speakerListGroupBoxVL.setSpacing(0)
        self.speakerListGroupBoxVL.setContentsMargins(0, 0, 0, 0)

        # speaker list
        self.speakerList = QListWidget(self.speakerListGroupBox)

        # stack widgets
        self.speakerListGroupBoxVL.addWidget(self.speakerList)
        self.speakerListGroupWidgetVL.addWidget(self.speakerListGroupBox)
        self.speakerListWidgetHL.addWidget(self.speakerListGroupWidget)

        # speaker list controls
        self.speakerListControls = QWidget(self.speakerListWidget)
        size_policy2.setHeightForWidth(self.speakerListControls.sizePolicy().hasHeightForWidth())
        self.speakerListControls.setSizePolicy(size_policy2)
        self.speakerListControls.setMinimumSize(QSize(30, 0))

        # speaker list controls layout
        self.speakerListControlsVL = QVBoxLayout(self.speakerListControls)
        self.speakerListControlsVL.setSpacing(3)
        self.speakerListControlsVL.setContentsMargins(0, 0, 0, 0)

        # speaker list moveUp button
        self.moveSpeakerUpButton = QPushButton(self.speakerListControls)
        size_policy3.setHeightForWidth(self.moveSpeakerUpButton.sizePolicy().hasHeightForWidth())
        self.moveSpeakerUpButton.setSizePolicy(size_policy3)
        self.moveSpeakerUpButton.setMinimumSize(QSize(30, 30))
        self.moveSpeakerUpButton.setMaximumSize(QSize(30, 30))
        self.moveSpeakerUpButton.setText("⬆")

        self.moveSpeakerUpButton.clicked.connect(self.move_speaker_up)

        # add button
        self.speakerListControlsVL.addWidget(self.moveSpeakerUpButton)

        # speaker list remove button
        self.removeSpeakerButton = QPushButton(self.speakerListControls)
        size_policy3.setHeightForWidth(self.removeSpeakerButton.sizePolicy().hasHeightForWidth())
        self.removeSpeakerButton.setSizePolicy(size_policy3)
        self.removeSpeakerButton.setMinimumSize(QSize(30, 30))
        self.removeSpeakerButton.setMaximumSize(QSize(30, 30))
        self.removeSpeakerButton.setText("➖")

        self.removeSpeakerButton.clicked.connect(self.remove_speaker)

        # add button
        self.speakerListControlsVL.addWidget(self.removeSpeakerButton)

        # speaker list moveDown
        self.moveSpeakerDownButton = QPushButton(self.speakerListControls)
        size_policy3.setHeightForWidth(self.moveSpeakerDownButton.sizePolicy().hasHeightForWidth())
        self.moveSpeakerDownButton.setSizePolicy(size_policy3)
        self.moveSpeakerDownButton.setMinimumSize(QSize(30, 30))
        self.moveSpeakerDownButton.setMaximumSize(QSize(30, 30))
        self.moveSpeakerDownButton.setText("⬇")

        self.moveSpeakerDownButton.clicked.connect(self.move_speaker_down)

        # stack widgets
        self.speakerListControlsVL.addWidget(self.moveSpeakerDownButton)
        self.speakerListWidgetHL.addWidget(self.speakerListControls)
        self.speakerListManagerVL.addWidget(self.speakerListWidget)

        # present list widget
        self.presentListWidget = QWidget(self.speakerListManager)
        size_policy4.setHeightForWidth(self.presentListWidget.sizePolicy().hasHeightForWidth())
        self.presentListWidget.setSizePolicy(size_policy4)
        self.presentListWidget.setMinimumSize(QSize(0, 120))

        # present list widget layout
        self.presentListWidgetHL = QHBoxLayout(self.presentListWidget)
        self.presentListWidgetHL.setSpacing(10)
        self.presentListWidgetHL.setContentsMargins(0, 0, 0, 0)

        # present list group widget
        self.presentListGroupWidget = QWidget(self.presentListWidget)

        # present list group widget layout
        self.presentListGroupWidgetVL = QVBoxLayout(self.presentListGroupWidget)
        self.presentListGroupWidgetVL.setSpacing(3)
        self.presentListGroupWidgetVL.setContentsMargins(0, 0, 0, 0)

        # present list GroupBox
        self.presentListGroupBox = QGroupBox(self.presentListGroupWidget)
        self.presentListGroupBox.setTitle("Anwesend-Liste")

        # present list GroupBox layout
        self.presentListGroupBoxVL = QVBoxLayout(self.presentListGroupBox)
        self.presentListGroupBoxVL.setSpacing(0)
        self.presentListGroupBoxVL.setContentsMargins(0, 0, 0, 0)

        # present list
        self.presentList = QListWidget(self.presentListGroupBox)
        self.presentList.setSortingEnabled(True)
        self.presentList.itemDoubleClicked.connect(self.add_speaker)

        # stack widgets
        self.presentListGroupBoxVL.addWidget(self.presentList)
        self.presentListGroupWidgetVL.addWidget(self.presentListGroupBox)
        self.presentListWidgetHL.addWidget(self.presentListGroupWidget)

        # present list controls
        self.presentListControls = QWidget(self.presentListWidget)
        size_policy2.setHeightForWidth(self.presentListControls.sizePolicy().hasHeightForWidth())
        self.presentListControls.setSizePolicy(size_policy2)
        self.presentListControls.setMinimumSize(QSize(30, 0))

        # present list controls layout
        self.presentListControlsVL = QVBoxLayout(self.presentListControls)
        self.presentListControlsVL.setSpacing(3)
        self.presentListControlsVL.setContentsMargins(0, 0, 0, 0)

        # present list remove button
        self.removePresentButton = QPushButton(self.presentListControls)
        size_policy3.setHeightForWidth(self.removePresentButton.sizePolicy().hasHeightForWidth())
        self.removePresentButton.setSizePolicy(size_policy3)
        self.removePresentButton.setMinimumSize(QSize(30, 30))
        self.removePresentButton.setMaximumSize(QSize(30, 30))
        self.removePresentButton.setText("➖")

        self.removePresentButton.clicked.connect(self.remove_present)

        # stack widgets
        self.presentListControlsVL.addWidget(self.removePresentButton)
        self.presentListWidgetHL.addWidget(self.presentListControls)
        self.speakerListManagerVL.addWidget(self.presentListWidget)

        # input box widget
        self.inputPresentWidget = QWidget(self.speakerListManager)
        size_policy5 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Fixed)
        size_policy5.setHorizontalStretch(0)
        size_policy5.setVerticalStretch(0)
        size_policy5.setHeightForWidth(self.inputPresentWidget.sizePolicy().hasHeightForWidth())
        self.inputPresentWidget.setSizePolicy(size_policy5)
        self.inputPresentWidget.setMinimumSize(QSize(0, 30))

        # input present widget layout
        self.inputPresentWidgetHL = QHBoxLayout(self.inputPresentWidget)
        self.inputPresentWidgetHL.setSpacing(10)
        self.inputPresentWidgetHL.setContentsMargins(0, 0, 0, 0)

        # input present edit widget
        self.inputPresentEditWidget = QWidget(self.inputPresentWidget)
        size_policy5.setHeightForWidth(self.inputPresentEditWidget.sizePolicy().hasHeightForWidth())
        self.inputPresentEditWidget.setSizePolicy(size_policy5)
        self.inputPresentEditWidget.setMinimumSize(QSize(0, 30))

        # input present edit widget layout
        self.inputPresentEditWidgetVL = QVBoxLayout(self.inputPresentEditWidget)
        self.inputPresentEditWidgetVL.setSpacing(3)
        self.inputPresentEditWidgetVL.setContentsMargins(0, 0, 0, 0)

        # input present EditBox
        self.inputPresentEditBox = QLineEdit(self.inputPresentEditWidget)
        size_policy5.setHeightForWidth(self.inputPresentEditBox.sizePolicy().hasHeightForWidth())
        self.inputPresentEditBox.setSizePolicy(size_policy5)
        self.inputPresentEditBox.setMinimumSize(QSize(0, 30))

        # stack widgets
        self.inputPresentEditWidgetVL.addWidget(self.inputPresentEditBox)
        self.inputPresentWidgetHL.addWidget(self.inputPresentEditWidget)

        # input present controls
        self.inputPresentControls = QWidget(self.inputPresentWidget)
        size_policy3.setHeightForWidth(self.inputPresentControls.sizePolicy().hasHeightForWidth())
        self.inputPresentControls.setSizePolicy(size_policy3)
        self.inputPresentControls.setMinimumSize(QSize(30, 30))

        # input present controls layout
        self.inputPresentControlsHL = QHBoxLayout(self.inputPresentControls)
        self.inputPresentControlsHL.setSpacing(3)
        self.inputPresentControlsHL.setContentsMargins(0, 0, 0, 0)

        # add present button
        self.addPresentButton = QPushButton(self.inputPresentControls)
        size_policy3.setHeightForWidth(self.addPresentButton.sizePolicy().hasHeightForWidth())
        self.addPresentButton.setSizePolicy(size_policy3)
        self.addPresentButton.setMinimumSize(QSize(30, 30))
        self.addPresentButton.setMaximumSize(QSize(30, 30))
        self.addPresentButton.setText("➕")

        self.addPresentButton.clicked.connect(self.add_present)
        self.inputPresentEditBox.returnPressed.connect(self.add_present)

        # stack widgets
        self.inputPresentControlsHL.addWidget(self.addPresentButton)
        self.inputPresentWidgetHL.addWidget(self.inputPresentControls)
        self.speakerListManagerVL.addWidget(self.inputPresentWidget)

        self.centralWidgetHL.addWidget(self.speakerListManager)

        self.setCentralWidget(self.centralwidget)

        self.show()

    def remove_current_speaker(self):
        if self.speakerList.count() > 0:
            item = self.speakerList.takeItem(0)
            self.currentSpeakerLabel.setText(item.text()[0].upper() + item.text()[1].lower())
            self.currentSpeakerLabel.update()
        else:
            self.currentSpeakerLabel.setText("")
            self.currentSpeakerLabel.update()

    def add_speaker(self, item):
        text = item.text()
        if len(self.currentSpeakerLabel.text()) > 0:
            self.speakerList.addItem(text)
        else:
            new_width = self.currentSpeakerLabel.width() - 25
            new_height = self.currentSpeakerLabel.height() - 25
            new_font = QFont()
            if new_height < new_width:
                new_font.setPointSize(new_height)
            else:
                new_font.setPointSize(new_width)
            new_font.setBold(True)
            self.currentSpeakerLabel.setFont(new_font)
            self.currentSpeakerLabel.setText(text[0].upper() + text[1].lower())
            self.currentSpeakerLabel.update()

    def move_speaker_up(self):
        if self.speakerList.count() > 0 and len(self.speakerList.selectedIndexes()) > 0:
            item_id = self.speakerList.selectedIndexes()[0]
            if item_id.row() != 0:
                item = self.speakerList.takeItem(item_id.row())
                self.speakerList.insertItem(item_id.row() - 1, item)
                self.speakerList.setCurrentRow(item_id.row() - 1)

    def remove_speaker(self):
        if self.speakerList.count() > 0 and len(self.speakerList.selectedIndexes()) > 0:
            item_id = self.speakerList.selectedIndexes()[0]
            self.speakerList.takeItem(item_id.row())

    def move_speaker_down(self):
        if self.speakerList.count() > 0 and len(self.speakerList.selectedIndexes()) > 0:
            item_id = self.speakerList.selectedIndexes()[0]
            if item_id.row() != self.speakerList.count() - 1:
                item = self.speakerList.takeItem(item_id.row())
                self.speakerList.insertItem(item_id.row() + 1, item)
                self.speakerList.setCurrentRow(item_id.row() + 1)

    def remove_present(self):
        if self.presentList.count() > 0 and len(self.presentList.selectedIndexes()) > 0:
            item_id = self.presentList.selectedIndexes()[0]
            self.presentList.takeItem(item_id.row())

    def add_present(self):
        text = self.inputPresentEditBox.text()
        if len(text) > 1:
            self.inputPresentEditBox.setText("")
            self.presentList.addItem(text)

    def resizeEvent(self, event):
        new_width = self.currentSpeakerLabel.width() - 25
        new_height = self.currentSpeakerLabel.height() - 25
        new_font = QFont()
        if new_height < new_width:
            new_font.setPointSize(new_height)
        else:
            new_font.setPointSize(new_width)
        new_font.setBold(True)
        self.currentSpeakerLabel.setFont(new_font)
        return super(QMainWindow, self).resizeEvent(event)
