#include "term.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

Term::Term(QString raw)
{
    QRegularExpressionMatch m;
    QRegularExpression r("([^ ]+) ([^\\ ]+) \\[([^\\]]+)\\] (.*)");
    raw.contains(r, &m);

    m_Traditional = m.captured(1);
    m_Simplified = m.captured(2);
    m_Pinyin = m.captured(3);
    QString meanings = m.captured(4).trimmed();
    m_English = meanings.split("/", QString::SkipEmptyParts);
}
