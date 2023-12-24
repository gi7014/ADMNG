#include "mainwindow.h"
#include "CPerson.h"

#include <QPushButton>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "txl_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.initialWin();
    w.setWindowTitle("通讯录管理系统");
    w.show();
    return a.exec();
}
