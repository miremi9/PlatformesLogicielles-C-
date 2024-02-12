#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sqlite3.h>
#include "databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  private:
    sqlite3* DB;
    DataBaseManager* manager;

    Q_OBJECT

  private:
    Ui::MainWindow *ui;

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool verifyInput(QString nom, QString prenom, QString motDePasse, QString typeUtilisateur);

  public slots:
    void whenButtonIsClicked();
  private slots:
    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();


};

#endif // MAINWINDOW_H
