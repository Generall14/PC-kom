#ifndef EQTHREAD_HPP
#define EQTHREAD_HPP

/**
 * \class EQThread
 * @brief Klasa rozszerza podstawową klasę QThread o kilka powtarzających się mechanizmów.
 *
 * Klasa EQThread ostatecznie implementuje metodę run() w której na okrągło powtarzana jest metoda Run() aż do momentu gdy nadejdzie żądanie zatrzymania wątku, wtedy wywoływana
 * jest metoda OnStop() i wątek kończy swoją pracę. Metoda OnStart() jest wywoływana jednorazowo po rozpoczęciu pracy wątku. Metoda Run() wywoływana jest bez opóźnienia, więc
 * jeżeli nie jest konieczna ciągła praca, powinno się w niej możliwie często oddawać procesor, np. poprzez QThread::msleep(int).
 *
 * Żądanie zatrzymania pracy wątku odbywa się poprzez wywołanie slotu Stop(), po zakończeniu aktualnie wykonywanej metody Run() oraz wywołaniu OnStop() wątek zakończy działanie.
 * Aby bezpiecznie zniszczyć obiekt wątku, po wywołaniu Stop() należy poczekać na faktyczne jego zakończenie:
 * \code{.cpp}while(EQThreadObj->isRunning()){}\endcode
 * , po tym można bezpiecznie go usunąć.
 */

#include <QObject>
#include <QThread>

class EQThread : public QThread
{
    Q_OBJECT
public:
    EQThread(QObject* parent = nullptr);
    virtual ~EQThread(){}

    void run() final;                                                                   /**<Główna pętla wątku*/

public slots:
    virtual void Stop();                                                                /**<Żądanie zakończenia pracy wątku*/

protected:
    virtual void Run() = 0;                                                             /**<Metoda cyklicznie wywoływana w trakcie działania wątku*/
    virtual void OnStart();                                                             /**<Metoda wywoływana przy rozpoczęciu pracy wątku*/
    virtual void OnStop();                                                              /**<Metoda wywoływana przy kończeniu pracy wątku*/
    volatile bool stopRequest = false;                                                  /**<Zmienna przetrzymująca żądanie zatrzymania*/
};

#endif
