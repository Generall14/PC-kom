#ifndef ABOUT_HPP
#define ABOUT_HPP

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QPixmap>

class About : public QDialog
{
    Q_OBJECT
public:
    About(QString mediumUI, QString logicUI, QString logUI, QWidget* parent);
    ~About();

private:
    void InitWidgets();
    QPixmap pic;
    QString _mediumUI;
    QString _logicUI;
    QString _logUI;
};

#endif
