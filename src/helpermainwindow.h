#ifndef HELPERMAINWINDOW_H
#define HELPERMAINWINDOW_H

#include "session.h"

#include <QMainWindow>
#include <QListWidgetItem>
#include <QChar>
#include <QTimer>
#include <QUrl>
#include <QtMultimedia/QSoundEffect>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>

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

    void on_actionNewSession_triggered();

    void on_actionSessionSave_triggered();

    void on_actionSessionOpen_triggered();

    // communication handlers
    void timerWarningChangedHandler(int arg1);

    void timerWarningSoundHandler(bool arg1);

private:
    Ui::helperMainWindow *ui;
    QTimer *updateTimer = new QTimer(this);
    QTimer *speakerTimer = new QTimer(this);
    Session *session = new Session(this);

    int timerWarningDelay;
    bool timerWarningSoundEnabled;

    QSoundEffect ding;
    QSoundEffect dingdingding;

    void speakerTimeout();
    void updateProgress();

    void loadFromSession();
    void clearWindow();

    void exitNewDialog();

    // void resizeEvent(QResizeEvent*);
    void closeEvent(QCloseEvent *event);
};
#endif // HELPERMAINWINDOW_H
