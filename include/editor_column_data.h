#ifndef EDITOR_COLUMN_DATA_H
#define EDITOR_COLUMN_DATA_H

const int LANE_WIDTH = 9;
const int HIGHWAY_WIDTH = LANE_WIDTH * 6 + 5;

enum class EditorColumnWidth
{
    Standard,
    Extended,
};

struct EditorColumnData
{
    EditorColumnWidth columnWidth;

    void toggleColumnWidth()
    {
        if (columnWidth == EditorColumnWidth::Standard)
            columnWidth = EditorColumnWidth::Extended;
        else columnWidth = EditorColumnWidth::Standard;
    }
};

#endif // EDITOR_COLUMN_DATA_H
