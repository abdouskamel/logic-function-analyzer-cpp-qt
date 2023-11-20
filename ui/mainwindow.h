#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "../logic/myfunction.h"
#include "truth_table_model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

        void updateAll(void);

    public slots :
        void on_expAnaButton_clicked(void);
        void on_fillButton_clicked(void);
        void on_analyzeButton_clicked(void);
        void on_clearButton_clicked(void);

    private:
        Ui::MainWindow* m_ui;

        MyFunction* m_the_function = nullptr;
        TruthTableModel m_table_model;
};

#endif // MAINWINDOW_H
