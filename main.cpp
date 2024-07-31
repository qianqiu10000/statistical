#include"myFindFiles.h"
#include<QDir>
#include<QtDebug>
#include<QTreeView>
#include<QHeaderView>
#include<QApplication>

int  main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    myFindFiles w;

    QTreeView tree;
    tree.setModel(w.model());
    tree.showMaximized();

    w.run(QDir::currentPath());

    tree.expandAll();
    tree.header()->resizeSections(QHeaderView::ResizeToContents);
    return a.exec();
}
