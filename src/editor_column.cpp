#include "editor_column.h"
#include "column_manager.h"

EditorColumn::EditorColumn(ColumnManager *colManager, QWidget *parent)
    : QWidget(parent), m_colManager(colManager)
{
    forceUpdateColumnWidth(EditorColumnWidth::Standard);
}

void EditorColumn::applyData(const EditorColumnData &data)
{
    setColumnWidth(data.columnWidth);
}

void EditorColumn::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();

    QPainter painter(this);
    painter.fillRect((width - COL_WIDTH) / 2, 0, width, height, m_bgColor);

    { // draw the column texture
        QRect targetRect(0, 0, width, height);
        QRect sourceRect(0, 0, width, 1);

        painter.drawPixmap(targetRect, m_colManager->imgs().getColFor(m_colWidth), sourceRect);
    }
}

void EditorColumn::setColumnWidth(EditorColumnWidth colWidth)
{
    // don't update anything if we don't have to!
    if (colWidth == m_colWidth) return;
    forceUpdateColumnWidth(colWidth);
}

void EditorColumn::forceUpdateColumnWidth(EditorColumnWidth colWidth)
{
    m_colWidth = colWidth;
    resize(colWidth == EditorColumnWidth::Standard ? COL_WIDTH : COL_WIDTH_EXT, 0);
}
