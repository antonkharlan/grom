#include "showinfo.h"
#include "ui_showinfo.h"
#include <QDebug>
#include "mainapp.h"
#include <QCloseEvent>
ShowInfo::ShowInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShowInfo)
{
    ui->setupUi(this);
}

ShowInfo::~ShowInfo()
{
    delete ui;
}

void ShowInfo::slot(QPixmap a)
{
    qDebug() << "Слот slot вызывается";

    if (!a.isNull()) {
        ui->photo->setPixmap(a);
        ui->photo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    } else {
        qDebug() << "Получен пустой QPixmap";
    }
}

void ShowInfo::slotname(QString name, QString mobilephone, QString mail, QString department, QString car, QString tablenomer, QString doljnost)
{
    qDebug() << "Слот slotname вызывается";
    ui->label->setText(name);
    ui->label_7->setText(mobilephone);
    ui->label_12->setText(mail);
    ui->label_9->setText(department);
    ui->label_15->setText(car);
    ui->label_6->setText(tablenomer);
    ui->label_11->setText(doljnost);
}
// void ShowInfo::closeEvent(QCloseEvent *event)
// {
//     // Создаем экземпляр MainWindow и показываем его
//     MainApp *mainapp = new MainApp();
//     mainapp->show();

//     // Закрываем текущее окно ScanWindow
//     event->accept();
// }

