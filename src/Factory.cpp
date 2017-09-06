#include "Factory.hpp"

#include "Frame_imp/FrameEmpty.hpp"

#include "MediumUI_imp/MediumUIEmpty.hpp"
#include "MediumUI_imp/MediumUIRS.hpp"

#include "Mendium_imp/MendiumEmpty.hpp"
#include "Mendium_imp/MendiumRS.hpp"

Factory::frameFormat Factory::frame = Factory::frameEmpty;
Factory::mediumUiFormat Factory::mediumui = Factory::mediumUIEmpty;
Factory::mendiumFormat Factory::mendium = Factory::mendiumEmpty;
QString Factory::windowName = "XXX";

void Factory::Config(frameFormat ff, mediumUiFormat muif, mendiumFormat mf, QString name)
{
    Factory::frame = ff;
    Factory::mediumui = muif;
    Factory::mendium = mf;
    Factory::windowName = name;
}

Frame* Factory::newFrame(QByteArray ba)
{
    switch (frame)
    {
    case Factory::frameNone:
        return NULL;
    case Factory::frameEmpty:
        return new FrameEmpty(ba);
    case Factory::frameSG1:
        return NULL;//-----------------------------------------------
    }
    return NULL;
}

MediumUI* Factory::newMediumUI(QFrame *fr)
{
    switch (mediumui)
    {
    case Factory::mediumUINone:
        return NULL;
    case Factory::mediumUIEmpty:
        return new MediumUiEmpty(fr);
    case Factory::mediumUIRS:
        return new MediumUiRS(fr);
    }
    return NULL;
}

Mendium* Factory::newMendium()
{
    switch (mendium)
    {
    case Factory::mendiumNone:
        return NULL;
    case Factory::mendiumEmpty:
        return new MendiumEmpty();
    case Factory::mendiumRS:
        return new MendiumRS();
    }
    return NULL;
}

int Factory::readTimeout()
{
    Frame* temp = Factory::newFrame(QByteArray());
    int tempv = temp->ReadTimeout();
    delete temp;
    return tempv;
}

int Factory::writeTimeout()
{
    Frame* temp = Factory::newFrame(QByteArray());
    int tempv = temp->WriteTimeout();
    delete temp;
    return tempv;
}

int Factory::frameLength()
{
    Frame* temp = Factory::newFrame(QByteArray());
    int tempv = temp->FrameLength();
    delete temp;
    return tempv;
}

QString Factory::WindowName()
{
    return windowName;
}
