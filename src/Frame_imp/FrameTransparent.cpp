#include "FrameTransparent.hpp"

FrameTransparent::displayMethod FrameTransparent::_displayMethod = FrameTransparent::hex;
char FrameTransparent::_invalidAsciiSign = '?';
char FrameTransparent::_hexSpecifier = '\\';

FrameTransparent::FrameTransparent(QByteArray ba)
    :Frame(ba)
{
    Desc::description = "FrameTransparent";
}

bool FrameTransparent::isValid()
{
    return true;
}

QString FrameTransparent::toQString()
{
    QString temp;
    char v;
    switch(getDisplayMethod())
    {
    case mixed:
        v = getHexSpecifier();
        temp.append("&#60;");
        for(QByteArray::iterator it = pck.begin();it<pck.end();it++)
        {
            if((*it<0x20)||(*it>0x7e))
            {
                temp.append(v+QString("%1").arg(((int)(*it))&0xFF, 2, 16, QChar('0')).toUpper());
            }
            else
                temp.append(*it);
        }
        temp.append('>');
        break;
    case ascii:
        v = getInvalidAsciiSign();
        temp.append("&#60;");
        for(QByteArray::iterator it = pck.begin();it<pck.end();it++)
        {
            if((*it<0x20)||(*it>0x7e))
                *it = v;
        }
        temp.append(pck);
        temp.append('>');
        break;
    case hex:
    default:
        for(auto s: pck)
            temp.append(QString("0x%1 ").arg(((int)(s))&0xFF, 2, 16, QChar('0')));
        temp.remove(temp.size()-1, 1);
        temp = temp.toUpper();
        temp = temp.replace("X", "x");
        break;
    }
    return temp;
}

QString FrameTransparent::toShortQString()
{
    return "XXX";
}

QByteArray FrameTransparent::magicNumbers()
{
    return "XXX";
}

FrameTransparent::displayMethod FrameTransparent::getDisplayMethod()
{
    return _displayMethod;
}

char FrameTransparent::getInvalidAsciiSign()
{
    return _invalidAsciiSign;
}

char FrameTransparent::getHexSpecifier()
{
    return _hexSpecifier;
}

void FrameTransparent::setDisplayMethod(FrameTransparent::displayMethod _method)
{
    _displayMethod = _method;
}

void FrameTransparent::setInvalidAsciiSign(char _sign)
{
    _invalidAsciiSign = _sign;
}

void FrameTransparent::setHexSpecifier(char _sign)
{
    _hexSpecifier = _sign;
}
