#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "file_download.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    spacer = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding);

    log = new ThreadLog(); // creating an additional stream for writing to a log file
    connect(this, SIGNAL(onSigLogMessage(QString)), log, SLOT(onLogMessage(QString)));//connection of events and methods for connection of threads.
    connect(this, SIGNAL(onSigClose()), log, SLOT(onClose()));
    log->start();// start thread
}

MainWindow::~MainWindow()
{
    delete ui;
    emit onSigClose();
}


void MainWindow::on_pb_Download_clicked()
{
    Add_Download();
}

void MainWindow::Add_Download()
/*
 * the method is used to create controls and download a new file
 * */
{

    ui->scrollAreaWidgetContents->layout()->removeItem(spacer);
    QString sURL = ui->le_URL->text();
    File_Download *fd = new File_Download(this); //creating a new load item
    connect(fd, SIGNAL(onSigLogMessage(QString)), this, SLOT(on_LogMessage(QString))); //connections
    fd->SetURL(ui->le_URL->text());//adding an address
    ui->scrollAreaWidgetContents->layout()->addWidget(fd);//placing an element on the form
    ui->scrollAreaWidgetContents->layout()->addItem(spacer);
    fd->StartDownload();//start of the download
}


void MainWindow::on_LogMessage(QString message)
/*
 * the method is engaged in processing and writing log messages
 */
{
    QString mes = QTime::currentTime().toString() + "\n\r";
    mes+= message + "\n\r\n\r";
    ui->te_Log->append(mes); //logging on the form
    emit onSigLogMessage(mes);//creating an event to write a log to a file
}
