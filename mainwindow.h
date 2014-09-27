#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "dialogloading.h"

#include "datamodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadDictionary();

public slots:
    void doSearch();
    void onSearchFinished();
    void loadingComplete();
    void loadingFailed();
    void onSelectionChanged(QModelIndex index);

private:
    Ui::MainWindow *ui;
    DialogLoading loadingDialog;
    DataModel * _m_DataModel;
    QMessageBox * msgBox;
};

#endif // MAINWINDOW_H
