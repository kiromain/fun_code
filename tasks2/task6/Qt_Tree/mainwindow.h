#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QFile>
#include <QModelIndex>

class Tree;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     Tree *getTreeFromIndex(const QModelIndex &index);

private slots:
     void addItem();
     void removeItem();
     void saveToFile();
     void readFromFile();

private:

    void buildModel(Tree *tree, QStandardItem *parent);
    Tree* modelIndexToTree(const QModelIndex &index);
    QTreeView *treeView;
    QStandardItemModel *model;
    Tree *root;

    void saveTree(Tree* tree, QFile &file,int depth);

};

#endif // MAINWINDOW_H
