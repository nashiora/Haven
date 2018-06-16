#include "editor_column.h"
#include "column_manager.h"

EditorColumn::EditorColumn(ColumnManager *colManager, QWidget *parent)
    : QWidget(parent), m_colManager(colManager)
{
    forceUpdateColumnWidth(ColumnWidth::Standard);
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

    { // draw the bg fill
        int bgWidth;
        switch (m_bgWidth)
        {
        case ColumnBgWidth::BtOnly: bgWidth = 4 * COL_LANE_WIDTH + 3 * COL_BORDER_WIDTH; break;
        case ColumnBgWidth::BtVol:  bgWidth = 6 * COL_LANE_WIDTH + 5 * COL_BORDER_WIDTH; break;
        case ColumnBgWidth::Fill:   bgWidth = width;                                     break;
        }
        painter.fillRect((width - bgWidth) / 2, 0, bgWidth, height, m_bgColor);
    }

    { // draw the column texture
        QRect targetRect(0, 0, width, height);
        QRect sourceRect(0, 0, width, 1);

        painter.drawPixmap(targetRect, m_colManager->imgs().getColFor(m_colWidth), sourceRect);
    }

    int editHeight = height - 1;
    for (int m = 0; m < 4; m++)
    {
        int mh = m * editHeight / 4;
        paintDivisionBar(editHeight - mh, true, painter);

        int m2h = (m + 1) * editHeight / 4;
        paintDivisionBar(editHeight - m2h, true, painter);

        for (int b = 1; b < 4; b++)
        {
            int bh = mh + b * editHeight / 16;
            paintDivisionBar(editHeight - bh, false, painter);
        }
    }
}

void EditorColumn::setColumnWidth(ColumnWidth colWidth)
{
    // don't update anything if we don't have to!
    if (colWidth == m_colWidth) return;
    forceUpdateColumnWidth(colWidth);
}

void EditorColumn::forceUpdateColumnWidth(ColumnWidth colWidth)
{
    m_colWidth = colWidth;
    resize(colWidth == ColumnWidth::Standard ? COL_WIDTH : COL_WIDTH_EXT, 0);
}

void EditorColumn::paintDivisionBar(int y, bool isMeasureStart, QPainter &painter)
{
    int width = this->width();
    int lineWidth = 4 * COL_LANE_WIDTH + 3 * COL_BORDER_WIDTH;

    QColor color;
    if (isMeasureStart)
        color = QColor(255, 255, 0);
    else color = QColor(96, 96, 96);

    painter.fillRect((width - lineWidth) / 2, y, lineWidth, 1, color);
}
