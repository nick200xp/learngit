#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QFont>
#include <QToolBar>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTextCodec>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createAction();
    void createMenu();
    void createToolBar();
    void fileRead();   //读文件
    void fileWrite();  //写文件

public:
    Ui::MainWindow *ui;

    QString filenName;
    QTextEdit *textEdit;

    //主菜单
    QMenu *file;
    QMenu *edit;
    QMenu *style;
    QMenu *insert; //插入菜单
    QMenu  *search; //查找菜单
    QMenu *help;   //帮助菜单

    QAction *newFile;
    QAction *openFile;
    QAction *save;
    QAction *saveAs;
    QAction *exit;


    QAction *undoAction;  //撤销
    QAction *redoAction;  //恢复
    /*
    QAction *copy;
    QAction *cut;
    QAction *paste;
    */

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

private slots:
    void NewFile();
    void OpenFile();
    void Save();
    void SaveAs();
    //void Color();


};

#endif // MAINWINDOW_H
