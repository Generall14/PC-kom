#include "LogUI.hpp"

LogUI::LogUI(QFrame* parent):
    QObject()
{
    cParent = parent;
    Desc::description = "Czysta abstrakcja LogUI";
}
