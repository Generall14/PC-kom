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
    static QString makeString(double val, unsigned int N, QString unit);
    static QString makeStringB(double val, unsigned int N, QString unit);

private:
    static const q _q[];
    static q get(unsigned int N);
};

#endif
