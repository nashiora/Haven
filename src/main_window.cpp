#include "kshchart.h"
#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setMinimumSize(400, 300);

    ui->setupUi(this);

    m_layout = new EditorLayout(12, 24);
    ui->h2ds->setLayout(m_layout);

    m_colManager.setLayout(m_layout);

    ui->mainToolBar->setIconSize(QSize(16, 16));
    ui->mainToolBar->addAction(ui->action_New);
    ui->mainToolBar->addAction(ui->action_Open);
    ui->mainToolBar->addAction(ui->action_Save);
    ui->mainToolBar->addAction(ui->actionSave_As);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionCut);
    ui->mainToolBar->addAction(ui->actionCopy);
    ui->mainToolBar->addAction(ui->actionPaste);
    ui->mainToolBar->addAction(ui->actionDelete);

    connect(ui->action_New, &QAction::triggered, this, &MainWindow::_new);
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::open);
    connect(ui->action_Save, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::saveAs);
    connect(ui->action_Close, &QAction::triggered, this, &MainWindow::_close);

    connect(ui->actionChart_Metadata, &QAction::triggered, this, &MainWindow::editMetadata);
    connect(ui->action_Undo, &QAction::triggered, this, &MainWindow::undo);
    connect(ui->action_Redo, &QAction::triggered, this, &MainWindow::redo);
    connect(ui->actionCut, &QAction::triggered, this, &MainWindow::cut);
    connect(ui->actionCopy, &QAction::triggered, this, &MainWindow::copy);
    connect(ui->actionPaste, &QAction::triggered, this, &MainWindow::paste);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::_delete);
    connect(ui->actionSelect_All, &QAction::triggered, this, &MainWindow::selectAll);
    connect(ui->actionDeselect, &QAction::triggered, this, &MainWindow::deselect);

    connect(ui->actionExtended_column_width, &QAction::toggled, this, &MainWindow::setColumnWidthExtended);

    connect(ui->actionPosition, &QAction::triggered, this, &MainWindow::tool_Position);

    connect(ui->actionBT, &QAction::triggered, this, &MainWindow::tool_Bt);
    connect(ui->actionFX, &QAction::triggered, this, &MainWindow::tool_Fx);
    connect(ui->actionVOL_Left, &QAction::triggered, this, &MainWindow::tool_VolLeft);
    connect(ui->actionVOL_Right, &QAction::triggered, this, &MainWindow::tool_VolRight);

    connect(ui->actionSpin, &QAction::triggered, this, &MainWindow::tool_Spin);
    connect(ui->actionSwing, &QAction::triggered, this, &MainWindow::tool_Swing);
    connect(ui->actionBounce, &QAction::triggered, this, &MainWindow::tool_Bounce);

    connect(ui->actionStop, &QAction::triggered, this, &MainWindow::tool_Stop);
    connect(ui->actionReverse, &QAction::triggered, this, &MainWindow::tool_Reverse);
    connect(ui->actionHide, &QAction::triggered, this, &MainWindow::tool_Hide);

    connect(ui->actionTilt_Kind, &QAction::triggered, this, &MainWindow::tool_TiltKind);
    connect(ui->actionVOL_GainKind, &QAction::triggered, this, &MainWindow::tool_VolGainKind);
    connect(ui->actionSlam_Volume, &QAction::triggered, this, &MainWindow::tool_SlamVolume);

    connect(ui->actionZoom, &QAction::triggered, this, &MainWindow::tool_Zoom);
    connect(ui->actionPitch, &QAction::triggered, this, &MainWindow::tool_Pitch);
    connect(ui->actionOffset, &QAction::triggered, this, &MainWindow::tool_Offset);
    connect(ui->actionRoll, &QAction::triggered, this, &MainWindow::tool_Roll);
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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    m_colManager.rearrangeColumns();
}

void MainWindow::_new()
{
    qInfo() << "new";
}

void MainWindow::open()
{
    qInfo() << "open";

    const QString DEFAULT_DIR_KEY("default_dir");
    QSettings settings;

    QString file = QFileDialog::getOpenFileName(this, "Select a chart",
                                                settings.value(DEFAULT_DIR_KEY).toString(),
                                                "K-Shoot MANIA Charts (*.ksh)");

    if (file.isEmpty())
        return;

    QDir currentDir;
    settings.setValue(DEFAULT_DIR_KEY, currentDir.absoluteFilePath(file));

    qInfo() << "attempting to open chart file from: " << file;

    if (file.endsWith(".ksh", Qt::CaseSensitivity::CaseInsensitive))
    {
        KshChart ksh(file);
        if (!ksh.load())
        {
            qInfo() << "  failed to load ksh file!";
            return;
        }
        else qInfo() << "  succeeded!";

        // TODO(local): convert KshChart to Haven's internal format
    }
}

