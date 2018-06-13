#include "include/chart.h"

#include <QtMath>

pos_t::pos_t(qint64 num, qint64 denom)
{
    if (denom == 0)
        num = (num < 0 ? -1 : num > 0 ? 1 : 0);
    else if (num == 0)
        denom = 1;

    simplify();

    this->num = num;
    this->denom = denom;
}
pos_t::pos_t(pos_t that) : num(that.num), denom(that.denom) { }

pos_t::simplify()
{
}

void pos_t::operator =(pos_t that)
{
    this->num = that.num;
    this->denom() = that.denom;
}

void pos_t::operator +=(pos_t that) { *this = *this + that; }
void pos_t::operator -=(pos_t that) { *this = *this - that; }
void pos_t::operator *=(qint64 that) { *this = *this * that; }

pos_t pos_t::operator +(pos_t that) const;
pos_t pos_t::operator -(pos_t that) const;
pos_t pos_t::operator *(qint64 that) const { return pos_t(num * that, denom); }

Chart::Chart()
{
}
