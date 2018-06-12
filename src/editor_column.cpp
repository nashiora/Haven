#include "editor_column.h"

EditorColumn::EditorColumn(ImageManager &imgs, QWidget *parent)
    : QWidget(parent), m_imgs(imgs)
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
    painter.fillRect(0, 0, width, height, m_bgColor);

    { // draw the column texture
        QRect targetRect(0, 0, width, height);
        QRect sourceRect(0, 0, width, 1);

        painter.drawPixmap(targetRect, m_imgs.getColFor(m_colWidth), sourceRect);
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
    resize(colWidth == EditorColumnWidth::Standard ? HIGHWAY_WIDTH : 109, 0);
}
