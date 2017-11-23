#ifndef ZR3UIFRAME_HPP
#define ZR3UIFRAME_HPP

#include <QObject>
#include <QStringList>
#include <QList>
#include "../../Frame.hpp"
#include "devClass.hpp"
#include "ZR3ReadFile.hpp"
#include "ZR3UIFrameUI.hpp"

class ZR3UIFrame : public QObject
{
    Q_OBJECT
    friend class ZR3UIFrameUI;
public:
    ZR3UIFrame(QFrame* parent, uchar adr);
    ~ZR3UIFrame();

    void Init();
    uchar Adr() const;

public slots:
    void FrameToUI(QSharedPointer<Frame> frame);

signals:
    void FrameToMendium(QSharedPointer<Frame> frame);
    void PureDataToMedium(QByteArray ar);
    void InternalDataReaded(QByteArray ba);
    void AdresChanged(uchar);
    void Error(QString);

protected:
    QFrame* cFrame = NULL;
    ZR3UIFrameUI* ui = NULL;
    uchar _adr;
    static const char _myAdr = 0xFE;

    ZR3ReadFile* rfile = NULL;
    void InitZR3ReadFile(uchar header);

    QByteArray strings;
    QList<QStringList> stringi;
    int currentLang = 0;
    void ParseStrings();

    QByteArray devDescriptor;
    QStringList parsedDevDesc;
    QList<davClass> devClasses;
    void ParseDevice();

    QByteArray methDescriptor;

    QString ConcStringPointers(QList<int> ptrs, int lang);

protected slots:
    //Metody warstwy protokołu:
    void protSET_ADR();
    void protSET_NEXT_ADR();
    void protHELLO();

    //Metody warstwy aplikacji:
    void aplReadReq(QString type, int offset, char size);

    void FinalizeZR3ReadFile(uchar _header, QByteArray arr);
    void UpdateCurrentLanguage(int newLang);
};

#endif
