#ifndef TRUTH_TABLE_MODEL_H
#define TRUTH_TABLE_MODEL_H

#include <QStandardItemModel>
#include "../logic/truth_table.h"

class TruthTableModel : public QStandardItemModel
{
    public:
        TruthTableModel(TruthTable const* table = nullptr);

        TruthTable getTruthTable(void) const;

        void setTruthTable(QList<QList<QChar>> const& tab_content, QStringList const& vars_array);
        void setTruthTable(TruthTable const* table);

        void clear(void);

    protected:
        TruthTable* m_table;
};

#endif // TRUTH_TABLE_MODEL_H

