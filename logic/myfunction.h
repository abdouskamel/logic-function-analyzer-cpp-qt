#ifndef MYFUNCTION
#define MYFUNCTION

#include "truth_table.h"
#include "utils/my_const.h"
#include "utils/binary_tree.h"

class MyFunction
{
    public:
        MyFunction(QString const& function);
        MyFunction(TruthTable const& truth_table);

        ~MyFunction();

        Tokens getTokens(void) const { return m_tokens; }
        const TruthTable& getTruthTable(void) const { return *m_truth_table; }

        QString getDisjForm(void) const { return m_disj_form.join(" + "); }
        QString getConjForm(void) const;
        QString getSimpleForm(void) const { return m_simple_form.join(" + "); }

    protected:
        Tokens m_tokens;
        MyBinTree* m_arb;
        TruthTable* m_truth_table;

        QStringList m_disj_form,
                    m_conj_form,
                    m_simple_form;
};

#endif // MYFUNCTION

