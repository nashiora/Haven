#ifndef EDITOR_LAYOUT_H
#define EDITOR_LAYOUT_H

#include <QStyle>
#include <QWidget>
#include <QLayout>

#include "editor_column.h"

class EditorLayout : public QLayout
{
public:
    EditorLayout(QWidget *parent, int margin = -1, int hSpacing = -1);
    EditorLayout(int margin = -1, int hSpacing = -1);
    ~EditorLayout();

    int addColumn(EditorColumn *col);
    void addItem(QLayoutItem *item) override;
    int horizontalSpacing() const;
    Qt::Orientations expandingDirections() const override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;
    QSize sizeHint() const override;

private:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem *> itemList;
    int m_hSpace;
};

#endif // EDITOR_LAYOUT_H
