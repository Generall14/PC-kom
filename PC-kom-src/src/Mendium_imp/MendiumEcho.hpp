#ifndef MENDIUMECHO_HPP
#define MENDIUMECHO_HPP

#include "../Mendium.hpp"

class MendiumEcho : public Mendium
{
    Q_OBJECT
public:
    MendiumEcho();
    virtual ~MendiumEcho();

public slots:
    virtual void Open(QString);
    virtual void Close();
    virtual void Write(QSharedPointer<Frame> fr);
    virtual void Flush();

protected:
    virtual void Run();

};

#endif
