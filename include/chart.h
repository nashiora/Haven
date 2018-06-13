#ifndef CHART_H
#define CHART_H

#include <QList>
#include <QtNumeric>

class pos_t
{
public:
    pos_t(qint64 num, qint64 denom);
    pos_t(pos_t that) : num(that.num), denom(that.denom) { }

    void operator =(pos_t that);
    void operator +=(pos_t that);
    void operator -=(pos_t that);
    void operator *=(qint64 that);

    pos_t operator +(pos_t that) const;
    pos_t operator -(pos_t that) const;
    pos_t operator *(qint64 that) const;

    qint64 num() const { return num; }
    void setNum(qint64 num) { this->num = num; }
    qint64 denom() const { return denom; }

private:
    void simplify();

    qint64 num, denom;
};

class TimingSection
{
};

class ChartObject
{
};

class ChartEvent
{
};

class ChartBuilder;

class Chart
{
    friend class ChartBuilder;

public:
    Chart();

private:
    QList<TimingSection> m_secs;
    QList<ChartObject> m_objs[6];
    QList<ChartObject> m_evts;
};

#endif // CHART_H
