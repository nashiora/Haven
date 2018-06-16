#ifndef COLUMN_MANAGER_H
#define COLUMN_MANAGER_H

#include <QList>

#include "editor_layout.h"
#include "editor_column.h"
#include "editor_column_data.h"
#include "image_manager.h"

// :local
// The column manager is what controls the 2D views note columns.
// It handles the creation/removal of columns on resize, and helps
//  to manage the container layout if necessary.
// Code which wants to mess with columns should likely come thru here
//  if at all possible.
//
// Currently a column manager has its own personal image manager,
//  but different parts of the program will eventually need image
//  access as well and shouldn't need to come thru here.
// Either we move the image manager back out to the main window
//  class and pass that to everything, or we split-up image
//  managers and optionally initialize lazily instead of up-front.

class ColumnManager
{
public:
    ColumnManager();

    // Set the layout this column manager uses.
    void setLayout(EditorLayout *layout) { m_layout = layout; }
    // Ensures that only as many columns as can fit in the container are there.
    // Will add or remove columns as needed, but WON'T re-create the entire list
    //  if it's not necessary to do so.
    // This does NOT layout the columns, only uses their size and index to determine
    //  the number of possible columns, which will be laid out later.
    void rearrangeColumns();

    // The default column width is what all non-forced columns will display with.
    ColumnWidth defaultColumnWidth() const { return m_colWidth; }
    void setDefaultColumnWidth(ColumnWidth colWidth);
    // Toggle the default column width, rather than figuring it out manually.
    void toggleDefaultColumnWidth();

    // Toggles the width of a single column at `index`, where `m_colOffset`
    //  is the origin (the far left column).
    // `m_colData[index + m_colOffset]` should be affected.
    // The behavior of a column width toggle is:
    //  - If the column width is currently the same as the default,
    //      toggle it and set the force flag.
    //  - If it's different, toggle it and remove the force flag.
    // A column whos width is forced will NOT use the default.
    // Going from a forced state to the default state should remove that flag.
    bool toggleColumnWidth(int index);

    // Changes the background color of the highways.
    // Used to help distinguish which tool is in use as in KSE.
    void setBackgroundColor(QColor color)
    {
        if (color == m_bgColor) return;
        m_bgColor = color;

        EditorColumn *col;
        foreach (col, m_cols)
            col->setBackgroundColor(m_bgColor);
    }

    // Changes how wide the background fill on a column is.
    // Used to help distinguish which tool is in use as in KSE.
    void setBackgroundWidth(ColumnBgWidth width)
    {
        if (width == m_bgWidth) return;
        m_bgWidth = width;

        EditorColumn *col;
        foreach (col, m_cols)
            col->setBackgroundWidth(m_bgWidth);
    }

    // the image manager this column manager uses.
    const ImageManager &imgs() { return m_imgs; }

private:
    // Determines the width of the parent container, if there is one.
    // If the program is running as it should, this should ALWAYS
    //  enter the second branch where the parent is a widget, which
    //  is our main container.
    // The other branches are healthy sanity checks without asserting,
    //  just in case our intentions change.
    int containerWidth() const
    {
        QObject *parent = m_layout->parent();
        // no parent, no width
        if (!parent)
            return 0;
        // widget parent, use that width
        else if (parent->isWidgetType())
        {
            QWidget *pw = static_cast<QWidget *>(parent);
            return pw->width();
        }
        // some other layout, use the size hint.
        else return static_cast<QLayout *>(parent)->sizeHint().width();
    }

    // Ensures that there's enough column data to index at
    //  `dataCount` without a bounds error.
    void ensureColumnData(int dataCount)
    {
        if (dataCount <= m_colData.count())
            return;

        for (int i = m_colData.count() - 1; i < dataCount; i++)
            m_colData.append(EditorColumnData());
    }

    ColumnWidth m_colWidth = ColumnWidth::Standard;
    QColor m_bgColor = QColor(0, 0, 0);
    ColumnBgWidth m_bgWidth = ColumnBgWidth::Fill;

    EditorLayout *m_layout;
    ImageManager m_imgs;

    int m_colOffset = 0;
    QList<EditorColumn *> m_cols;
    QList<EditorColumnData> m_colData;
};

#endif // COLUMN_MANAGER_H
