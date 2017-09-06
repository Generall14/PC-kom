#include "Mendium.hpp"
#include "Factory.hpp"

Mendium::Mendium()
{

}

void Mendium::run()
{
    while(!stopRequest)
    {
        this->Run();
    }
    Close();
}

void Mendium::Stop()
{
    stopRequest = true;
}

bool Mendium::isOpened()
{
    return opened;
}
