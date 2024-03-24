# fiso-helper Qt project file
# Application version
VERSION_MAJOR = 1
VERSION_MINOR = 5
VERSION_BUILD = 0

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
           "VERSION_MINOR=$$VERSION_MINOR"\
           "VERSION_BUILD=$$VERSION_BUILD"

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/settingsdialog.cpp \
    src/main.cpp \
    src/helpermainwindow.cpp

HEADERS += \
    src/settingsdialog.h \
    src/helpermainwindow.h \

FORMS += \
    src/forms/helpermainwindow.ui \
    src/forms/settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
