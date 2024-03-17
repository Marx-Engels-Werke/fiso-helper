#include "helpermainwindow.h"
#include "ui_helpermainwindow.h"

helperMainWindow::helperMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::helperMainWindow)
{
    ui->setupUi(this);
}

helperMainWindow::~helperMainWindow()
{
    delete ui;
}

void helperMainWindow::on_addPresentButton_clicked()
{
    if (ui->inputPresentEditBox->text().length() > 1) {
        ui->presentList->addItem(ui->inputPresentEditBox->text().simplified());
        ui->inputPresentEditBox->setText("");
    }

}


void helperMainWindow::on_inputPresentEditBox_returnPressed()
{
    if (ui->inputPresentEditBox->text().length() > 1) {
        ui->presentList->addItem(ui->inputPresentEditBox->text().simplified());
        ui->inputPresentEditBox->setText("");
    }
}


void helperMainWindow::on_presentList_itemDoubleClicked(QListWidgetItem *item)
{
    if (ui->currentSpeakerLabel->text() == "") {
        ui->currentSpeakerLabel->setText(item->text());

        QFont labelFont = ui->currentSpeakerLabel->font();
        labelFont.setPointSize(ui->currentSpeakerLabel->height() - 25);
        ui->currentSpeakerLabel->setFont(labelFont);
    }
    else {
        ui->speakerList->addItem(item->text());
    }
}


void helperMainWindow::on_removePresentButton_clicked()
{
    if (!ui->presentList->selectedItems().isEmpty()) {
        QListWidgetItem* item = ui->presentList->selectedItems().at(0);
        ui->presentList->takeItem(ui->presentList->row(item));
    }
}


void helperMainWindow::on_removeSpeakerButton_clicked()
{
    if (!ui->speakerList->selectedItems().isEmpty()) {
        QListWidgetItem* item = ui->speakerList->selectedItems().at(0);
        ui->speakerList->takeItem(ui->speakerList->row(item));
    }
}


void helperMainWindow::on_removeCurrentSpeakerButton_clicked()
{
    if (ui->speakerList->count() > 0) {
        ui->currentSpeakerLabel->setText(ui->speakerList->item(0)->text());

        QFont labelFont = ui->currentSpeakerLabel->font();
        labelFont.setPointSize(ui->currentSpeakerLabel->height() - 25);
        ui->currentSpeakerLabel->setFont(labelFont);

        ui->speakerList->takeItem(0);
    }
    else {
        ui->currentSpeakerLabel->setText("");
    }
}


void helperMainWindow::on_moveSpeakerUpButton_clicked()
{
    if (!ui->speakerList->selectedItems().isEmpty()) {
        int selected_row = ui->speakerList->row(ui->speakerList->selectedItems().at(0));
        if (selected_row != 0) {
            QListWidgetItem* item = ui->speakerList->takeItem(selected_row);
            ui->speakerList->insertItem(selected_row - 1, item->text());
            ui->speakerList->setCurrentRow(selected_row - 1);
        }
    }
}


void helperMainWindow::on_moveSpeakerDownButton_clicked()
{
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
    labelFont.setPointSize(ui->currentSpeakerLabel->height() - 25);
    ui->currentSpeakerLabel->setFont(labelFont);
}
