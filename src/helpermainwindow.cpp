#include "helpermainwindow.h"
#include "ui_helpermainwindow.h"
#include "settingsdialog.h"

helperMainWindow::helperMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::helperMainWindow) {
    ui->setupUi(this);

    // set default dettings
    this->timerWarningDelay = 15;
    this->timerWarningSoundEnabled = false;

    // connect timers
    connect(this->updateTimer, &QTimer::timeout, this, &helperMainWindow::updateProgress);
    connect(this->speakerTimer, &QTimer::timeout, this, &helperMainWindow::speakerTimeout);

    // sounds
    this->ding.setSource(QUrl("qrc:/sounds/sounds/ding.wav"));
    this->dingdingding.setSource(QUrl("qrc:/sounds/sounds/dingdingding.wav"));

    // session
    this->isChanged = false;
}

helperMainWindow::~helperMainWindow() {
    delete ui;
}

// ui elements
void helperMainWindow::on_addPresentButton_clicked() {
    if (ui->inputPresentEditBox->text().length() > 1) {
        QString str = ui->inputPresentEditBox->text().simplified();
        ui->presentList->addItem(str);
        ui->inputPresentEditBox->setText("");

        this->isChanged = true;
    }
}

void helperMainWindow::on_inputPresentEditBox_returnPressed() {
    if (ui->inputPresentEditBox->text().length() > 1) {
        QString str = ui->inputPresentEditBox->text().simplified();
        ui->presentList->addItem(str);
        ui->inputPresentEditBox->setText("");

        this->isChanged = true;
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

    this->isChanged = true;
}

void helperMainWindow::on_removePresentButton_clicked() {
    if (!ui->presentList->selectedItems().isEmpty()) {
        QListWidgetItem* item = ui->presentList->selectedItems().at(0);
        int selected_row = ui->presentList->row(item);
        ui->presentList->takeItem(selected_row);
    }

    this->isChanged = true;
}

void helperMainWindow::on_removeSpeakerButton_clicked() {
    if (!ui->speakerList->selectedItems().isEmpty()) {
        QListWidgetItem* item = ui->speakerList->selectedItems().at(0);
        int selected_row = ui->speakerList->row(item);
        ui->speakerList->takeItem(selected_row);
    }

    this->isChanged = true;
}

void helperMainWindow::on_removeCurrentSpeakerButton_clicked() {
    if (ui->speakerList->count() > 0) {
        ui->currentSpeakerLabel->setText(ui->speakerList->item(0)->text());

        QFont labelFont = ui->currentSpeakerLabel->font();
        labelFont.setPointSize(30);
        ui->currentSpeakerLabel->setFont(labelFont);

        ui->speakerList->takeItem(0);

        this->isChanged = true;
    }
    else {
        ui->currentSpeakerLabel->setText("");

        this->isChanged = true;
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
        this->isChanged = true;
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
        this->isChanged = true;
    }
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

// menu elements

void helperMainWindow::on_actionExit_triggered() {
    this->close();
}

void helperMainWindow::on_actionSettings_triggered() {
    settingsDialog *sd = new settingsDialog(timerWarningDelay, timerWarningSoundEnabled, this);
    connect(sd, &settingsDialog::timerWarningDelayChanged, this, &helperMainWindow::timerWarningChangedHandler);
    connect(sd, &settingsDialog::timerWarningSoundChanged, this, &helperMainWindow::timerWarningSoundHandler);
    sd->show();
}

void helperMainWindow::on_actionNewSession_triggered() {
    if (this->isChanged) {
        this->exitNewDialog();
    }
    else {
        this->clearWindow();
        this->isChanged = false;
    }
}

void helperMainWindow::on_actionSessionSave_triggered() {
    QString filename = QFileDialog::getSaveFileName(this, tr("Satzung speichern"), "", tr("Satzung Datei (*.sdaj)"));
    QSaveFile file(filename);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to save file"),
                                 file.errorString());
        return;
    }

    this->isChanged = false;
    QDataStream out(&file);

    out << ui->currentSpeakerLabel->text().toUtf8();

    QList<QByteArray> speakerList;
    for (int i = 0; i < ui->speakerList->count(); ++i)
        speakerList.append(ui->speakerList->item(i)->text().toUtf8());

    QList<QByteArray> presentList;
    for (int i = 0; i < ui->presentList->count(); ++i)
        presentList.append(ui->presentList->item(i)->text().toUtf8());

    out << speakerList;
    out << presentList;

    file.commit();
}

