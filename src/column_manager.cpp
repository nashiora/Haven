#include "column_manager.h"

ColumnManager::ColumnManager()
{
}

void ColumnManager::rearrangeColumns()
{
    ensureColumnData(m_cols.count() + m_colOffset);

    int margin = m_layout->margin();
    int spacing = m_layout->horizontalSpacing();

    int maxWidth = containerWidth();

    int xMax = margin;
    if (m_cols.count() > 0)
    {
        EditorColumn *col; int i = 0;
        foreach (col, m_cols)
        {
            col->applyData(m_colData[m_colOffset + i]);
            xMax += col->width() + spacing;

            i++;
        }
    }

    if (xMax > maxWidth)
    {
        for (int i = m_cols.count() - 1; i >= 0; i--)
        {
            EditorColumn *col = m_cols.at(i);

            int xEnd = xMax - spacing - col->width();
            if (xEnd <= maxWidth)
                break;

            xMax = xEnd;

            m_layout->removeWidget(col);
            col->deleteLater();

            m_cols.removeLast();
        }
    }
    else
    {
        while (true)
        {
            ensureColumnData(m_colData.count() + 1);

            auto col = new EditorColumn(m_imgs);
            col->applyData(m_colData[m_colOffset + m_cols.count()]);

            xMax = m_layout->addColumn(col);
            m_cols.append(col);

            if (xMax > maxWidth)
                break;
        }
    }
}

void ColumnManager::setDefaultColumnWidth(EditorColumnWidth colWidth)
{
    m_colWidth = colWidth;
}

bool ColumnManager::toggleColumnWidth(int index)
{
    if (index < m_cols.count())
    {
        auto col = m_cols.at(index);
        col->toggleColumnWidth();

        int dataIndex = index + m_colOffset;
        assert(dataIndex >= 0 && dataIndex < m_colData.count());
        m_colData[dataIndex].toggleColumnWidth();

        rearrangeColumns();
        m_layout->update();

        return true;
    }

    return false;
}
