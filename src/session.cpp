#include "session.h"

Session::Session(QObject *parent)
    : QObject{parent} {
    this->hasChanged = false;
    this->currentSpeaker = "";
}

bool Session::isChanged() {
    return this->hasChanged;
}

QString Session::getCurrentSpeaker() {
    return this->currentSpeaker;
}

QStringList Session::getSpeakerList() {
    return this->speakerList;
}

QString Session::getSpeakerListItem(int row) {
    return this->speakerList.at(row);
}

QStringList Session::getPresentList() {
    return this->presentList;
}

QString Session::getPresentListItem(int row) {
    return this->presentList.at(row);
}

int Session::getSpeakerListSize() {
    return this->speakerList.size();
}

int Session::getPresentListSize() {
    return this->presentList.size();
}

void Session::proceed() {
    if (this->speakerList.size() >= 1) {
        this->applyHasChanged();
        this->currentSpeaker = this->speakerList.takeFirst();
    }
}

void Session::addSpeaker(int present_row) {
    if (this->currentSpeaker == "") {
        this->applyHasChanged();
        this->currentSpeaker = this->presentList.at(present_row);
    }
    else {
        this->applyHasChanged();
        this->speakerList.append(this->presentList.at(present_row));
    }
}

void Session::removeSpeaker(int row) {
    this->applyHasChanged();
    this->speakerList.removeAt(row);
}

void Session::moveSpeakerUp(int row) {
    this->applyHasChanged();
    this->speakerList.move(row, row - 1);
}

void Session::moveSpeakerDown(int row) {
    this->applyHasChanged();
    this->speakerList.move(row, row + 1);
}

void Session::addPresent(const QString &str) {
    this->applyHasChanged();
    this->presentList.append(str);
    this->presentList.sort(Qt::CaseInsensitive);
}

void Session::removePresent(int row) {
    this->applyHasChanged();
    this->presentList.removeAt(row);
}

bool Session::save(const QString &filename, QWidget *parent) {
    QSaveFile file(filename);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(parent, tr("Unable to save file"),
                                 file.errorString());
        return false;
    }

    QDataStream out(&file);

    out << this->currentSpeaker;
    out << this->speakerList;
    out << this->presentList;

    file.commit();
    return true;
}

bool Session::load(const QString &filename, QWidget *parent) {
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(parent, tr("Unable to open file"),
                                 file.errorString());
        return false;
    }

    QDataStream in(&file);

    in >> this->currentSpeaker;
    in >> this->speakerList;
    in >> this->presentList;

    file.close();
    return true;
}

void Session::applyHasChanged() {
    if (!this->hasChanged)
        this->hasChanged = true;
}

void Session::applyNotChanged() {
    if (this->hasChanged)
        this->hasChanged = false;
}
