#ifndef MYFINDFILES_H
#define MYFINDFILES_H

#include<QStandardItemModel>


class QString;
class myFindFiles
{
public:
    myFindFiles();
    virtual ~myFindFiles();
    void initialize();

    int codeLines()const;
    int microLines()const;
    int annoMultiLines()const;
    int annoSingleLines()const;

    QStandardItemModel *model();
    void run(const QString &dir);
private:
    int m_codeLines;
    int m_microLines;
    int m_emptyLines;
    int m_annoMultiLines;
    int m_annoSingleLines;
    QStandardItemModel m_model;
    void recursion(QStandardItem *node);
};

#endif // MYFINDFILES_H
