#include "mainwindow.h"
#include "CPerson.h"
#include "./ui_mainwindow.h"
#include "./QRibbon/QRibbon.h"

#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <sstream>

CPerson *head = new CPerson;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
    QRibbon::install(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hideAll() {
    ui->homePageWidget->hide();
    ui->addContactWidget->hide();
    ui->showContactWidget->hide();
    ui->checkContactWidget->hide();
    ui->storeContactWidget->hide();
    ui->loadContactWidget->hide();
    ui->deleteContactWidget->hide();
    ui->modifyContactWidget->hide();
    ui->aboutWidget->hide();
}

void MainWindow::initialWin() {
    hideAll();
    ui->homePageWidget->show();
    QPixmap pix(":/images/imgs/hfut.jpg");
    pix = pix.scaled(ui->hfutLabel->size());
    ui->hfutLabel->setPixmap(pix);
}

void MainWindow::on_backHomePage_triggered()
{
    hideAll();
    ui->homePageWidget->show();
}


void MainWindow::on_addContact_triggered()
{
    hideAll();
    ui->addContactWidget->show();
}


void MainWindow::on_addContactReset_triggered()
{
    ui->addNameLineEdit->clear();
    ui->addPhoneLineEdit->clear();
    ui->addZipLineEdit->clear();
    ui->addAddressPlainEdit->clear();
    QMessageBox resetTip(QMessageBox::Question, "提示", "成功重置文本框！", QMessageBox::Yes);
    resetTip.exec();
}


void MainWindow::on_addContactAdd_triggered()
{
    if (ui->addNameLineEdit->text() == "" || ui->addPhoneLineEdit->text() == "" || ui->addZipLineEdit->text() == "" || ui->addAddressPlainEdit->toPlainText() == "") {
        QMessageBox emptyTip(QMessageBox::Question, "提示", "有文本为空，请检查！", QMessageBox::Yes);
        emptyTip.exec();
    } else {
        CPerson *node = new CPerson;
        node->name = ui->addNameLineEdit->text();
        node->Phone_number = ui->addPhoneLineEdit->text();
        node->Postal_code = ui->addZipLineEdit->text();
        node->address = ui->addAddressPlainEdit->toPlainText();

        CPerson *t = head->next;
        head->next = node;
        node->next = t;
        QMessageBox addSucessTip(QMessageBox::Question, "提示", "添加成功！", QMessageBox::Yes);
        addSucessTip.exec();
    }
}


void MainWindow::on_showContact_triggered()
{
    hideAll();
    ui->showContactWidget->show();
    CPerson *node = head->next;
    if (node == NULL) {
        ui->label_9->show();
        ui->contactTableWidget->hide();
    }
    else {
        ui->label_9->hide();
        ui->contactTableWidget->verticalHeader()->setHidden(true);
        ui->contactTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->contactTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        int contactNum = 0, row = 0;
        while (node) {
            contactNum++;
            node = node->next;
        }
        node = head->next;
        ui->contactTableWidget->setRowCount(contactNum);
        while (node) {
            int column = 0;
            ui->contactTableWidget->setItem(row, column, new QTableWidgetItem(node->name));
            column++;
            ui->contactTableWidget->setItem(row, column, new QTableWidgetItem(node->Phone_number));
            column++;
            ui->contactTableWidget->setItem(row, column, new QTableWidgetItem(node->Postal_code));
            column++;
            ui->contactTableWidget->setItem(row, column, new QTableWidgetItem(node->address));
            row++;
            node = node->next;
        }
        ui->contactTableWidget->show();
    }
}


void MainWindow::on_searchContact_triggered()
{
    hideAll();
    ui->checkContactWidget->show();
}


void MainWindow::on_searchContactStart_triggered()
{
    ui->checkNameLineEdit->setReadOnly(true);
    ui->checkPhoneLineEdit->setReadOnly(true);
    ui->checkZipLineEdit->setReadOnly(true);
    ui->checkAddressLineEdit->setReadOnly(true);
    QString searchedItem = ui->searchedLineEdit->text();
    int itemSelect = ui->comboBox->currentIndex();
    CPerson *node = head->next;
    if (node == NULL) {
        QMessageBox nullTip(QMessageBox::Question, "提示", "通讯录中无联系人！", QMessageBox::Yes);
        nullTip.exec();
    } else {
        bool find = false;
        QMessageBox noTip(QMessageBox::Question, "提示", "未查找到相关资料！", QMessageBox::Yes);
        switch (itemSelect) {
        case 0:
            while (node) {
                if (node->name == searchedItem) {
                    ui->checkNameLineEdit->setText(QString(node->name));
                    ui->checkPhoneLineEdit->setText(QString(node->Phone_number));
                    ui->checkZipLineEdit->setText(QString(node->Postal_code));
                    ui->checkAddressLineEdit->setPlainText(QString(node->address));
                    find = true;
                }
                node = node->next;
            }
            if (find == false) {
                noTip.exec();
            }
            break;
        case 1:
            while (node) {
                if (node->Phone_number == searchedItem) {
                    ui->checkNameLineEdit->setText(QString(node->name));
                    ui->checkPhoneLineEdit->setText(QString(node->Phone_number));
                    ui->checkZipLineEdit->setText(QString(node->Postal_code));
                    ui->checkAddressLineEdit->setPlainText(QString(node->address));
                    find = true;
                }
                node = node->next;
            }
            if (find == false) {
                noTip.exec();
            }
            break;
        case 2:
            while (node) {
                if (node->Postal_code == searchedItem) {
                    ui->checkNameLineEdit->setText(QString(node->name));
                    ui->checkPhoneLineEdit->setText(QString(node->Phone_number));
                    ui->checkZipLineEdit->setText(QString(node->Postal_code));
                    ui->checkAddressLineEdit->setPlainText(QString(node->address));
                    find = true;
                }
                node = node->next;
            }
            if (find == false) {
                noTip.exec();
            }
            break;
        case 3:
            while (node) {
                if (node->address == searchedItem) {
                    ui->checkNameLineEdit->setText(QString(node->name));
                    ui->checkPhoneLineEdit->setText(QString(node->Phone_number));
                    ui->checkZipLineEdit->setText(QString(node->Postal_code));
                    ui->checkAddressLineEdit->setPlainText(QString(node->address));
                    find = true;
                }
                node = node->next;
            }
            if (find == false) {
                noTip.exec();
            }
            break;
        default:
            break;
        }
    }
}


void MainWindow::on_storeContact_triggered()
{
    hideAll();
    QString path = QDir::currentPath();
    ui->saveFileRootPlainTextEdit->setPlainText(path);
    ui->saveFileRootPlainTextEdit->setReadOnly(true);
    ui->storeContactWidget->show();
}


void MainWindow::on_storeContactReset_triggered()
{
    QString path = QDir::currentPath();
    ui->saveFileRootPlainTextEdit->setPlainText(path);
    ui->saveFileNameLineEdit->clear();
    QMessageBox resetTip(QMessageBox::Question, "提示", "已成功重置！", QMessageBox::Yes);
    resetTip.exec();
}


void MainWindow::on_storeContactSelectRoot_triggered()
{
    QString path = QFileDialog::getExistingDirectory(this, "请选择保存的位置", "/");
    if (path.isEmpty()) return;
    else {
        ui->saveFileRootPlainTextEdit->setPlainText(path + "/");
        QMessageBox successSaved(QMessageBox::Question, "提示", "已成功修改保存位置！", QMessageBox::Yes);
        successSaved.exec();
    }
}


void MainWindow::on_storeContactSave_triggered()
{
    QString path = ui->saveFileRootPlainTextEdit->toPlainText();
    QString Filename = ui->saveFileNameLineEdit->text() + ".csv";
    QString file = path + Filename;
    std::fstream csv;
    csv.open(file.toLocal8Bit().constData(), std::ios::app);
    if (!csv.is_open()) {
        QMessageBox warnningTip(QMessageBox::Warning, "警告", "文件打开失败！", QMessageBox::Yes);
        warnningTip.exec();
    } else {
        csv << QString("姓名").toLocal8Bit().constData() << ","
            << QString("电话").toLocal8Bit().constData() << ","
            << QString("邮编").toLocal8Bit().constData() << ","
            << QString("住址").toLocal8Bit().constData() << std::endl;
        CPerson *node = head->next;
        while (node) {
            csv << node->name.toLocal8Bit().constData() << ","
                << node->Phone_number.toLocal8Bit().constData() << ","
                << node->Postal_code.toLocal8Bit().constData() << ","
                << node->address.toLocal8Bit().constData() << std::endl;
            node = node->next;
        }
        csv.close();
        QMessageBox successSaved(QMessageBox::Question, "提示", "保存成功！", QMessageBox::Yes);
        successSaved.exec();
    }
}


void MainWindow::on_loadContact_triggered()
{
    hideAll();
    ui->loadContactWidget->show();
}


void MainWindow::on_loadContactSelect_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, "请选择csv文件", "./", "csv文件(*.csv)");
    if (path.isEmpty()) return;
    std::ifstream csv(path.toLocal8Bit().constData(), std::ios::in);
    if (!csv.is_open()) {
        QMessageBox warnningTip(QMessageBox::Warning, "警告", "打开文件失败！", QMessageBox::Yes);
        warnningTip.exec();
    } else {
        ui->csvPathLineEdit->setText(path);
        csv.close();
    }
}


