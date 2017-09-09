#include "Mendium.hpp"
#include "Factory.hpp"

Mendium::Mendium():
    EQThread()
{

}

void Mendium::Stop()
{
    stopRequest = true;
    Close();
}

bool Mendium::isOpened()
{
    return opened;
}
