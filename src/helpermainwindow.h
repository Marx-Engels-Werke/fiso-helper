#ifndef HELPERMAINWINDOW_H
#define HELPERMAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QChar>
#include <QMessageBox>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class helperMainWindow;
}
QT_END_NAMESPACE

class helperMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    helperMainWindow(QWidget *parent = nullptr);
    ~helperMainWindow();

private slots:
    void on_addPresentButton_clicked();

    void on_inputPresentEditBox_returnPressed();

    void on_presentList_itemDoubleClicked(QListWidgetItem *item);

    void on_removePresentButton_clicked();

    void on_removeSpeakerButton_clicked();

    void on_removeCurrentSpeakerButton_clicked();

    void on_moveSpeakerUpButton_clicked();

    void on_moveSpeakerDownButton_clicked();

    void on_timerEdit_userTimeChanged(const QTime &time);

    void on_timerGoButton_clicked();

    void on_timerStopButton_clicked();

private:
    Ui::helperMainWindow *ui;
    QTimer *updateTimer = new QTimer();
    QTimer *speakerTimer = new QTimer();

    void resizeEvent(QResizeEvent*);
    void speakerTimeout();
    void updateProgress();
};
#endif // HELPERMAINWINDOW_H
