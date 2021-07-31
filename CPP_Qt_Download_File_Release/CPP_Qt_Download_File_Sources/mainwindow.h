#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpacerItem>
#include "threadlog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots: // methods that handle events
    void on_pb_Download_clicked();
    void on_LogMessage(QString message);

signals: //custom events that the object creates
    void onSigClose();
    void onSigLogMessage(QString);


private:
    Ui::MainWindow *ui;
    void Add_Download();
    QSpacerItem *spacer;
    ThreadLog *log;

};
#endif // MAINWINDOW_H
