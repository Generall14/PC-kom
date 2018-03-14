#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * \class MainWindow
 * @brief Klasa zbierająca i łącząca cały ambaras.
 *
 * Klasa wyłuskuje z fabryki abstrakcyjnej Factory konkretne implementacje poszczególnych klas abstrakcyjnych, następnie łączy je sygnałami i slotami według ustalonej strukturt (patrz
 * mainpage.dox). Generuje również szkielet GUI.
 */

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QFrame>
#include <QKeyEvent>
#include "src/MediumUI.hpp"
#include "src/Mendium.hpp"
#include "src/LogicUI.hpp"
#include "src/FrameBuilder.hpp"
#include "src/LogUI.hpp"
#include "src/LogFile.hpp"
#include "src/LogFormater.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QFrame* frameMedium = nullptr;
    QFrame* frameLogicUI = nullptr;
    QFrame* frameLogUI = nullptr;

    MediumUI* mediumUI = nullptr;
    Mendium* mendium = nullptr;
    LogicUI* logicUI = nullptr;
    FrameBuilder* frameBuilder = nullptr;
    LogUI* logUI = nullptr;
    LogFile* logFile = nullptr;
    LogFormater* logFormater = nullptr;

    void InitGUI();
    void InitStructure();
    virtual void keyPressEvent(QKeyEvent *event);

public slots:
    void ErrorMessage(QString er);

signals:
    void FakeDiscinnect();
    void HALT();
};

#endif // MAINWINDOW_H
