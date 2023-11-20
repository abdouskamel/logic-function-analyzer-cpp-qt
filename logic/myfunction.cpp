#include "myfunction.h"

#include "formula/analyzer.h"
#include "formula/my_parser.h"
#include "formula/simplificator.h"

MyFunction::MyFunction(QString const& function)
    : m_tokens(MyParser::tokenizeIt(function)),
      m_arb(new MyBinTree(""))
{
    MyParser::makeTheTree(m_arb, m_tokens);
    m_truth_table = new TruthTable(m_arb, m_tokens);

    m_disj_form = Analyzer::getDisjForm(m_truth_table->getTable(), m_truth_table->getVariables());
    m_conj_form = Analyzer::getConjForm(m_truth_table->getTable(), m_truth_table->getVariables());

    if(m_disj_form.isEmpty())
    {
        m_simple_form << "0";
    }

    else if(m_conj_form.isEmpty())
    {
        m_simple_form << "1";
    }

    else
    {
        m_simple_form = Simplificator::simplifyIt(m_disj_form);
    }
}

MyFunction::MyFunction(TruthTable const& truth_table)
    : m_arb(nullptr)
{
    m_truth_table = new TruthTable(truth_table);

    m_disj_form = Analyzer::getDisjForm(m_truth_table->getTable(), m_truth_table->getVariables());
    m_conj_form = Analyzer::getConjForm(m_truth_table->getTable(), m_truth_table->getVariables());

    if(m_disj_form.isEmpty())
    {
        m_simple_form << "0";
    }

    else if(m_conj_form.isEmpty())
    {
        m_simple_form << "1";
    }

    else
    {
        m_simple_form = Simplificator::simplifyIt(m_disj_form);
    }
}

MyFunction::~MyFunction()
{
    delete m_arb;
    delete m_truth_table;

    m_arb = nullptr;
    m_truth_table = nullptr;
}

QString
MyFunction::getConjForm(void) const
{
    QString result;

    for(int i(0); i < m_conj_form.size(); ++i)
    {
        result += "(" + m_conj_form[i] + ")";

        if(i != m_conj_form.size() - 1)
        {
            result += ".";
        }
    }

    return result;
}
