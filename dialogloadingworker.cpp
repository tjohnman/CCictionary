#include "dialogloadingworker.h"

#include <QtDebug>
#include <QFile>

void DialogLoadingWorker::run()
{
    qDebug() << "Opening cedict_ts.u8... ";
    QFile dictFile("cedict_ts.u8");

    if(!dictFile.exists())
    {
        emit loadFailed();
        return;
    }

    if(dictFile.open(QIODevice::ReadOnly))
    {
        emit gotFileSize(dictFile.size());
        qDebug() << "Reading lines...";

        while(!dictFile.atEnd())
        {
            QString line = QString(dictFile.readLine());
            if(line[0] != '#')
            {
                emit readLine(dictFile.pos(), line.left(line.length()-1));
            }
        }

        dictFile.close();

        emit loadSucceeded();
    }
}
