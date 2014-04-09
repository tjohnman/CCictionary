#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "term.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), SLOT(doSearch()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), SLOT(doSearch()));
    connect(&loadingDialog, SIGNAL(finished(int)), this, SLOT(loadingComplete()));

    connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(onSelectionChanged(QModelIndex)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doSearch()
{
    ui->lineEdit->setEnabled(false);
    _m_DataModel->search(ui->lineEdit->text());
    ui->listView->reset();
}

void MainWindow::onSelectionChanged(QModelIndex index)
{
    Term term(_m_DataModel->getRawData(index.row()));

    ui->label_Simplified->setText(term.m_Simplified);
    ui->label_Traditional->setText(term.m_Traditional);

    ui->textBrowser->clear();

    ui->textBrowser->append(QString("<p style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;'><span style=' font-size:12pt;'>%1</span></p><br>&nbsp;").arg(term.m_Pinyin));

    for(int i=0; i<term.m_English.size(); ++i)
    {
        ui->textBrowser->append(QString("<p style=' margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;'><span style=' font-size:8pt; font-weight:600;'>%1.</span><span style=' font-size:10pt;'> %2</span></p>").arg(i+1).arg(term.m_English[i]));
    }
}

void MainWindow::loadingComplete()
{
    _m_DataModel = new DataModel(loadingDialog.m_Lines, ui->listView);
    connect(_m_DataModel, SIGNAL(searchFinished()), this, SLOT(onSearchFinished()));
    ui->listView->setModel(_m_DataModel);
    show();
}

void MainWindow::onSearchFinished()
{
    ui->lineEdit->setEnabled(true);
}

void MainWindow::loadDictionary()
{
    loadingDialog.show();
    loadingDialog.start();
}
