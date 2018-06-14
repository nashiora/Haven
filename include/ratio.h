#ifndef INCLUDEATIO_BASE_H
#define INCLUDEATIO_BASE_H

// :local
// I have plans for this to support "invalid" ratios as
//  N / 0 where N can either be -1, 0 or 1 for -INF, NaN and +INF.
// We can always throw or assert if that happens instead,
//  since this doesn't HAVE to be super general purpose and invalid
//  chart positions and such are likely VERY bad.

// TODO(local): all of the ratio conversion and operator functions

class rat
{
public:
    rat(int num, int denom);
    rat(const rat &that)
        : m_num(that.m_num), m_denom(that.m_denom) { }

    void operator =(const rat &that)
    {
        m_num = that.m_num;
        m_denom = that.m_denom;
    }

    inline int num() const { return m_num; }
    inline int denom() const { return m_denom; }

    void operator +=(const rat& rhs);

private:
    rat(int num, int denom, bool dummy)
        : m_num(num), m_denom(denom) { }

    int m_num;
    int m_denom;
};

#endif // INCLUDEATIO_BASE_H
