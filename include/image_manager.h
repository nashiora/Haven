#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <QPixmap>

#include "editor_column_data.h"

class ImageManager
{
public:
    ImageManager();

    const QPixmap &getColFor(EditorColumnWidth colWidth) const
    {
        if (colWidth == EditorColumnWidth::Standard)
            return col();
        else return col_w();
    }

    const QPixmap &col() const { return m_col; }
    const QPixmap &col_w() const { return m_col_w; }

    const QPixmap &btc() const { return m_btc; }
    const QPixmap &bth() const { return m_bth; }

    const QPixmap &fxc() const { return m_fxc; }
    const QPixmap &fxh() const { return m_fxh; }

private:
    QPixmap m_col = QPixmap(":/col");
    QPixmap m_col_w = QPixmap(":/col_w");

    QPixmap m_btc = QPixmap(":/btc");
    QPixmap m_bth = QPixmap(":/bth");

    QPixmap m_fxc = QPixmap(":/fxc");
    QPixmap m_fxh = QPixmap(":/fxh");
};

#endif // IMAGE_MANAGER_H
