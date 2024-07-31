#include "myFindFiles.h"
#include"myAnalyzer.h"

#include<QDir>
#include<QDebug>

myFindFiles::myFindFiles()
{
    initialize();
}

myFindFiles::~myFindFiles()
{

}

void myFindFiles::initialize()
{
    m_codeLines = 0;
    m_microLines = 0;
    m_emptyLines = 0;
    m_annoMultiLines = 0;
    m_annoSingleLines = 0;

    m_model.clear();
    m_model.setHorizontalHeaderLabels(
               QStringList() << "文件名"
               << "代码行数"
               << "宏行数"
               << "空行数"
               << "多行注释"
               << "单行注释");

}

int myFindFiles::codeLines() const
{
    return m_codeLines;
}

int myFindFiles::microLines() const
{
    return m_microLines;
}

int myFindFiles::annoMultiLines() const
{
    return m_annoMultiLines;
}

int myFindFiles::annoSingleLines() const
{
    return m_annoSingleLines;
}

QStandardItemModel *myFindFiles::model()
{
    return &m_model;
}

void myFindFiles::run(const QString &dir)
{
    initialize();
    QStandardItem *root = new QStandardItem;
    root->setText(dir);
    root->setData(dir);
    m_model.appendRow(root);
    recursion(root);

    QList<QStandardItem *>line;
    QStandardItem *item = new QStandardItem;
    item->setText("统计");
    line.append(item);
    item = new QStandardItem;
    item->setText(QString::number(m_codeLines));
    line.append(item);
    item = new QStandardItem;
    item->setText(QString::number(m_emptyLines));
    line.append(item);
    item = new QStandardItem;
    item->setText(QString::number(m_microLines));
    line.append(item);
    item = new QStandardItem;
    item->setText(QString::number(m_annoMultiLines));
    line.append(item);
    item = new QStandardItem;
    item->setText(QString::number(m_annoSingleLines));
    line.append(item);
    m_model.appendRow(line);
}

void myFindFiles::recursion(QStandardItem *node)
{

    QDir workDir(node->data().toString());
    if(workDir.isEmpty()) {
        return;
    }
    if(!workDir.isReadable()) {
        return;
    }
    QStringList fileList = workDir.entryList(
                               QStringList() << "*.cpp" << "*.h" << "*.cxx",
                               QDir::Files);
    myAnalyzer analyzer;
    for(int i = 0; i < fileList.count(); i++)
    {
        QString file = fileList.at(i);

        if(! analyzer.procFile(workDir.path() + "/" + file)) {
            continue;
        }

        int codeLines = analyzer.codeLines();
        int emptyLines = analyzer.emptyLines();
        int microLines = analyzer.microLines();
        int annoMultiLines = analyzer.annoMultiLines();
        int annoSingleLines = analyzer.annoSingleLines();

        m_codeLines += codeLines;
        m_emptyLines += emptyLines;
        m_microLines += microLines;
        m_annoMultiLines += annoMultiLines;
        m_annoSingleLines += annoSingleLines;

        QList<QStandardItem *>line;
        QStandardItem *item = new QStandardItem;
        item->setText(file);
        item->setData(workDir.absolutePath() + "/" + file);
        line.append(item);
        item = new QStandardItem;
        item->setText(QString::number(codeLines));
        line.append(item);
        item = new QStandardItem;
        item->setText(QString::number(emptyLines));
        line.append(item);
        item = new QStandardItem;
        item->setText(QString::number(microLines));
        line.append(item);
        item = new QStandardItem;
        item->setText(QString::number(annoMultiLines));
        line.append(item);
        item = new QStandardItem;
        item->setText(QString::number(annoSingleLines));
        line.append(item);

        node->appendRow(line);
    }



    QStringList dirList = workDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    foreach(QString d, dirList) {
        QStandardItem *item = new QStandardItem;
        item->setText(d);
        item->setData(workDir.path() + "/" + d);
        node->appendRow(item);
        recursion(item);
    }
}

