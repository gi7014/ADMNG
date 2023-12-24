QT       += core gui
RC_ICONS = logo.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QRibbon/QRibbon.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CPerson.h \
    QRibbon/QRibbon.h \
    mainwindow.h

FORMS += \
    QRibbon/qribbon.ui \
    mainwindow.ui

TRANSLATIONS += \
    tx_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    QRibbon/QRibbon.qrc \
    Resources/resources.qrc

DISTFILES += \
    QRibbon/Resource/icon/add_bottom.png \
    QRibbon/Resource/icon/add_left.png \
    QRibbon/Resource/icon/add_right.png \
    QRibbon/Resource/icon/add_top.png \
    QRibbon/Resource/icon/arrowBottom.png \
    QRibbon/Resource/icon/branch-closed.png \
    QRibbon/Resource/icon/branch-end.png \
    QRibbon/Resource/icon/branch-more.png \
    QRibbon/Resource/icon/branch-open.png \
    QRibbon/Resource/icon/branch_close.png \
    QRibbon/Resource/icon/branch_open.png \
    QRibbon/Resource/icon/calendar_nextmonth.png \
    QRibbon/Resource/icon/calendar_prevmonth.png \
    QRibbon/Resource/icon/checkbox_checked.png \
    QRibbon/Resource/icon/checkbox_checked_disable.png \
    QRibbon/Resource/icon/checkbox_parcial.png \
    QRibbon/Resource/icon/checkbox_parcial_disable.png \
    QRibbon/Resource/icon/checkbox_unchecked.png \
    QRibbon/Resource/icon/checkbox_unchecked_disable.png \
    QRibbon/Resource/icon/downarrow.png \
    QRibbon/Resource/icon/eye.png \
    QRibbon/Resource/icon/eyeClosed.png \
    QRibbon/Resource/icon/eyeClosed0.png \
    QRibbon/Resource/icon/radiobutton_checked.png \
    QRibbon/Resource/icon/radiobutton_checked_disable.png \
    QRibbon/Resource/icon/radiobutton_unchecked.png \
    QRibbon/Resource/icon/radiobutton_unchecked_disable.png \
    QRibbon/Resource/icon/unknow.png \
    QRibbon/Resource/icon/uparrow.png \
    QRibbon/Resource/icon/vline.png \
    Resources/imgs/hfut.jpg \
    Resources/imgs/homePage.png