void MainWindow::on_loadContactRead_triggered()
{
    QString path = ui->csvPathLineEdit->text();
    std::ifstream csv(path.toLocal8Bit().constData(), std::ios::in);
    std::string line;
    CPerson *p = head;
    std::getline(csv, line);
    while (std::getline(csv, line)) {
        QStringList fields = QString::fromLocal8Bit(line).split(",");

        CPerson *node = new CPerson;

        if (fields.size() >= 4) {
            node->name = fields[0];
            ui->loadProgressPlainTextEdit->appendPlainText(QString("姓名：") + QString(fields[0]) + "\t");

            node->Phone_number = fields[1];
            ui->loadProgressPlainTextEdit->appendPlainText(QString("电话：") + QString(fields[1]) + "\t");

            node->Postal_code = fields[2];
            ui->loadProgressPlainTextEdit->appendPlainText(QString("邮编：") + QString(fields[2]) + "\t");

            node->address = fields[3];
            ui->loadProgressPlainTextEdit->appendPlainText(QString("住址：") + QString(fields[3]) + "\t");
        }

        p->next = node;
        p = node;
        ui->loadProgressPlainTextEdit->appendPlainText(QString('\n'));
    }
    ui->loadProgressPlainTextEdit->appendPlainText(QString("读取完毕！"));
    QMessageBox successLoaded(QMessageBox::Question, "提示", "读取完毕！", QMessageBox::Yes);
    successLoaded.exec();
}


