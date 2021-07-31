/*
 * class for fronne ent of a loading element
 */

#include "file_download.h"
#include "ui_file_download.h"

File_Download::File_Download(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::File_Download)
{
    ui->setupUi(this);
    ui->progStarus->setMaximum(100);
    ui->progStarus->setValue(0);
}

File_Download::~File_Download()
{
    delete ui;
}

void File_Download::SetURL(QString URLParam)
{
    if(!URLParam.isEmpty())
    {
        sURL = URLParam;
    }
}
void File_Download::onSetFileName(QString FileName)
/*
 * method for assigning a filename.
 */
{
    ui->l_FileName->setText(FileName);
    Name = FileName;
    emit onSigLogMessage(Name + "  start download.");
}

void File_Download::onProgress(qint64 bytesReceived, qint64 bytesTotal)
/*
 * method for displaying download progress
 */
{
    if(bytesTotal > 0)
    {
        int proc = (bytesReceived*100)/bytesTotal;
        ui->l_Status->setText(QString("%1 / %2").arg(bytesReceived).arg(bytesTotal));
        if( ui->progStarus->value() < proc)
            ui->progStarus->setValue(proc);
    }
}

void File_Download::StartDownload()
/*
 *method to create an additional stream and start downloading
 */
{
    hDownload = new Download(this, sURL);
    connect(hDownload, SIGNAL(onSetFileName(QString)), this, SLOT(onSetFileName(QString)));
    connect(hDownload, SIGNAL(onProgress(qint64, qint64)), this, SLOT(onProgress(qint64, qint64)));
    connect(hDownload, SIGNAL(onFinishedDownload(int)), this, SLOT(onFinished(int)));
    connect(hDownload, SIGNAL(onErrorMesage(QString)), this, SLOT(onErrorMesage(QString)));
    connect(this, SIGNAL(onStopDownload()), hDownload, SLOT(onStopDownload()));
    connect(this, SIGNAL(onPsuse()), hDownload, SLOT(onPsuse()));
    hDownload->StartDownload();
}

void File_Download::onFinished(int status)
{
    if(!isPause)
    {
        emit onSigLogMessage(Name + "  finished download.");
    }
}

void File_Download::on_pb_Stop_clicked()
/*
 * method to completely stop downloading
 */
{
    ui->pb_Pause->hide();
    ui->pb_Stop->hide();
    ui->progStarus->setValue(100);
    emit onStopDownload();
    emit onSigLogMessage(Name + "  stop download.");
}

void File_Download::on_pb_Pause_clicked()
/*
 * method for temporarily stopping a download
 */
{
    if(isPause)
    {
       isPause = false;
       ui->pb_Pause->setText("Pause");
       hDownload->StartDownload();
       emit onSigLogMessage(Name + "  proceed download.");
    }else
    {
        isPause = true;
        ui->pb_Pause->setText("Proceed");
        emit onPsuse();
        emit onSigLogMessage(Name + "  psuse download.");
    }
    onFinished(200);
}


void  File_Download::onErrorMesage(QString MesageErroe)
{
    emit onSigLogMessage(Name + "  " + MesageErroe);
}
