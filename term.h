#ifndef TERM_H
#define TERM_H

#include <QStringList>

class Term
{
public:
    Term(QString raw);

public:
    QString m_Traditional, m_Simplified, m_Pinyin;
    QStringList m_English;
};

#endif // TERM_H