void MainWindow::on_deleteContact_triggered()
{
    hideAll();
    ui->deleteContactWidget->show();
}


void MainWindow::on_deleteContactSearch_triggered()
{
    int deleteItem = ui->deleteContactComboBox->currentIndex();
    QString deleteInfo = ui->deleteContactInfoLineEdit->text();
    ui->deleteContactTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->deleteContactTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    CPerson *node = head->next;
    if (node == NULL) {
        QMessageBox noMember(QMessageBox::Warning, "警告", "通讯录中无联系人！", QMessageBox::Yes);
        noMember.exec();
        return;
    }

    CPerson *array[20];
    int i = 0;

    switch (deleteItem) {
    case 0:
        while (node) {
            if (node->name == deleteInfo) {
                array[i] = node;
                i++;
            }
            node = node->next;
        }
        break;
    case 1:
        while (node) {
            if (node->Phone_number == deleteInfo) {
                array[i] = node;
                i++;
            }
            node = node->next;
        }
        break;
    case 2:
        while (node) {
            if (node->Postal_code == deleteInfo) {
                array[i] = node;
                i++;
            }
            node = node->next;
        }
        break;
    case 3:
        while (node) {
            if (node->address == deleteInfo) {
                array[i] = node;
                i++;
            }
            node = node->next;
        }
        break;
    default:
        break;
    }

    if (i == 0) {
        QMessageBox noMember(QMessageBox::Warning, "警告", "通讯录中无联系人！", QMessageBox::Yes);
        noMember.exec();
        return;
    }
    else {
        ui->deleteContactTableWidget->setRowCount(i);
        for (int j = 0;j < i; j++) {
            int k = 0;
            ui->deleteContactTableWidget->setItem(j, k, new QTableWidgetItem(array[j]->name));
            k++;
            ui->deleteContactTableWidget->setItem(j, k, new QTableWidgetItem(array[j]->Phone_number));
            k++;
            ui->deleteContactTableWidget->setItem(j, k, new QTableWidgetItem(array[j]->Postal_code));
            k++;
            ui->deleteContactTableWidget->setItem(j, k, new QTableWidgetItem(array[j]->address));
        }
        QMessageBox finded(QMessageBox::Question, "提示", "查找完毕！", QMessageBox::Yes);
        finded.exec();
        return;
    }
}


