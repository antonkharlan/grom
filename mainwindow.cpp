#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QSettings>
#include <QCoreApplication>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();
    ui->centralwidget->setAttribute(Qt::WA_TranslucentBackground);
    ui->centralwidget->setStyleSheet("backgroung-color: rgba(0,0,0,0);");
    QPixmap pix("C:/Users/bystr/Documents/Autorization/img/user.png");
    ui->image->setPixmap(pix.scaled(128,128, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->image->setStyleSheet("background-color: transparent;");

    ui->lineEdit->setPlaceholderText(QApplication::translate("Form", "employer@gmail.com", 0));
    ui->lineEdit_2->setPlaceholderText(QApplication::translate("Form", "password", 0));
    ui->pushButton->setShortcut(QKeySequence(Qt::Key_Return));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Получаем текст из lineEdit (логин)
    QString login = ui->lineEdit->text();

    // Получаем текст из lineEdit_2 (пароль)
    QString password = ui->lineEdit_2->text();

    // Предположим, у вас есть ожидаемые значения логина и пароля
    QString expectedLogin = "Login";
    QString expectedPassword = "Password";

    // Проверяем введенные логин и пароль
    if (login == expectedLogin && password == expectedPassword)
    {
        QSettings settings("MyCompany", "MyApp");
        settings.setValue("RememberMe", ui->checkBox->isChecked());
        if (ui->checkBox->isChecked()) {
            settings.setValue("Login", login);
            settings.setValue("Password", password);
        } else {
            // Если чекбокс не выбран, удаляем сохраненные данные
            settings.remove("Login");
            settings.remove("Password");}
        // Логин и пароль верные, открываем новое окно PanelWindow
        this->hide();
        mainapp = new MainApp(this);
        mainapp->show();
        // panel panelWindow;
        // panelWindow.setModal(true);

        //panelWindow.exec();
    }
    else
    {
        this->hide();

        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
    }
}


void MainWindow::loadSettings()
{
    // Загружаем сохраненное состояние чекбокса "Запомнить меня"
    QSettings settings("MyCompany", "MyApp");
    bool rememberMe = settings.value("RememberMe", false).toBool();

    // Устанавливаем состояние чекбокса из сохраненных настроек
    ui->checkBox->setChecked(rememberMe);

    // Если чекбокс был выбран, загружаем также сохраненные логин и пароль
    if (rememberMe) {
        QString savedLogin = settings.value("Login").toString();
        QString savedPassword = settings.value("Password").toString();

        // Устанавливаем сохраненные логин и пароль в соответствующие lineEdit
        ui->lineEdit->setText(savedLogin);
        ui->lineEdit_2->setText(savedPassword);
    }
}

