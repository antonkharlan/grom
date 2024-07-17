#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class dbconnect
{
public:
    static QSqlDatabase& instance() {
        static QSqlDatabase db;
        if (!db.isOpen()) {
            db = QSqlDatabase::addDatabase("QIBASE");
            db.setHostName("172.18.110.56");
            db.setDatabaseName("C:/ACS/Base/ACS.FDB");
            db.setUserName("ADM");
            db.setPassword("700");
            db.setPort(3050);

            if (!db.open()) {
                qCritical() << "Не удалось подключиться к базе данных:" << db.lastError().text();
            } else {
                qDebug() << "Соединение с базой данных успешно установлено";
            }
        }
        return db;
    }

private:
    dbconnect() {} // Запрещаем создание экземпляров этого класса
    ~dbconnect() {}
    dbconnect(const dbconnect&) = delete;
    dbconnect& operator=(const dbconnect&) = delete;
};

#endif // DBCONNECT_H
