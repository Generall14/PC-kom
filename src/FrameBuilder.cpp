#include "FrameBuilder.hpp"

FrameBuilder::FrameBuilder()
{

}

void FrameBuilder::run()
{
    while(!stopRequest)
    {
        this->Run();
    }
}

void FrameBuilder::Stop()
{
    stopRequest = true;
}
