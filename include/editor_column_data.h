#ifndef EDITOR_COLUMN_DATA_H
#define EDITOR_COLUMN_DATA_H

const int COL_LANE_WIDTH = 9;
const int COL_BORDER_WIDTH = 1;

const int COL_WIDTH = 59;
const int COL_WIDTH_EXT = 109;

enum class EditorColumnWidth
{
    Standard,
    Extended,
};

struct EditorColumnData
{
    EditorColumnWidth columnWidth = EditorColumnWidth::Standard;
    bool forceWidth = false;

    void toggleColumnWidth()
    {
        if (columnWidth == EditorColumnWidth::Standard)
            columnWidth = EditorColumnWidth::Extended;
        else columnWidth = EditorColumnWidth::Standard;
    }
};

#endif // EDITOR_COLUMN_DATA_H
