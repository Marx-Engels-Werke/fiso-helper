#ifndef HELPERMAINWINDOW_H
#define HELPERMAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QChar>
#include <QMessageBox>

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

private:
    Ui::helperMainWindow *ui;
    void resizeEvent(QResizeEvent*);
};
#endif // HELPERMAINWINDOW_H
