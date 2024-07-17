#include "panel.h"
#include "ui_panel.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>
panel::panel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::panel)
{
    ui->setupUi(this);

    // Устанавливаем имя драйвера для работы с Firebird
    QSqlDatabase db = QSqlDatabase::addDatabase("QIBASE");

    // Устанавливаем параметры подключения к базе данных
    db.setHostName("172.18.110.56");
    db.setDatabaseName("C:/ACS/Base/ACS.FDB"); // Путь к файлу базы данных
    db.setUserName("ADM");
    db.setPassword("700");
    db.setPort(3050);

    // Пытаемся открыть соединение с базой данных
    if (!db.open()) {
        QMessageBox::critical(this, "Ошибка соединения", "Не удалось подключиться к базе данных.");
        return;
    }


    QSqlQuery query1;
    if (!query1.exec("SELECT FIO,DEPARTMENT,MOBILE,MAIL,START_D,NIO,AUTO FROM PERSONNEL")) {
        QMessageBox::critical(this, "Ошибка запроса", "Не удалось выполнить запрос к базе данных: " + query1.lastError().text());
        db.close();
        return;
    }

    // Очищаем содержимое QTableWidget перед загрузкой новых данных
 // Устанавливаем количество строк равным 0
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0); // Устанавливаем количество строк равным 0

    // Задаем пользовательские заголовки столбцов
    ui->tableWidget->setColumnCount(7); // Устанавливаем количество столбцов

    // Устанавливаем заголовки столбцов
    ui->tableWidget->setHorizontalHeaderLabels({"ФИО", "Отдел", "Мобильный", "Email", "Дата начала работы", "НИО", "Автомобиль"});
    // Заполняем QTableWidget данными из результата запроса
    int row = 0;
    while (query1.next()) {
        ui->tableWidget->insertRow(row);

        // Добавляем данные в ячейки QTableWidget
        QSqlRecord record = query1.record(); // Получаем запись результата запроса
        for (int col = 0; col < record.count(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(record.value(col).toString());
            ui->tableWidget->setItem(row, col, item);
        }

        ++row;
    }

    // Закрываем соединение с базой данных
    db.close();

}

panel::~panel()
{
    qDebug() << QSqlDatabase::drivers();
    delete ui;
}

void panel::on_toolButton_triggered(QAction *arg1)
{

}

