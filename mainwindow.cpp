#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    setWindowIcon(QIcon(":/image/images/Editor.png"));
    setWindowTitle(tr("Qt文本编辑器"));
    textEdit = new QTextEdit();
    setCentralWidget(textEdit);
    createAction();   //创建动作
    createMenu();   //创建菜单
    createToolBar();  //创建工具栏

    //文件菜单的动作与槽的连接
    connect(newFile,SIGNAL(triggered()),this,SLOT(NewFile()));
    connect(openFile,SIGNAL(triggered()),this,SLOT(OpenFile()));
    connect(save,SIGNAL(triggered()),this,SLOT(Save()));
    connect(saveAs,SIGNAL(triggered()),this,SLOT(SaveAs()));
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));

    //编辑菜单的动作与槽的连接
    connect(undoAction,SIGNAL(triggered()),textEdit,SLOT(undo()));
    connect(redoAction,SIGNAL(triggered()),textEdit,SLOT(redo()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

//创建动作
void MainWindow::createAction()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    //新建文件
    newFile = new QAction(QIcon(":/image/images/filenew.png"),tr("新建文件"),this);
    newFile->setShortcut(tr("Ctrl+N"));
    newFile->setStatusTip(tr("新建一个文件"));

    //打开文件
    openFile = new QAction(QIcon(":/image/images/fileopen.png"),tr("打开文件"),this);
    openFile->setShortcut(tr("Ctrl+O"));
    openFile->setStatusTip(tr("打开一个文件"));

    //保存文件
    save = new QAction(QIcon(":/image/images/filesave.png"),tr("保存"),this);
    save->setShortcut(tr("Ctrl+S"));
    save->setStatusTip(tr("保存文件"));

    //另存为
    saveAs = new QAction(QIcon(":/image/images/filesaveas.png"),tr("另存为"),this);
    saveAs->setShortcut(tr("Ctrl+A"));
    saveAs->setStatusTip(tr("文件另存为"));

    //退出
    exit = new QAction(QIcon(":/image/images/Exit.png"),tr("退出"),this);
    exit->setShortcut(tr("Ctrl+Q"));
    exit->setStatusTip(tr("退出"));

    //恢复
    redoAction = new QAction(QIcon(":/image/images/Redo.png"),tr("恢复"),this);
    redoAction->setShortcut(tr("Ctrl+R"));
    redoAction->setStatusTip(tr("恢复"));

    //撤销
    undoAction = new QAction(QIcon(":/image/images/Undo.png"),tr("撤销"),this);
    undoAction->setShortcut(tr("Ctrl+U"));
    undoAction->setStatusTip(tr("撤销"));

}


//创建菜单
void MainWindow::createMenu()
{
    //文件菜单
    file = menuBar()->addMenu(tr("文件(&F)"));
    file->addAction(newFile);
    file->addAction(openFile);
    file->addSeparator();
    file->addAction(save);
    file->addAction(saveAs);
    file->addSeparator();
    file->addAction(exit);

    //编辑菜单
    edit = menuBar()->addMenu(tr("编辑(&E)"));
    edit->addAction(undoAction);
    edit->addAction(redoAction);
    edit->addSeparator();


}

//创建工具栏
void MainWindow::createToolBar()
{
    //文件
    fileToolBar = addToolBar(tr("文件(&N)"));
    fileToolBar->addAction(newFile);
    fileToolBar->addAction(openFile);
    fileToolBar->addAction(save);
    fileToolBar->addAction(exit);

    //编辑
    editToolBar = addToolBar(tr("编辑(&E)"));
    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);
    editToolBar->addSeparator();



}

//新建文件
void MainWindow::NewFile()
{
    MainWindow *newEdit = new MainWindow;
    newEdit->show();
}

//打开文件
void MainWindow::OpenFile()
{
    filenName = QFileDialog::getOpenFileName(this,tr("打开文件"),"/","allFile(*.*)");
    if(!filenName.isEmpty())
    {
        if(textEdit->document()->isEmpty())
        {
            fileRead();
        }else
        {
            MainWindow *newEdit = new MainWindow;
            newEdit->show();
            QFile file(filenName);
            if(!file.open(QFile::ReadOnly|QFile::Text)){
                QMessageBox::warning(this,"多文档编辑器",tr("不可以打开文件%1:\n%2").arg(filenName).arg(file.errorString()));
                return;
          }

        QTextStream in(&file);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        newEdit->textEdit->setPlainText(in.readAll());
        QApplication::restoreOverrideCursor();

        }
    }
}

//封装的读文件,用于精简程序
void MainWindow::fileRead()
{
    QFile file(filenName);
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::warning(this,tr("多文档编辑器"),tr("不可以打开文件%1\n%2").arg(filenName).arg(file.errorString()));
        return;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
}

//封装的写文件,用于精简程序
void MainWindow::fileWrite()
{
    QFile file(filenName);
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,tr("多文档编辑器"),tr("不可以写入文件%1\n%2").arg(filenName).arg(file.errorString()));
        return;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<<textEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    return;

}

//保存文件
void MainWindow::Save()
{
    if(filenName.isEmpty())
    {
        filenName = QFileDialog::getSaveFileName(this,tr("另存为"),tr("未命名.txt"));
        fileWrite();
    }else {
        fileWrite();
    }

}

//另存为
void MainWindow::SaveAs()
{
    filenName = QFileDialog::getSaveFileName(this,tr("另存为"),tr("未命名.txt"));
    fileWrite();
}
