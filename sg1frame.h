#ifndef SG1FRAME_H
#define SG1FRAME_H

#include <QByteArray>
#include <QString>

class SG1Frame
{
public:
    SG1Frame(QByteArray ba);

    void FromQByteArray(QByteArray ba);
    bool isValid();
    QString toQString();

private:
    QByteArray pck;
};

#endif // SG1FRAME_H
