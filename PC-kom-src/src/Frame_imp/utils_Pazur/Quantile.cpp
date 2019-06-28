#include "Quantile.hpp"
#include <QDebug>
#include "src/Utils/StaticUtils.hpp"

const Quantile::q Quantile::_q[] = {{1,5.00012500416628E-05,9.9034875525363},
                                   {2,0.005016743455942,6.25333564259579},
                                    {3,0.022696873820503,4.90828749023597},
                                    {4,0.048359564747205,4.18771502462585},
                                    {8,0.156677945002853,2.99112992011245},
                                    {12,0.240643532392155,2.53129799581422},
                                    {16,0.303833078208023,2.27765060356302},
                                    {32,0.453599271301824,1.83903409360166},
                                    {64,0.58533576302866,1.56145206902782},
                                    {96,0.650958691999826,1.44700433194637},
                                    {128,0.692262533918695,1.38124887387405},
                                    {256,0.77501531523824,1.26176971981032},
                                    {384,0.813606949247811,1.21092292113354},
                                    {512,0.837182432887743,1.1812174119031},
                                    {1024,0.882993028262374,1.12620872524102},
                                    {2048,0.916320429436338,1.08828090500262},
                                    {3072,0.931333842394451,1.07173381559757},
                                    {4096,0.940356537622928,1.06194424400708},
                                    {8192,0.957588650112113,1.04356176930411},
                                    {16384,0.969891939993799,1.03068327686444},
                                    {32768,0.978650970094765,1.02163664012189},
                                    {65536,0.984874225807445,1.01526957974771}};

double Quantile::getLow(unsigned int N)
{
    return get(N).low;
}

double Quantile::getHigh(unsigned int N)
{
    return get(N).high;
}

Quantile::q Quantile::get(unsigned int N)
{
    uint size = (sizeof(_q)/sizeof(*_q));
    uint min = 100e6, idx = 0;
    for(uint i=0;i<size;i++)
    {
        uint diff = abs(int(N-_q[i].N));
        if(diff<min)
        {
            min = diff;
            idx = i;
        }
    }
    return _q[idx];
}

QString Quantile::makeString(float val, unsigned int N, const QString& unit)
{
    QString temp="(";

    temp += SU::displayFloat(val*getLow(N), 2, 'f')+unit+" - ";
    temp += SU::displayFloat(val*getHigh(N), 2, 'f')+unit+")";

    return temp;
}

QString Quantile::makeStringB(float val, unsigned int N, const QString& unit)
{
    QString temp=SU::displayFloat(val, 2, 'f')+unit+"(+";
    temp += QString::number((getHigh(N)-1)*100, 'f', 2)+"%, -";
    temp += QString::number((1-getLow(N))*100, 'f', 2)+"%)";

    return temp;
}
