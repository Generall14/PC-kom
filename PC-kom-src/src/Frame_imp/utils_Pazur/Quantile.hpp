#ifndef QUANTILE_HPP
#define QUANTILE_HPP

#include <QString>

class Quantile
{
    struct q
    {
        unsigned int N;
        float low;
        float high;
    };

public:
    static double getLow(unsigned int N);
    static double getHigh(unsigned int N);
    static QString makeString(float val, unsigned int N, const QString& unit);
    static QString makeStringB(float val, unsigned int N, const QString& unit);

private:
    static const q _q[];
    static q get(unsigned int N);
};

#endif
