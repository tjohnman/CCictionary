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
    connect(&loadingDialog, SIGNAL(succeeded()), this, SLOT(loadingComplete()));
    connect(&loadingDialog, SIGNAL(failed()), this, SLOT(loadingFailed()));

    connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(onSelectionChanged(QModelIndex)));

    ui->searchProgressBar->hide();

    msgBox = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doSearch()
{
    QString searchTerms = ui->lineEdit->text();

    if (searchTerms.isEmpty()) {
        return;
    }

    ui->lineEdit->setEnabled(false);
    ui->pushButton->hide();
    ui->searchProgressBar->show();
    _m_DataModel->search(searchTerms);
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

void MainWindow::loadingFailed()
{
    if(msgBox) delete msgBox;
    msgBox = new QMessageBox();
    msgBox->setText("The file \"cedict_ts.u8\" could not be loaded.");
    msgBox->setIcon(QMessageBox::Critical);
    msgBox->setDetailedText("Please make sure the dictionary file is in the same directory as this application (that means inside the .app bundle on OS X) and that you have permissions to read it. You can download it here: http://www.mdbg.net/chindict/chindict.php?page=cedict. Make sure to uncompress it as necessary.");
    msgBox->show();
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
    ui->searchProgressBar->hide();
    ui->pushButton->show();
}

void MainWindow::loadDictionary()
{
    loadingDialog.show();
    loadingDialog.start();
}
