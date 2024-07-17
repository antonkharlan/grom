#include "mainapp.h"
#include "ui_mainapp.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDebug>
#include <QVector>

MainApp::MainApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainApp)
    , showinfo(nullptr)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    QSqlDatabase db = QSqlDatabase::addDatabase("QIBASE");
    db.setHostName("172.18.110.56");
    db.setDatabaseName("C:/ACS/Base/ACS.FDB");
    db.setUserName("ADM");
    db.setPassword("700");
    db.setPort(3050);

    if (!db.open()) {
        QMessageBox::critical(this, "Ошибка соединения", "Не удалось подключиться к базе данных.");
        return;
    }

    QSqlQuery query1;
    if (!query1.exec("SELECT FIO, DEPARTMENT, MOBILE, MAIL, START_D, NIO, AUTO FROM PERSONNEL")) {
        QMessageBox::critical(this, "Ошибка запроса", "Не удалось выполнить запрос к базе данных: " + query1.lastError().text());
        db.close();
        return;
    }

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels({"ФИО", "Отдел", "Мобильный", "Email", "Дата начала работы", "НИО", "Автомобиль"});

    int row = 0;
    while (query1.next()) {
        ui->tableWidget->insertRow(row);
        QSqlRecord record = query1.record();
        for (int col = 0; col < record.count(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(record.value(col).toString());
            ui->tableWidget->setItem(row, col, item);
        }
        ++row;
    }

    db.close();
}

MainApp::~MainApp()
{
    delete ui;
    if (showinfo) {
        delete showinfo;
    }
}

void MainApp::on_tableWidget_cellDoubleClicked(int row, int /*column*/)
{
    if (showinfo) {
        delete showinfo;
        showinfo = nullptr;
    }
    if (!showinfo) {
        showinfo = new ShowInfo;
        connect(this, &MainApp::signal, showinfo, &ShowInfo::slot);
        connect(this, &MainApp::signalname, showinfo, &ShowInfo::slotname);
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QIBASE");
    db.setHostName("172.18.110.56");
    db.setDatabaseName("C:/ACS/Base/ACS.FDB");
    db.setUserName("ADM");
    db.setPassword("700");
    db.setPort(3050);

    if (!db.open()) {
        QMessageBox::critical(this, "Ошибка соединения", "Не удалось подключиться к базе данных.");
        return;
    }

    QString fio = ui->tableWidget->item(row, 0)->text();
    QString department = ui->tableWidget->item(row, 1)->text();
    QString mobile = ui->tableWidget->item(row, 2)->text();
    QString mail = ui->tableWidget->item(row, 3)->text();
    QString automobile = ui->tableWidget->item(row, 6)->text();
    // QString NewMobile[][];
    // for(int i = 0; i<sizeof(mobile)/8; i++)
    // {
    //     if(mobile[i] == ";"){
    //     myVector.push_back(massive[i]);
    //     }
    //     }
    //     myVector.push_back(massive[i]);
    //     qDebug() << "Value " << i << ": " << myVector.value(i);
    // }
    // for(int i {0}; i<sizeof(mobile)/8, i++){
    //     if(mobile[i] == ";"){
    //         mobile[i] = ;
    //     }
    // }
    if(automobile == "")
    {
        automobile = "нет автомобиля";
    }
    QString tabelnomer, doljnost;
    QSqlQuery query;
    query.prepare("SELECT FOTO, TABELNOMER, DOLJNOST FROM PERSONNEL WHERE FIO = :fio");
    query.bindValue(":fio", fio);

    if (query.exec() && query.next()) {
        QByteArray imageData = query.value(0).toByteArray();
        tabelnomer = query.value(1).toString();

        // for(int i {4}; i<7;i++){
        //     phone[i-4]=tabelnomer[i];
        // }
        // for(int i {14}; i<18;i++){
        //     cabinet[i-14]=tabelnomer[i];
        // }

        doljnost = query.value(2).toString();
        QPixmap pixmap;
        if (!pixmap.loadFromData(imageData)) {
            qDebug() << "Ошибка загрузки изображения из данных";
            return;
        }

        showinfo->show();
        emit signal(pixmap);
        emit signalname(fio, mobile, department, mail, automobile, tabelnomer, doljnost);
    } else {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    }

    db.close();
}
