#ifndef EDITOR_COLUMN_DATA_H
#define EDITOR_COLUMN_DATA_H

const int COL_LANE_WIDTH = 9;
const int COL_BORDER_WIDTH = 1;

const int COL_WIDTH = 59;
const int COL_WIDTH_EXT = 109;

enum class ColumnWidth
{
    Standard,
    Extended,
};

enum class ColumnBgWidth
{
    Fill,
    BtOnly,
    BtVol,
};

struct EditorColumnData
{
    ColumnWidth columnWidth = ColumnWidth::Standard;
    bool forceWidth = false;

    void toggleColumnWidth()
    {
        if (columnWidth == ColumnWidth::Standard)
            columnWidth = ColumnWidth::Extended;
        else columnWidth = ColumnWidth::Standard;
    }
};

#endif // EDITOR_COLUMN_DATA_H
