#ifndef THREADLOG_H
#define THREADLOG_H


#include <QThread>
#include<QFile>

class ThreadLog : public QThread
{
    Q_OBJECT
public:
    explicit ThreadLog();
    void run();

private:
    QString sFileName = "Log.txt";
    QFile *file;
    bool isStop = false;

public slots:
    void onLogMessage(QString);
    void onClose();
};

#endif // THREADLOG_H
