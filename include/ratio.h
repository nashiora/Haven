#ifndef INCLUDEATIO_BASE_H
#define INCLUDEATIO_BASE_H

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
