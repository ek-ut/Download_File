/*
 * class for writing a log in an additional stream
 */

#include "threadlog.h"

ThreadLog::ThreadLog()
{

    file= new QFile(sFileName);
}


void ThreadLog::run()
/*
 * the method creates an additional stream
 */
{
    do {
        sleep(1);
    } while (isStop);
}

void ThreadLog::onLogMessage(QString message)
/*
 * the method for writing a log
 */
{
    if (file->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        file->write(message.toLatin1());
    }
    file->close();
}

void ThreadLog::onClose()
{
    isStop = true;
}