void MainWindow::save()
{
    qInfo() << "save";
}

void MainWindow::saveAs()
{
    qInfo() << "saveAs";

    QStringList filters;
    filters << "K-Shoot MANIA Charts (*.ksh)";

    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
    dialog.setConfirmOverwrite(true);
    dialog.setNameFilters(filters);

    dialog.exec();

    QStringList files = dialog.selectedFiles();
    if (files.count() == 0)
        return; // canceled or something

    assert(files.count() == 1);
    QString file = files.first();

    qInfo() << "saving chart file to: " << file;
}

void MainWindow::_close()
{
    qInfo() << "close";
    close();
}

void MainWindow::editMetadata()
{
    qInfo() << "edit meta";
}

void MainWindow::undo()
{
    qInfo() << "undo";
}

void MainWindow::redo()
{
    qInfo() << "redo";
}

void MainWindow::cut()
{
    qInfo() << "cut";
}

void MainWindow::copy()
{
    qInfo() << "copy";
}

void MainWindow::paste()
{
    qInfo() << "paste";
}

void MainWindow::_delete()
{
    qInfo() << "delete";
}

void MainWindow::selectAll()
{
    qInfo() << "select all";
}

void MainWindow::deselect()
{
    qInfo() << "deselect";
}

void MainWindow::setColumnWidthExtended(bool checked)
{
    qInfo() << "set column width extended";
    m_colManager.setDefaultColumnWidth(checked ? ColumnWidth::Extended : ColumnWidth::Standard);
}

void MainWindow::tool_Position()
{
    qInfo() << "tool position";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtOnly);
    m_colManager.setBackgroundColor(QColor(0, 0, 0));
}

void MainWindow::tool_Bt()
{
    qInfo() << "tool bt";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtOnly);
    m_colManager.setBackgroundColor(QColor(30, 36, 24));
}

void MainWindow::tool_Fx()
{
    qInfo() << "tool fx";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtOnly);
    m_colManager.setBackgroundColor(QColor(38, 30, 8));
}

void MainWindow::tool_VolLeft()
{
    qInfo() << "tool vol left";
    m_colManager.setBackgroundWidth(ColumnBgWidth::Fill);
    m_colManager.setBackgroundColor(QColor(2, 24, 34));
}

void MainWindow::tool_VolRight()
{
    qInfo() << "tool vol right";
    m_colManager.setBackgroundWidth(ColumnBgWidth::Fill);
    m_colManager.setBackgroundColor(QColor(38, 2, 38));
}

void MainWindow::tool_Spin()
{
    qInfo() << "tool spin";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtOnly);
    m_colManager.setBackgroundColor(QColor(24, 0, 32));
}

void MainWindow::tool_Swing()
{
    qInfo() << "tool swing";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtOnly);
    m_colManager.setBackgroundColor(QColor(4, 36, 20));
}

void MainWindow::tool_Bounce()
{
    qInfo() << "tool bounce";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtOnly);
    m_colManager.setBackgroundColor(QColor(32, 2, 22));
}

void MainWindow::tool_TiltKind()
{
    qInfo() << "tool tilt kind";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtOnly);
    m_colManager.setBackgroundColor(QColor(0, 38, 24));
}

void MainWindow::tool_VolGainKind()
{
    qInfo() << "tool vol gain & kind";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtOnly);
    m_colManager.setBackgroundColor(QColor(0, 24, 24));
}

void MainWindow::tool_SlamVolume()
{
    qInfo() << "tool slam vol";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtOnly);
    m_colManager.setBackgroundColor(QColor(24, 0, 6));
}

void MainWindow::tool_Stop()
{
    qInfo() << "tool stop";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtOnly);
    m_colManager.setBackgroundColor(QColor(36, 0, 0));
}

void MainWindow::tool_Reverse()
{
    qInfo() << "tool reverse";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtOnly);
    m_colManager.setBackgroundColor(QColor(0, 34, 0));
}

void MainWindow::tool_Hide()
{
    qInfo() << "tool hide";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtOnly);
    m_colManager.setBackgroundColor(QColor(0, 0, 38));
}

void MainWindow::tool_Zoom()
{
    qInfo() << "tool zoom";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtVol);
    m_colManager.setBackgroundColor(QColor(24, 12, 0));
}

void MainWindow::tool_Pitch()
{
    qInfo() << "tool pitch";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtVol);
    m_colManager.setBackgroundColor(QColor(0, 4, 24));
}

void MainWindow::tool_Offset()
{
    qInfo() << "tool offset";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtVol);
    m_colManager.setBackgroundColor(QColor(24, 24, 4));
}

void MainWindow::tool_Roll()
{
    qInfo() << "tool roll";
    m_colManager.setBackgroundWidth(ColumnBgWidth::BtVol);
    m_colManager.setBackgroundColor(QColor(24, 14, 12));
}

