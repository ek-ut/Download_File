#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QUrl>
#include <QFileInfo>
#include<QFile>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class Download : public QObject
{
    Q_OBJECT
public:
    explicit Download(QObject *parent = nullptr, QString UrlParam = "");
    void StartDownload();

signals:
    void onSetFileName(QString FileName);
    void onProgress(qint64, qint64);
    void onFinishedDownload(int);
    void onErrorMesage(QString);

public slots:
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onReadyRead();
    void onFinished();
    void onError(QNetworkReply::NetworkError);
    void onStopDownload();
    void onPsuse();

private:
    QString sFileName;
    QString sUrl;
    QUrl url;
    bool continue_downloading = false;
    bool isStop = false;
    qint64 bytesCurrentReceived = 0;
    qint64 bytesDownload = 0;
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    bool fileExists(QString name);
    QString Name_Creation(QString name);

};

#endif // DOWNLOAD_H