void MainWindow::on_deleteContactDelete_triggered()
{
    int currentRow = ui->deleteContactTableWidget->currentIndex().row();
    if (currentRow == -1) {
        QMessageBox war(QMessageBox::Warning, "警告", "请先选择一个要删除的联系人！", QMessageBox::Yes);
        war.exec();
        return;
    } else {
        QString name = ui->deleteContactTableWidget->item(currentRow, 0)->text();
        QString phone = ui->deleteContactTableWidget->item(currentRow, 1)->text();
        QString zip = ui->deleteContactTableWidget->item(currentRow, 2)->text();
        QString address = ui->deleteContactTableWidget->item(currentRow, 3)->text();
        CPerson *node = head;
        while (node->next) {
            if (QString(node->next->name) == name &&
                QString(node->next->Phone_number) == phone &&
                QString(node->next->Postal_code) == zip &&
                QString(node->next->address) == address) {
                QMessageBox isDelete(QMessageBox::Question, "提示", "是否删除？", QMessageBox::Yes | QMessageBox::No);
                int ret = isDelete.exec();
                if (ret == QMessageBox::Yes) {
                    if (node->next->next == NULL) {
                        node->next = NULL;
                    } else {
                        node->next = node->next->next;
                    }
                    QMessageBox successDelete(QMessageBox::Question, "提示", "删除成功！", QMessageBox::Yes);
                    successDelete.exec();
                    ui->deleteContactTableWidget->clear();
                    ui->deleteContactTableWidget->setRowCount(0);
                    break;
                } else {
                    return;
                }
            }
            node = node->next;
        }
        return;
    }
}


void MainWindow::on_modifyContact_triggered()
{
    hideAll();
    ui->modifyContactWidget->show();
}


void MainWindow::on_modifyContactSearch_triggered()
{
    int modifyItem = ui->comboBox_2->currentIndex();
    QString modifyInfo = ui->modifyInfoLineEdit->text();

    CPerson *node = head->next;
    bool find = false;

    switch (modifyItem) {
    case 0:
        while (node) {
            if (node->name == modifyInfo) {
                find = true;
                break;
            }
            node = node->next;
        }
        break;
    case 1:
        while (node) {
            if (node->Phone_number == modifyInfo) {
                find = true;
                break;
            }
            node = node->next;
        }
        break;
    case 2:
        while (node) {
            if (node->Postal_code == modifyInfo) {
                find = true;
                break;
            }
            node = node->next;
        }
        break;
    case 3:
        while (node) {
            if (node->address == modifyInfo) {
                find = true;
                break;
            }
            node = node->next;
        }
        break;
    default:
        break;
    }
    if (find == false) {
        QMessageBox didntFind(QMessageBox::Question, "提示", "未查找到该联系人", QMessageBox::Yes);
        didntFind.exec();
        return;
    } else {
        QString name = node->name;
        QString phone = node->Phone_number;
        QString zip = node->Postal_code;
        QString address = node->address;
        ui->nameModifyLineEdit->setText(name);
        ui->phoneModifyLineEdit->setText(phone);
        ui->zipModifyLineEdit->setText(zip);
        ui->addressModifyPlainTextEdit->setPlainText(address);
        modifyNode = node;
        return;
    }
}


void MainWindow::on_modifyContactSave_triggered()
{
    if (ui->nameModifyLineEdit->text().isEmpty() || ui->phoneModifyLineEdit->text().isEmpty() || ui->zipModifyLineEdit->text().isEmpty() || ui->addressModifyPlainTextEdit->toPlainText().isEmpty()) {
        QMessageBox noModify(QMessageBox::Question, "提示", "未选择联系人或有项目为空");
        noModify.exec();
        return;
    } else {
        modifyNode->name = ui->nameModifyLineEdit->text();
        modifyNode->Phone_number = ui->phoneModifyLineEdit->text();
        modifyNode->Postal_code = ui->zipModifyLineEdit->text();
        modifyNode->address = ui->addressModifyPlainTextEdit->toPlainText();
        QMessageBox Modified(QMessageBox::Question, "提示", "修改完毕！", QMessageBox::Yes);
        Modified.exec();
        ui->nameModifyLineEdit->clear();
        ui->phoneModifyLineEdit->clear();
        ui->zipModifyLineEdit->clear();
        ui->addressModifyPlainTextEdit->clear();
        return;
    }
}

void MainWindow::on_about_triggered()
{
    hideAll();
    ui->aboutTextEdit->setReadOnly(true);
    ui->aboutWidget->show();
}

