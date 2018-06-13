#ifndef COLUMN_MANAGER_H
#define COLUMN_MANAGER_H

#include <QList>

#include "editor_layout.h"
#include "editor_column.h"
#include "editor_column_data.h"
#include "image_manager.h"

class ColumnManager
{
public:
    ColumnManager();

    void setLayout(EditorLayout *layout) { m_layout = layout; }
    void rearrangeColumns();

    EditorColumnWidth defaultColumnWidth() const { return m_colWidth; }
    void setDefaultColumnWidth(EditorColumnWidth colWidth);
    void toggleDefaultColumnWidth();

    bool toggleColumnWidth(int index);

    void setBackgroundColor(QColor color)
    {
        if (color == m_bgColor) return;
        m_bgColor = color;

        EditorColumn *col;
        foreach (col, m_cols)
            col->setBackgroundColor(m_bgColor);
    }

    const ImageManager &imgs() { return m_imgs; }

private:
    int containerWidth() const
    {
        QObject *parent = m_layout->parent();
        if (!parent)
            return 0;
        else if (parent->isWidgetType())
        {
            QWidget *pw = static_cast<QWidget *>(parent);
            return pw->width();
        }
        else return static_cast<QLayout *>(parent)->sizeHint().width();
    }

    void ensureColumnData(int dataCount)
    {
        if (dataCount <= m_colData.count())
            return;

        for (int i = m_colData.count() - 1; i < dataCount; i++)
            m_colData.append(EditorColumnData());
    }

    EditorColumnWidth m_colWidth = EditorColumnWidth::Standard;
    QColor m_bgColor;

    EditorLayout *m_layout;
    ImageManager m_imgs;

    int m_colOffset = 0;
    QList<EditorColumn *> m_cols;
    QList<EditorColumnData> m_colData;
};

#endif // COLUMN_MANAGER_H
