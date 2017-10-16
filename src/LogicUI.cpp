#include "LogicUI.hpp"

LogicUI::LogicUI(QFrame* parent):
    QObject()
{
    cParent = parent;
    Desc::description = "Czysta abstrakcja LogicUI";
}
