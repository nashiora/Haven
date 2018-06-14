#include "ratio.h"

template <typename T>
static T GCD(T v0, T v1)
{
    while (v1 != 0)
    {
        int temp = v1;
        v1 = v0 % v1;
        v0 = temp;
    }
    return v0;
}

template <typename T>
static T LCM(T v0, T v1)
{
    return v0 / GCD(v0, v1) * v1;
}

template <typename T>
static void simplify(T &num, T &denom)
{
    int div = GCD(num, denom);
    if (div > 1)
    {
        num /= div;
        denom /= div;
    }
}

rat::rat(int num, int denom)
{
    if (denom == 0)
    {
        num = num < 0 ? -1 : num > 0 ? 1 : 0;
        goto set_fields;
    }
    else if (num == 0)
    {
        denom = 1;
        goto set_fields;
    }
    else if (denom < 0)
    {
        num = -num;
        denom = -denom;
    }

    simplify(num, denom);

set_fields:
    m_num = num;
    m_denom = denom;
}

void rat::operator +=(const rat& rhs)
{
    if (m_denom == 0 || rhs.m_denom == 0)
    {
        m_num = 0;
        m_denom = 0;
        return;
    }

    int lcm = LCM(m_denom, rhs.m_denom);
    long long na = m_num * (long long)lcm / m_denom;
    long long nb = rhs.m_num * (long long)lcm / rhs.m_denom;

    long long n = na + nb;

    m_num = (int)n;
    m_denom = lcm;
}
