#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CPerson.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void initialWin();

private slots:
    void hideAll();

    void on_backHomePage_triggered();

    void on_addContact_triggered();

    void on_loadContact_triggered();

    void on_storeContact_triggered();

    void on_modifyContact_triggered();

    void on_deleteContact_triggered();

    void on_showContact_triggered();

    void on_searchContact_triggered();

    void on_addContactAdd_triggered();

    void on_addContactReset_triggered();

    void on_searchContactStart_triggered();

    void on_loadContactSelect_triggered();

    void on_loadContactRead_triggered();

    void on_modifyContactSearch_triggered();

    void on_modifyContactSave_triggered();

    void on_deleteContactSearch_triggered();

    void on_deleteContactDelete_triggered();

    void on_storeContactSave_triggered();

    void on_storeContactReset_triggered();

    void on_storeContactSelectRoot_triggered();

    void on_about_triggered();

private:
    Ui::MainWindow *ui;
    CPerson *modifyNode;
};
#endif // MAINWINDOW_H
