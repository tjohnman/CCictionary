#ifndef SEARCHWORKER_H
#define SEARCHWORKER_H

#include <QThread>
#include <QStringList>

class SearchWorker : public QThread
{
    Q_OBJECT
public:
    SearchWorker(QObject *parent = 0);

    void init(QString query, QStringList * lines, QStringList * results);
    void run();

signals:
    void addedRow();

public slots:

private:
    QStringList * _m_Results, * _m_Lines;
    QString _m_Query;
};

#endif // SEARCHWORKER_H
