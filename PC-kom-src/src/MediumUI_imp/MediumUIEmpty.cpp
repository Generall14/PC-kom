#include "MediumUIEmpty.hpp"

#include <QLabel>

MediumUiEmpty::MediumUiEmpty(QFrame* parent):
    MediumUI(parent)
{
    description = "MediumUiEmpty";
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
