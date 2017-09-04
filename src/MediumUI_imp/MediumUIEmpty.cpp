#include "MediumUIEmpty.hpp"

#include <QLabel>

MediumUiEmpty::MediumUiEmpty(QFrame* parent):
    MediumUI(parent)
{

}

void MediumUiEmpty::Init()
{
    new QLabel("Nic tu nie ma - testowa implementacja klasy MediumUI", cParent);
}

void MediumUiEmpty::Connected()
{

}

void MediumUiEmpty::Disconnected()
{

}
