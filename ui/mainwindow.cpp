#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../logic/utils/tokens_exception.h"
#include <stdexcept>

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_ui->truthTableView->setModel(&m_table_model);
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_the_function;

    m_ui = nullptr;
    m_the_function = nullptr;
}

void
MainWindow::updateAll(void)
{
    m_ui->disjFormEdit->setText(m_the_function->getDisjForm());
    m_ui->conjFormEdit->setText(m_the_function->getConjForm());
    m_ui->simpFormEdit->setText(m_the_function->getSimpleForm());
}

void
MainWindow::on_expAnaButton_clicked(void)
{
    QString exp(m_ui->userExpEdit->toPlainText());

    try
    {
        m_the_function = new MyFunction(exp);
        m_table_model.setTruthTable(&m_the_function->getTruthTable());

        updateAll();
    }

    catch(TokensException const& e)
    {
        QMessageBox::critical(this, "Erreur lors du parsage", e.what());
    }
}

void
MainWindow::on_fillButton_clicked(void)
{
    int nb_vars = m_ui->nbVarsBox->value();

    if(nb_vars == 0)
    {
        m_table_model.clear();
        return ;
    }

    MyBinTree arb("0");
    QStringList vars_array;
    QList<QList<QChar>> my_table;

    for(int i(0); i < nb_vars; ++i)
    {
        vars_array << QChar('A' + i);
    }

    my_table = Analyzer::makeTruthTable(&arb, vars_array);

    m_table_model.setTruthTable(my_table, vars_array);
}

void
MainWindow::on_analyzeButton_clicked(void)
{
    try
    {
        TruthTable table = m_table_model.getTruthTable();
        delete m_the_function;
        m_the_function = new MyFunction(table);
        updateAll();
    }

    catch(std::runtime_error const& e)
    {
        QMessageBox::critical(this, "Erreur table de vérité", e.what());
    }
}

void
MainWindow::on_clearButton_clicked(void)
{
    m_table_model.clear();
}
