#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractListModel>

#include "searchworker.h"

class SearchWorker;

class DataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    DataModel(QStringList lines, QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void search(QString query);
    QString getRawData(int row);

signals:
    void searchFinished();

public slots:
    void onSearchFinished();
    void onRowAdded();

private:
    QStringList _m_Lines, _m_Results;
    SearchWorker _m_SearchWorker;
};

#endif // DATAMODEL_H
