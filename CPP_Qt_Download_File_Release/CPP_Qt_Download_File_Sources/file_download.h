#ifndef FILE_DOWNLOAD_H
#define FILE_DOWNLOAD_H

#include <QWidget>
//#include "threaddownload.h"
#include "download.h"

namespace Ui {
class File_Download;
}

class File_Download : public QWidget
{
    Q_OBJECT

public:
    explicit File_Download(QWidget *parent = nullptr);
    ~File_Download();
    void SetURL(QString URLParam);
    void StartDownload();

signals:
    void onStopDownload();
    void onPsuse();
    void onSigLogMessage(QString);

public slots:
    void onSetFileName(QString FileName);
    void onProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onFinished(int status);
    void onErrorMesage(QString);

private slots:
    void on_pb_Stop_clicked();

    void on_pb_Pause_clicked();

private:
    Ui::File_Download *ui;
    QString sURL = "https://ubuntu.volia.net/ubuntu-releases/20.04.2.0/ubuntu-20.04.2.0-desktop-amd64.iso";
    Download * hDownload = nullptr;
    bool isPause = false;
    QString Name;

};

#endif // FILE_DOWNLOAD_H
