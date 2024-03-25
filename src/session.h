#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QFile>
#include <QSaveFile>
#include <QMessageBox>
#include <QCryptographicHash>

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QObject *parent = nullptr);

    bool isChanged();

    QString getCurrentSpeaker();
    QStringList getSpeakerList();
    QString getSpeakerListItem(int row);
    QStringList getPresentList();
    QString getPresentListItem(int row);
    int getSpeakerListSize();
    int getPresentListSize();

    void proceed();
    void addSpeaker(int present_row);
    void removeSpeaker(int row);
    void moveSpeakerUp(int row);
    void moveSpeakerDown(int row);
    void addPresent(const QString &str);
    void removePresent(int row);

    bool save(const QString &filename, QWidget *parent);
    bool load(const QString &filename, QWidget *parent);

    void applyHasChanged();
    void applyNotChanged();

private:
    bool hasChanged;

    QString currentSpeaker;
    QStringList speakerList;
    QStringList presentList;
};

#endif // SESSION_H
