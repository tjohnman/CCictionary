#ifndef DIALOGLOADINGWORKER_H
#define DIALOGLOADINGWORKER_H

#include <QThread>

class DialogLoadingWorker : public QThread
{
    Q_OBJECT

public:
    void run();

signals:
    void gotFileSize(int size);
    void readLine(int filePos, QString line);
    void loadFailed();
    void loadSucceeded();
};

#endif // DIALOGLOADINGWORKER_H
