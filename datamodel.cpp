#include "datamodel.h"

#include <QtDebug>

DataModel::DataModel(QStringList lines, QObject *parent) : QAbstractListModel(parent)
{
    _m_Lines = QStringList(lines);
    _m_Results = QStringList();
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

int DataModel::search(QString query)
{
    _m_Results.clear();

    for(unsigned int i=0; i<_m_Lines.size(); ++i)
    {
        QStringList words = query.split(" ", QString::SkipEmptyParts, Qt::CaseInsensitive);
        for(unsigned int j=0; j<words.size(); ++j)
        {
            if(_m_Lines[i].contains(words[j]))
            {
                _m_Results.push_back(_m_Lines[i]);
                break;
            }
        }
    }

    return _m_Results.size();
}