void helperMainWindow::on_actionSessionOpen_triggered() {
    if (this->isChanged)
        this->exitNewDialog();
    else
        this->clearWindow();

    QString filename = QFileDialog::getOpenFileName(this, tr("Satzung öffnen"), "", tr("Satzung Datei (*.sdaj)"));
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
                                 file.errorString());
        return;
    }

    QDataStream in(&file);

    QByteArray currentSpeaker;
    QList<QByteArray> speakerList;
    QList<QByteArray> presentList;

    in >> currentSpeaker;
    in >> speakerList;
    in >> presentList;

    file.close();

    ui->currentSpeakerLabel->setText(currentSpeaker);

    for (auto &item: speakerList) {
        ui->speakerList->addItem(item);
    }

    for (auto &item: presentList) {
        ui->presentList->addItem(item);
    }
}

// communication handlers

void helperMainWindow::timerWarningChangedHandler(int warningDelay) {
    this->timerWarningDelay = warningDelay;
}

void helperMainWindow::timerWarningSoundHandler(bool soundState) {
    this->timerWarningSoundEnabled = soundState;
}

// private

// void helperMainWindow::resizeEvent(QResizeEvent*) {
//     QFont labelFont = ui->currentSpeakerLabel->font();
//     labelFont.setPointSize(30);
//     ui->currentSpeakerLabel->setFont(labelFont);
// }

void helperMainWindow::speakerTimeout() {
    speakerTimer->stop();
    updateTimer->stop();
    ui->timerProgressBar->setValue(0);

    ui->currentSpeakerLabel->setAutoFillBackground(true);
    QPalette backgroundPalette;
    backgroundPalette.setColor(QPalette::Window, Qt::red);
    ui->currentSpeakerLabel->setPalette(backgroundPalette);

    if (this->timerWarningSoundEnabled)
        this->dingdingding.play();
}

void helperMainWindow::updateProgress() {
    ui->timerProgressBar->setValue(ui->timerProgressBar->value() - 1);
    if (speakerTimer->remainingTime() / 1000 < this->timerWarningDelay &&
        ui->currentSpeakerLabel->palette().window().color() != Qt::yellow) {
        ui->currentSpeakerLabel->setAutoFillBackground(true);
        QPalette backgroundPalette;
        backgroundPalette.setColor(QPalette::Window, Qt::yellow);
        ui->currentSpeakerLabel->setPalette(backgroundPalette);

        if (this->timerWarningSoundEnabled)
            this->ding.play();
    }
}

void helperMainWindow::clearWindow() {
    ui->currentSpeakerLabel->clear();
    ui->speakerList->clear();
    ui->presentList->clear();
    ui->inputPresentEditBox->clear();
}

void helperMainWindow::exitNewDialog() {
    QMessageBox::StandardButton resBtn = QMessageBox::question(this,
                                                               tr("fiso-helper"),
                                                               tr("Satzung speichern?"),
                                                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    switch (resBtn) {
    case QMessageBox::Save:
        this->on_actionSessionSave_triggered();
        this->isChanged = false;
        this->clearWindow();
        break;
    case QMessageBox::Discard:
        this->isChanged = false;
        this->clearWindow();
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }
}

void helperMainWindow::closeEvent(QCloseEvent *event) {
    if(this->isChanged) {
        QMessageBox::StandardButton resBtn = QMessageBox::question(this,
                                                                   tr("fiso-helper"),
                                                                   tr("Satzung speichern?"),
                                                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        switch (resBtn) {
        case QMessageBox::Save:
            this->on_actionSessionSave_triggered();
            event->accept();
            break;
        case QMessageBox::Discard:
            event->accept();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
        default:
            event->ignore();
            break;
        }
    }
}
