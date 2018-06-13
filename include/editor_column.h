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

    EditorColumnWidth columnWidth() const { return m_colWidth; }
    void setColumnWidth(EditorColumnWidth colWidth);
    void toggleColumnWidth()
    {
        if (m_colWidth == EditorColumnWidth::Standard)
            forceUpdateColumnWidth(EditorColumnWidth::Extended);
        else forceUpdateColumnWidth(EditorColumnWidth::Standard);
    }

    void setBgColor(QColor color) { m_bgColor = color; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void forceUpdateColumnWidth(EditorColumnWidth colWidth);

    ColumnManager *m_colManager;

    QColor m_bgColor = QColor(0, 0, 0);
    EditorColumnWidth m_colWidth;
};

#endif // EDITOR_COLUMN_H
