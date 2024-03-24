#include "settingsdialog.h"
#include "ui_settingsdialog.h"

settingsDialog::settingsDialog(int timerWarn, bool timerSound, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::settingsDialog) {
    ui->setupUi(this);

    ui->timerWarningDelaySpinBox->setValue(timerWarn);
    ui->timerWarningSoundCheckBox->setChecked(timerSound);
}

settingsDialog::~settingsDialog() {
    delete ui;
}

void settingsDialog::on_buttonBox_accepted() {
    emit timerWarningSoundChanged(ui->timerWarningSoundCheckBox->isChecked());
    emit timerWarningDelayChanged(ui->timerWarningDelaySpinBox->value());
    this->close();
}


void settingsDialog::on_buttonBox_rejected() {
    this->close();
}
