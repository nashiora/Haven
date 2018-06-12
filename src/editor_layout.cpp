#include "editor_layout.h"

EditorLayout::EditorLayout(QWidget *parent, int margin, int hSpacing)
    : QLayout(parent), m_hSpace(hSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

EditorLayout::EditorLayout(int margin, int hSpacing)
    : m_hSpace(hSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

EditorLayout::~EditorLayout()
{
    while (itemList.count() > 0)
        delete takeAt(0);
}

int EditorLayout::addColumn(EditorColumn *col)
{
    addWidget(col);
    return doLayout(QRect(), true);
}
void EditorLayout::addItem(QLayoutItem *item)
{
    if (EditorColumn *col = qobject_cast<EditorColumn *>(item->widget()))
    {
        itemList.append(item);
    }
    else
    {
        // TODO(local): error, don't add non-column widgets please!
    }
}
int EditorLayout::horizontalSpacing() const { return m_hSpace >= 0 ? m_hSpace : smartSpacing(QStyle::PM_LayoutHorizontalSpacing); }

Qt::Orientations EditorLayout::expandingDirections() const { return 0; }

int EditorLayout::count() const { return itemList.count(); }
QLayoutItem *EditorLayout::itemAt(int index) const { return itemList.value(index); }
QLayoutItem *EditorLayout::takeAt(int index) { if (index >= 0) return itemList.takeAt(index); else return 0; }

QSize EditorLayout::minimumSize() const
{
    QSize size;
    QLayoutItem *item;
    foreach (item, itemList)
        size = size.expandedTo(item->minimumSize());
    size += QSize(2 * margin(), 2 * margin());
    return size;
}
void EditorLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}
QSize EditorLayout::sizeHint() const { return minimumSize(); }

int EditorLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(left, top, -right, -bottom);

    int x = effectiveRect.x();
    int y = effectiveRect.y();

    int height = effectiveRect.height();

    QLayoutItem *item;
    foreach (item, itemList)
    {
        QWidget *wid = item->widget();

        int spaceX = horizontalSpacing();
        if (spaceX == -1)
            spaceX = wid->style()->layoutSpacing(QSizePolicy::PushButton,
                                                 QSizePolicy::PushButton, Qt::Horizontal);

        int nextX = x + wid->width() + spaceX;
        if (!testOnly) item->setGeometry(QRect(QPoint(x, y), QSize(wid->width(), height)));

        x = nextX;
    }

    return x;
}

int EditorLayout::smartSpacing(QStyle::PixelMetric pm) const
{
    QObject *parent = this->parent();
    if (!parent)
        return -1;
    else if (parent->isWidgetType())
    {
        QWidget *pw = static_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, 0, pw);
    }
    else return static_cast<QLayout *>(parent)->spacing();
}
