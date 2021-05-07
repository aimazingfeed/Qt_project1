#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QWidget>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QDateTime>
#include <QDir>

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
    bool dtcomp(QDateTime* left, QDateTime *right);
    bool isSecondEarlier(QString first, QString second);
    std::vector<std::string> split(const std::string&, char);
    std::vector<std::string> sort(const QFileInfoList&);


private slots:
    void on_showButton_clicked( );


private:
    Ui::MainWindow *ui;
    bool con=true;
    QDate cd = QDate::currentDate();
    QString path="L:/Projects/Qt_test/" + cd.toString("dd.MM.yyyy") +".sql";
    QStringList filters = {"*.sql"};
    QDir dir;
    std::vector<std::string> pathsFiles;

};
#endif // MAINWINDOW_H
