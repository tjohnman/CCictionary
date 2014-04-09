#include "searchworker.h"
#include "term.h"

#include <QDebug>

SearchWorker::SearchWorker(QObject * parent) :
    QThread(parent)
{
}

void SearchWorker::init(QString query, QStringList *lines, QStringList *results)
{
    _m_Results = results;
    _m_Query = query;
    _m_Lines = lines;
}


void SearchWorker::run()
{
    _m_Results->clear();

    bool * added = new bool[_m_Lines->size()];

    for(int i=0; i<_m_Lines->size(); ++i)
    {
        Term term(_m_Lines->at(i));
        QStringList queryWords = _m_Query.split(" ", QString::KeepEmptyParts);

        for(int j=0; j<term.m_English.size(); ++j)
        {
            if(queryWords.contains(term.m_English[j], Qt::CaseInsensitive))
            {
                _m_Results->push_back(_m_Lines->at(i));
                emit addedRow();
                added[i] = true;
            }
        }
    }

    for(int i=0; i<_m_Lines->size(); ++i)
    {
        Term term(_m_Lines->at(i));
        QStringList queryWords = _m_Query.split(" ", QString::KeepEmptyParts);

        for(int j=0; j<term.m_English.size(); ++j)
        {
            for(int k=0; k<queryWords.size(); ++k)
            {
                if(!added[i] && term.m_English[j].contains(queryWords[k], Qt::CaseInsensitive))
                {
                    _m_Results->push_back(_m_Lines->at(i));
                    emit addedRow();
                    added[i] = true;
                }
            }
        }
    }

    delete[] added;
}
