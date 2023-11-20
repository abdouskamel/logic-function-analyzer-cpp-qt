#include "truth_table_model.h"
#include "../logic/utils/my_utils.h"
#include <stdexcept>

TruthTableModel::TruthTableModel(TruthTable const* table)
    : QStandardItemModel()
{
    clear();

    if(table != nullptr)
    {
        setTruthTable(table);
    }
}

TruthTable
TruthTableModel::getTruthTable(void) const
{
    QStringList vars;
    QList<QList<QChar>> table;

    // Récupération des variables
    int i(0);
    QStandardItem* the_item;

    while((the_item = item(0, i)) != nullptr && !the_item->text().isEmpty())
    {
        if(!MyUtils::checkVariable(the_item->text()))
        {
            throw std::runtime_error("Veuillez vérifier vos variables, elles ne doivent contenir que des caractères alphanumériques.");
        }

        if(vars.contains(the_item->text()))
        {
            throw std::runtime_error("La variable '" + the_item->text().toStdString() + "' existe déjà.");
        }

        vars << the_item->text();
        ++i;
    }

    if(vars.size() <= 1)
    {
        throw std::runtime_error("Votre table est vide.");
    }

    // Récupération de la table
    QList<QChar> tab_row;

    bool stop(false);
    int j(0);
    i = 1;

    while(!stop)
    {
        tab_row.clear();

        if(item(i, vars.size() - 1) != nullptr && item(i, vars.size() - 1)->text() != "1")
        {
            tab_row = MyUtils::buildTableRow(i - 1, vars.size() - 1);
            tab_row.append('0');
        }

        else
        {
            stop = true;

            for(j = 0; j < vars.size(); ++j)
            {
                the_item = item(i, j);

                if(the_item == nullptr || the_item->text().isEmpty())
                {
                    tab_row.append('x');
                }

                else
                {
                    if(the_item->text() == "1" || the_item->text() == "0" ||
                       the_item->text() == "x")
                    {
                        tab_row.append(the_item->text()[0]);
                        stop = false;
                    }

                    else
                    {
                        throw std::runtime_error("Veuillez vérifier les valeurs de votre table de vérité.");
                    }
                }
            }
        }

        if(!stop)
        {
            table.append(tab_row);
        }

        i += 1;
    }

    vars.pop_back();
    return TruthTable(vars, table);
}

void
TruthTableModel::setTruthTable(QList<QList<QChar>> const& tab_content, QStringList const& vars_array)
{
    clear();
    QStandardItem* item(nullptr);

    int i(0);
    for(i = 0; i < vars_array.size(); ++i)
    {
        item = new QStandardItem(vars_array[i]);
        setItem(0, i, item);
    }

    item = new QStandardItem("S");
    setItem(0, i, item);

    for(int i(0); i < tab_content.size(); ++i)
    {
        for(int j(0); j < tab_content[i].size(); ++j)
        {
            item = new QStandardItem(tab_content[i][j]);
            setItem(i + 1, j, item);
        }
    }
}

void
TruthTableModel::setTruthTable(TruthTable const* table)
{
    setTruthTable(table->getTable(), table->getVariables());
}

void
TruthTableModel::clear(void)
{
    QStandardItemModel::clear();

    setRowCount(4096);
    setColumnCount(12);
}
