#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDate>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("L:/Projects/Qt_test/Qt_db.db");
    db.setUserName("root");
    if (!db.open()) {
        qDebug() << db.lastError().text();
        return;
    } else {
        qDebug() << "Success";
    }

}
string MainWindow::getDataFromFile() {

    QFile file(path);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly))) {
        QString str="";
        while(!file.atEnd()) {
            str=str+file.readLine();
        }

        file.close();

        return str.toStdString();
    } else {
        qDebug() << path;
        con = false;
    }
}
MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_showButton_clicked() {
    QSqlQueryModel* query = new QSqlQueryModel;
//    while (con) {
    QString str = QString::fromStdString(getDataFromFile());
    query->setQuery(str);
    QTableView *tv = new QTableView(this);
    tv->setModel(query);
    ui->tableView->setModel(query);
    }
//}
