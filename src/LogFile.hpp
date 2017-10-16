#ifndef LOGFILE_HPP
#define LOGFILE_HPP

/**
 * \class LogFile
 * @brief Interfejs klas odpowiedzialnych za zapisywanie logów do plików.
 *
 * Jedynym slotem klasy jest LogString(QString) na który są przesyłane sygnały od LogFormater z przygotowanym tekstem do zapisu. Zadaniem klasy jest zapis komunikatów do plików
 * (lub w razie potrzeby do czegokolwiek zasadnego).
 *
 * Sygnalizacja wszelkich błędów odbywa się za pomocą sygnału Error(QString).
 */

#include <QFrame>
#include <QString>
#include <QObject>

class LogFile : public QObject
{
    Q_OBJECT
public:
    LogFile(){}
    virtual ~LogFile(){}

public slots:
    virtual void LogString(QString str) = 0;                                            /**<Informacja do zapisu*/

signals:
    void Error(QString msg);                                                            /**<Informowanie o błędzie*/
};

#endif
