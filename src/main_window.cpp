#include "main_window.h"
#include "ui_main_window.h"

#include <QMap>

#include "tool_colors.h"

static QMap<int, QColor> s_tempColors;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_layout = new EditorLayout(12, 24);
    ui->h2ds->setLayout(m_layout);

    m_colManager.setLayout(m_layout);

    s_tempColors.insert(Qt::Key_O, COLOR_POS);

    s_tempColors.insert(Qt::Key_H, COLOR_BT_CHIP);
    s_tempColors.insert(Qt::Key_J, COLOR_BT_HOLD);
    s_tempColors.insert(Qt::Key_K, COLOR_FX_CHIP);
    s_tempColors.insert(Qt::Key_L, COLOR_FX_HOLD);

    s_tempColors.insert(Qt::Key_Q, COLOR_VOL_LEFT);
    s_tempColors.insert(Qt::Key_W, COLOR_VOL_RIGHT);
    s_tempColors.insert(Qt::Key_R, COLOR_ROLL);

    s_tempColors.insert(Qt::Key_S, COLOR_SPIN);
    s_tempColors.insert(Qt::Key_F, COLOR_STOP);
    s_tempColors.insert(Qt::Key_G, COLOR_VOL_KIND);

    s_tempColors.insert(Qt::Key_Z, COLOR_ZOOM_TOP);
    s_tempColors.insert(Qt::Key_X, COLOR_ZOOM_BOT);
    s_tempColors.insert(Qt::Key_V, COLOR_SLAM_VOL);
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

    if (s_tempColors.contains(event->key()))
    {
        QColor color = s_tempColors.value(event->key());
        m_colManager.setBackgroundColor(color);
        return;
    }

    switch (event->key())
    {
    case Qt::Key_QuoteLeft:
        m_colManager.toggleDefaultColumnWidth();
        break;

    default:
        int index = event->key() - Qt::Key_0;
        if (index >= 0 && index <= 9)
        {
            index--;
            if (index == -1) index = 9;

            m_colManager.toggleColumnWidth(index);
        }
        break;
    }

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    m_colManager.rearrangeColumns();
}
