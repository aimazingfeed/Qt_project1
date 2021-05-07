#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDateTime>
#include <QFileInfoList>
#include <QtAlgorithms>


using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QSqlDatabase db;

//    QSqlTableModel* model;
//    QSqlQueryModel* query;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("L:/Projects/Qt_test/Qt_db.db");
    db.setUserName("root");


    if (!db.open()) {
        qDebug() << db.lastError().text();
        return;
    } else {
        qDebug() << "Success";
    }

    dir.setPath("L:/Projects/Project_Qt1");
    dir.setNameFilters(filters);
    QFileInfoList list = dir.entryInfoList(QDir::Files,QDir::Time);
    qDebug() << "list size " << list.size();

    pathsFiles = sort(list);
    for (auto i:pathsFiles)
    {
        qDebug() << QString::fromStdString(i);
    }


}

std::vector<std::string> MainWindow::sort(const QFileInfoList& list) {
    vector<std::string> buf;
    for (size_t i = 0;i<list.size(); ++i) {
        buf.push_back((list[i].absoluteFilePath()).toStdString());
    }
    for (size_t i = 0;i<buf.size(); ++i) {
        for (size_t i = 1;i<buf.size(); ++i) {
            if (isSecondEarlier(QString::fromStdString(buf[i-1]),QString::fromStdString(buf[i]))) {
                swap(buf[i-1],buf[i]);
            }
        }
    }
    return buf;

}




bool MainWindow::isSecondEarlier(QString first, QString second) {
    string strFirst, strSecond;
    strFirst = first.toStdString();
    strFirst.erase(strFirst.end()-4,strFirst.end());
    strFirst.erase(0,strFirst.find_last_of('/')+1);

    strSecond = second.toStdString();
    strSecond.erase(strSecond.end()-4,strSecond.end());
    strSecond.erase(0,strSecond.find_last_of('/')+1);





    vector<string> first_tokens = split(strFirst,'.');
    vector<string> second_tokens= split(strSecond,'.');

    for (size_t i = first_tokens.size()-1; i >0 ;i--) {
        if (stoi(first_tokens[i]) > stoi(second_tokens[i])) {
            return true;
        } else {
            continue;
        }
    }
    return false;
}
std::vector<std::string> MainWindow::split(const std::string& s, char seperator) {

   std::vector<std::string> output;

    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(seperator, pos)) != std::string::npos) {
        std::string substring( s.substr(prev_pos, pos-prev_pos) );

        output.push_back(substring);

        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word

    return output;
}

string MainWindow::getDataFromFile() {

QString str="";
for (auto i:pathsFiles) {
    QFile file(QString::fromStdString(i));
    if ((file.exists())&&(file.open(QIODevice::ReadOnly))) {

        while(!file.atEnd()) {
            str=str+file.readLine();
        }
    file.close();
    } else {
        qDebug() << path;
    }
}
return str.toStdString();
}

bool MainWindow::dtcomp(QDateTime* left, QDateTime *right) {
  return *left < *right;
}



MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_showButton_clicked() {
    QSqlQueryModel* query = new QSqlQueryModel;
    QString str = QString::fromStdString(getDataFromFile());
    query->setQuery(str);
    QTableView *tv = new QTableView(this);
    tv->setModel(query);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setModel(query);

}
