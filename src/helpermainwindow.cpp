#include "helpermainwindow.h"
#include "ui_helpermainwindow.h"

helperMainWindow::helperMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::helperMainWindow) {
    ui->setupUi(this);
    connect(this->updateTimer, &QTimer::timeout, this, &helperMainWindow::updateProgress);
    connect(this->speakerTimer, &QTimer::timeout, this, &helperMainWindow::speakerTimeout);
}

helperMainWindow::~helperMainWindow() {
    delete ui;
}

void helperMainWindow::on_addPresentButton_clicked() {
    if (ui->inputPresentEditBox->text().length() > 1) {
        ui->presentList->addItem(ui->inputPresentEditBox->text().simplified());
        ui->inputPresentEditBox->setText("");
    }

}


void helperMainWindow::on_inputPresentEditBox_returnPressed() {
    if (ui->inputPresentEditBox->text().length() > 1) {
        ui->presentList->addItem(ui->inputPresentEditBox->text().simplified());
        ui->inputPresentEditBox->setText("");
    }
}


void helperMainWindow::on_presentList_itemDoubleClicked(QListWidgetItem *item) {
    if (ui->currentSpeakerLabel->text() == "") {
        ui->currentSpeakerLabel->setText(item->text());

        QFont labelFont = ui->currentSpeakerLabel->font();
        labelFont.setPointSize(30);
        ui->currentSpeakerLabel->setFont(labelFont);
    }
    else {
        ui->speakerList->addItem(item->text());
    }
}


void helperMainWindow::on_removePresentButton_clicked() {
    if (!ui->presentList->selectedItems().isEmpty()) {
        QListWidgetItem* item = ui->presentList->selectedItems().at(0);
        ui->presentList->takeItem(ui->presentList->row(item));
    }
}


void helperMainWindow::on_removeSpeakerButton_clicked() {
    if (!ui->speakerList->selectedItems().isEmpty()) {
        QListWidgetItem* item = ui->speakerList->selectedItems().at(0);
        ui->speakerList->takeItem(ui->speakerList->row(item));
    }
}


void helperMainWindow::on_removeCurrentSpeakerButton_clicked() {
    if (ui->speakerList->count() > 0) {
        ui->currentSpeakerLabel->setText(ui->speakerList->item(0)->text());

        QFont labelFont = ui->currentSpeakerLabel->font();
        labelFont.setPointSize(30);
        ui->currentSpeakerLabel->setFont(labelFont);

        ui->speakerList->takeItem(0);
    }
    else {
        ui->currentSpeakerLabel->setText("");
    }
    if (ui->timerGroupBoxWidget->isChecked()) {
        speakerTimer->stop();
        updateTimer->stop();
        ui->timerEdit->setEnabled(true);
        ui->timerProgressBar->setValue(ui->timerProgressBar->maximum());
    }
    ui->currentSpeakerLabel->setAutoFillBackground(false);
}


void helperMainWindow::on_moveSpeakerUpButton_clicked() {
    if (!ui->speakerList->selectedItems().isEmpty()) {
        int selected_row = ui->speakerList->row(ui->speakerList->selectedItems().at(0));
        if (selected_row != 0) {
            QListWidgetItem* item = ui->speakerList->takeItem(selected_row);
            ui->speakerList->insertItem(selected_row - 1, item->text());
            ui->speakerList->setCurrentRow(selected_row - 1);
        }
    }
}


void helperMainWindow::on_moveSpeakerDownButton_clicked() {
    if (!ui->speakerList->selectedItems().isEmpty()) {
        int selected_row = ui->speakerList->row(ui->speakerList->selectedItems().at(0));
        if (selected_row != ui->speakerList->count() - 1) {
            QListWidgetItem* item = ui->speakerList->takeItem(selected_row);
            ui->speakerList->insertItem(selected_row + 1, item->text());
            ui->speakerList->setCurrentRow(selected_row + 1);
        }
    }
}

void helperMainWindow::resizeEvent(QResizeEvent*) {
    QFont labelFont = ui->currentSpeakerLabel->font();
    labelFont.setPointSize(30);
    ui->currentSpeakerLabel->setFont(labelFont);
}

void helperMainWindow::on_timerEdit_userTimeChanged(const QTime &time) {
    int timerMaxTime = time.minute() * 60 + time.second();
    ui->timerProgressBar->setMaximum(timerMaxTime);
    ui->timerProgressBar->setValue(timerMaxTime);
}


void helperMainWindow::on_timerGoButton_clicked() {
    speakerTimer->start(ui->timerEdit->time().minute() * 60 * 1000 + ui->timerEdit->time().second() * 1000);
    updateTimer->start(1000);
    ui->timerEdit->setEnabled(false);
    ui->timerProgressBar->setValue(ui->timerProgressBar->maximum());
    ui->currentSpeakerLabel->setAutoFillBackground(false);
}


void helperMainWindow::on_timerStopButton_clicked() {
    speakerTimer->stop();
    updateTimer->stop();
    ui->timerEdit->setEnabled(true);
    ui->timerProgressBar->setValue(ui->timerProgressBar->value());
}

void helperMainWindow::updateProgress() {
    ui->timerProgressBar->setValue(ui->timerProgressBar->value() - 1);
    if (speakerTimer->remainingTime() / 1000 <= 15.0 &&
        ui->currentSpeakerLabel->palette().color(QPalette::Window) != Qt::yellow) {
        ui->currentSpeakerLabel->setAutoFillBackground(true);
        QPalette backgroundPalette;
        backgroundPalette.setColor(QPalette::Window, Qt::yellow);
        ui->currentSpeakerLabel->setPalette(backgroundPalette);
    }
}

void helperMainWindow::speakerTimeout() {
    speakerTimer->stop();
    updateTimer->stop();
    ui->timerProgressBar->setValue(0);
    if (ui->currentSpeakerLabel->palette().color(QPalette::Window) != Qt::red) {
        ui->currentSpeakerLabel->setAutoFillBackground(true);
        QPalette backgroundPalette;
        backgroundPalette.setColor(QPalette::Window, Qt::red);
        ui->currentSpeakerLabel->setPalette(backgroundPalette);
    }
}
