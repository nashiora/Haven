#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <QPixmap>

#include "editor_column_data.h"

// :local
// I'm not sure how I want to handle this kinda stuff in the long run,
//  but we only need access to a few image resources so a huge system
//  for dynamically handling image loads/unloads seems unnecessary.
// This simply initializes every QPixmap from a binary resource
//  (where the `:` prefix means Qts resources, as described in the
//   resources.rc file in this project) and allows const references
//  to those fields for use.

// TODO(local): see if resource management is needed

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
