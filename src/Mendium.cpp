#include "Mendium.hpp"
#include "Factory.hpp"

Mendium::Mendium():
    EQThread()
{
    Desc::description = "Czysta abstrakcja Mendium";
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
