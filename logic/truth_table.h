#ifndef TRUTH_TABLE_H
#define TRUTH_TABLE_H

#include "utils/my_utils.h"
#include "formula/analyzer.h"
#include <QList>

class TruthTable
{
    public:
        TruthTable(MyBinTree* arb, Tokens const& tokens);
        TruthTable(QStringList const& vars, QList<QList<QChar>> const& table);

        QStringList getVariables(void) const { return m_vars; }
        const QList<QList<QChar>>& getTable(void) const { return m_table; }

    protected:
        QStringList m_vars;
        QList<QList<QChar>> m_table;

};

#endif // TRUTH_TABLE_H

