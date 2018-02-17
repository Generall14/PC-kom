#include "MediumUI.hpp"

MediumUI::MediumUI(QFrame* parent):
    QObject()
{
    cParent = parent;
    Desc::description = "Czysta abstrakcja MediumUI";
}
