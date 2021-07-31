/*
 * class for file download backend
 */

#include "download.h"

Download::Download(QObject *parent, QString UrlParam) : QObject(parent)
{
    sUrl = UrlParam;
    url = QUrl(sUrl);
    sFileName = Name_Creation(url.fileName());
}


void Download::StartDownload()
/*
 * method for downloading the file
 */
{
    emit onSetFileName(sFileName);
    isStop = false;
    QNetworkRequest request;
    request.setUrl(url); //setting up a request by address

    if(continue_downloading)//setting the start byte of the download if it was suspended.
    {
        QString strRange = QString("bytes=%1-").arg(bytesCurrentReceived);
        request.setRawHeader("Range", strRange.toLatin1());
    }

    reply = manager.get(request);// receiving an array of data from hosting
    //connection of download events and reaction to them
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
    connect(reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
}

QString Download::Name_Creation(QString name)
/*
 * create a new filename if a file with that name already exists
 */
{
    QString newName;
    newName = name;
    if(fileExists(newName))
    {
        QString sName;
        QString Type;
        QString Count;
        int i = 0;
        int point_index = newName.lastIndexOf(".");
        if(point_index < 0)
        {
          sName =  newName;
          Type = ".xml";
        }else
        {
            sName = newName.left(point_index);
            Type = newName.right(newName.length() - point_index);
        }
        do
        {
            i++;
            Count = QString("(%1)").arg(i);
            newName = sName+Count+Type;
        } while (fileExists(newName));

    }
    return newName;
}


bool Download::fileExists(QString name)
{
    QFileInfo check_file(name);
    return check_file.exists() && check_file.isFile();
}

void Download::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    bytesDownload = bytesReceived;
    emit onProgress(bytesReceived +bytesCurrentReceived, bytesTotal + bytesCurrentReceived);
}

void Download::onReadyRead()
/*
 * reading an array of data from the exchange buffer and writing it to a file
 */
{
    if (!isStop)
        {
            QFile file(sFileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                file.write(reply->readAll());
            }
            file.close();
        }
}

void Download::onFinished()
/*
 * event handling end of download
 */
{
    isStop = true;
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (reply->error() != QNetworkReply::NoError)
    {
         emit onErrorMesage(reply->errorString());
    }
    emit onFinishedDownload(statusCode.toInt());
}

void Download::onError(QNetworkReply::NetworkError)
/*
 * error event handling
 */
{
    QString strError = reply->errorString();
    emit onErrorMesage(strError);
    onStopDownload();
    emit onFinishedDownload(1);
}

void Download::onStopDownload()
/*
 * handling the event when the user wants to stop downloading
 */
{
    isStop = true;
       if (reply != NULL)
       {
           disconnect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
           disconnect(reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
           disconnect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
           disconnect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
           reply->abort();
           reply->deleteLater();
           reply = NULL;
       }

}


void Download::onPsuse()
/*
 * handling the event when the user wants to pause the download
 */
{
    if (!isStop)
    {
        bytesCurrentReceived += bytesDownload;
        onStopDownload();
    }
}


