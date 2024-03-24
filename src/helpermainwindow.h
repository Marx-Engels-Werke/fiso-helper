#ifndef HELPERMAINWINDOW_H
#define HELPERMAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QChar>
#include <QTimer>
#include <QUrl>
#include <QtMultimedia/QSoundEffect>

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

    void setTimerWarning(int newTimerWarning);

private slots:

    // ui elements
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

    // menu elements
    void on_actionExit_triggered();

    void on_actionSettings_triggered();

    // communication handlers
    void timerWarningChangedHandler(int arg1);

    void timerWarningSoundHandler(bool arg1);

private:
    Ui::helperMainWindow *ui;
    QTimer *updateTimer = new QTimer();
    QTimer *speakerTimer = new QTimer();

    void resizeEvent(QResizeEvent*);
    void speakerTimeout();
    void updateProgress();

    int timerWarningDelay;
    bool timerWarningSoundEnabled;

    QSoundEffect ding;
    QSoundEffect dingdingding;
};
#endif // HELPERMAINWINDOW_H
