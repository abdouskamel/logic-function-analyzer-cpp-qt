#include "truth_table.h"

TruthTable::TruthTable(MyBinTree* arb, Tokens const& tokens)
{
    m_vars = MyUtils::getFuncVars(tokens);
    m_table = Analyzer::makeTruthTable(arb, m_vars);
}

TruthTable::TruthTable(QStringList const& vars, const QList<QList<QChar>> &table)
    : m_vars(vars), m_table(table)
{

}
