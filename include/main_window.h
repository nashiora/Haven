#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QFrame>

#include "column_manager.h"
#include "editor_layout.h"
#include "editor_column.h"
#include "image_manager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:

    // FILE:

    void _new();
    void open();
    void save();
    void saveAs();
    void close();

    // EDIT

    void editMetadata();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void _delete();
    void selectAll();
    void deselect();

    // TOOLS: Default

    void tool_Position();

    // TOOLS: Playables

    void tool_Bt();
    void tool_Fx();
    void tool_VolLeft();
    void tool_VolRight();

    // TOOLS: Instant Events

    void tool_Spin();
    void tool_Swing();
    void tool_Bounce();

    // TOOLS: Effect Parameters

    void tool_TiltKind();
    void tool_VolGainKind();
    void tool_SlamVolume();

    // TOOLS: Sections

    void tool_Stop();
    void tool_Reverse();
    void tool_Hide();

    // TOOLS: Camera/Highway Controls

    void tool_Zoom();
    void tool_Pitch();
    void tool_Offset();
    void tool_Roll();

private:
    Ui::MainWindow *ui;

    EditorLayout *m_layout;
    ColumnManager m_colManager;
};

#endif // MAIN_WINDOW_H
