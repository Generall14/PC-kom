#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include "src/MediumUI.hpp"
#include "src/Mendium.hpp"
#include "src/LogicUI.hpp"
#include "src/FrameBuilder.hpp"
#include "src/LogUI.hpp"
#include "src/LogFile.hpp"
#include "src/LogFormater.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    MediumUI* mediumUI = NULL;
    Mendium* mendium = NULL;
    LogicUI* logicUI = NULL;
    FrameBuilder* frameBuilder = NULL;
    LogUI* logUI = NULL;
    LogFile* logFile = NULL;
    LogFormater* logFormater = NULL;

public slots:
    void ErrorMessage(QString er);

signals:
    void FakeDiscinnect();
    void HALT();
};

#endif // MAINWINDOW_H
