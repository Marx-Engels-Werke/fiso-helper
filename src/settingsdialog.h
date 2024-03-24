#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit settingsDialog(int timerWarn, bool timerSound, QWidget *parent = nullptr);
    ~settingsDialog();

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:

    void timerWarningDelayChanged(int a);

    void timerWarningSoundChanged(bool a);

private:

    Ui::settingsDialog *ui;

};

#endif // SETTINGSDIALOG_H
