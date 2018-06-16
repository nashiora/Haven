#ifndef EDITOR_COLUMN_H
#define EDITOR_COLUMN_H

#include <QtWidgets>

#include "editor_column_data.h"

class ColumnManager;

class EditorColumn : public QWidget
{
    Q_OBJECT

public:
    EditorColumn(ColumnManager *colManager, QWidget *parent = nullptr);

    void applyData(const EditorColumnData &data);

    ColumnWidth columnWidth() const { return m_colWidth; }
    void setColumnWidth(ColumnWidth colWidth);
    void toggleColumnWidth()
    {
        if (m_colWidth == ColumnWidth::Standard)
            forceUpdateColumnWidth(ColumnWidth::Extended);
        else forceUpdateColumnWidth(ColumnWidth::Standard);
    }

    void setBackgroundColor(QColor color) { m_bgColor = color; repaint(); }
    void setBackgroundWidth(ColumnBgWidth width) { m_bgWidth = width; repaint(); }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void forceUpdateColumnWidth(ColumnWidth colWidth);

    void paintDivisionBar(int y, bool isMeasureStart, QPainter &painter);

    ColumnManager *m_colManager;

    QColor m_bgColor = QColor(30, 36, 24);
    ColumnBgWidth m_bgWidth = ColumnBgWidth::Fill;
    ColumnWidth m_colWidth = ColumnWidth::Standard;
};

#endif // EDITOR_COLUMN_H
