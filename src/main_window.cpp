#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_layout = new EditorLayout(12, 24);
    ui->h2ds->setLayout(m_layout);

    m_colManager.setLayout(m_layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    m_colManager.rearrangeColumns();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);

    int index = event->key() - Qt::Key_0;
    if (index >= 0 && index <= 9)
    {
        index--;
        if (index == -1) index = 9;

        m_colManager.toggleColumnWidth(index);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    m_colManager.rearrangeColumns();
}
