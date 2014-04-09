#include "datamodel.h"
#include "term.h"

#include <QtDebug>

DataModel::DataModel(QStringList lines, QObject *parent) : QAbstractListModel(parent)
{
    _m_Lines = QStringList(lines);
    _m_Results = QStringList();

    connect(&_m_SearchWorker, SIGNAL(finished()), this, SLOT(onSearchFinished()));
    connect(&_m_SearchWorker, SIGNAL(addedRow()), this, SLOT(onRowAdded()));
}

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= _m_Results.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return _m_Results.at(index.row()).split(" ")[1];
    else
        return QVariant();
}


QString DataModel::getRawData(int row)
{
    return _m_Results.at(row);
}


QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    return QString();
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    return _m_Results.size();
}

void DataModel::search(QString query)
{
    _m_SearchWorker.init(query, &_m_Lines, &_m_Results);
    _m_SearchWorker.start();
}

void DataModel::onRowAdded()
{
    emit dataChanged(createIndex(0, 0), createIndex(_m_Results.size()-1, 0));
}

void DataModel::onSearchFinished()
{
    emit searchFinished();
}
