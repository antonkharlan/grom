#ifndef PANEL_H
#define PANEL_H

#include <QDialog>
#include <QObject>
namespace Ui {
class panel;
}

class panel : public QDialog
{
    Q_OBJECT

public:
    explicit panel(QWidget *parent = nullptr);
    ~panel();


private slots:
    void on_toolButton_triggered(QAction *arg1);

private:
    Ui::panel *ui;
};

#endif // PANEL_H
