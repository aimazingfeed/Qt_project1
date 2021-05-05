#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QWidget>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QDateTime>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::string getDataFromFile();
    QSqlDatabase db;
    QSqlTableModel* model;
    QSqlQueryModel* query;

private slots:
    void on_showButton_clicked();


private:
    Ui::MainWindow *ui;
    bool con=true;
    QDate cd = QDate::currentDate();
    QString path="L:/Projects/Qt_test/" + cd.toString("dd.MM.yyyy") +".sql";

};
#endif // MAINWINDOW_H
