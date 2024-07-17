#ifndef MAINAPP_H
#define MAINAPP_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include "showinfo.h"

namespace Ui {
class MainApp;
}

class MainApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainApp(QWidget *parent = nullptr);
    ~MainApp();

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::MainApp *ui;
    ShowInfo *showinfo = nullptr;

signals:
    void signal(QPixmap a);
    void signalname(QString name, QString mobilephone, QString mail, QString department, QString car, QString &tablenomer, QString &doljnost);
};

#endif // MAINAPP_H
