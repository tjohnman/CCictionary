#include "dialogloading.h"
#include "ui_dialogloading.h"

#include <QtDebug>

DialogLoading::DialogLoading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLoading)
{
    ui->setupUi(this);
}

DialogLoading::~DialogLoading()
{
    delete ui;
}

void DialogLoading::start()
{
    ui->progressBar->setMaximum(0);
    ui->progressBar->setValue(0);

    connect(&workerThread, SIGNAL(loadSucceeded()), this, SLOT(workerDone()));
    connect(&workerThread, SIGNAL(readLine(int, QString)), this, SLOT(onLineRead(int,QString)));
    connect(&workerThread, SIGNAL(gotFileSize(int)), this, SLOT(onGotFileSize(int)));
    connect(&workerThread, SIGNAL(loadFailed()), this, SLOT(onLoadFailed()));
    workerThread.start();
}

void DialogLoading::onLoadFailed()
{
    emit failed();
    close();
}

void DialogLoading::onGotFileSize(int size)
{
    ui->progressBar->setMaximum(size);
}

void DialogLoading::onLineRead(int filePos, QString line)
{
    m_Lines.push_back(line);
    ui->progressBar->setValue(filePos);
    ui->label->setText(QString("Reading dictionary entries... (%1 entries read)").arg(m_Lines.size()));
}

void DialogLoading::workerDone()
{
    emit succeeded();
    close();
}
