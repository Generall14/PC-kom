#include "LogicUISLA.hpp"
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include "../Frame_imp/FrameSLA.hpp"
#include "../FrameBuilder_imp/FrameBuilderTerminal.hpp"

LogicUISLA::LogicUISLA(QFrame* parent):
    LogicUI(parent)
{
    Desc::description = "LogicUIEmpty";
}

void LogicUISLA::Init()
{
    FrameBuilderTerminal::setPckSize(130);

    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    BuildGUI();
}

void LogicUISLA::BuildGUI()
{
    //=======================Grupa wyslijcos======================================================
    QGroupBox* groupBoxWyslijCos = new QGroupBox("Wyślij coś");
    mainLay->addWidget(groupBoxWyslijCos);
    QVBoxLayout* mainWyslijCosLay = new QVBoxLayout(groupBoxWyslijCos);


    QHBoxLayout* cameraIdLayout = new QHBoxLayout();
    mainWyslijCosLay->addLayout(cameraIdLayout);
    QLabel* label = new QLabel("Camera Id:");
    cameraIdLayout->addWidget(label);
    cameraIdLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Maximum));
    sbCameraId = new QSpinBox();
    cameraIdLayout->addWidget(sbCameraId);
    sbCameraId->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sbCameraId->setMinimum(0);
    sbCameraId->setMaximum(2);


    QHBoxLayout* firstBtnLay = new QHBoxLayout();
    mainWyslijCosLay->addLayout(firstBtnLay);
    firstBtnLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Maximum));
    QPushButton* btn = new QPushButton("getVersionNumber");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, &QPushButton::clicked, [&](){emit WriteFrame(FrameSLA::getVersionNumber());});
    firstBtnLay->addWidget(btn);

    btn = new QPushButton("getStabilizationParameters");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, &QPushButton::clicked, [&](){emit WriteFrame(FrameSLA::getStabilizationParameters(CameraId()));});
    firstBtnLay->addWidget(btn);

    btn = new QPushButton("getStabilizationBias");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(GetStabilizationBias()));
    firstBtnLay->addWidget(btn);

    btn = new QPushButton("resetAllParameters");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, &QPushButton::clicked, [&](){emit WriteFrame(FrameSLA::resetAllParameters());});
    firstBtnLay->addWidget(btn);

    QHBoxLayout* firstBBtnLay = new QHBoxLayout();
    mainWyslijCosLay->addLayout(firstBBtnLay);
    firstBBtnLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Maximum));
    btn = new QPushButton("resetStabilizationparameters");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, &QPushButton::clicked, [&](){emit WriteFrame(FrameSLA::resetStabilizationParameters(CameraId()));});
    firstBBtnLay->addWidget(btn);

    btn = new QPushButton("Demo");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(DemoMode()));
    firstBBtnLay->addWidget(btn);

    //=======================Grupa stabilizacja===================================================
    QGroupBox* groupBoxStab = new QGroupBox("Stabilizacja");
    mainLay->addWidget(groupBoxStab);
    QVBoxLayout* mainStabLay = new QVBoxLayout(groupBoxStab);


    QHBoxLayout* secBtnLay = new QHBoxLayout();
    mainStabLay->addLayout(secBtnLay);
    secBtnLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Maximum));
    btn = new QPushButton("Stab On");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(StabOn()));
    secBtnLay->addWidget(btn);

    btn = new QPushButton("Stab mid");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(StabMid()));
    secBtnLay->addWidget(btn);

    btn = new QPushButton("Stab off");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(StabOff()));
    secBtnLay->addWidget(btn);

    //=======================Grupa wideotraker====================================================
    QGroupBox* groupBoxTrack = new QGroupBox("Tracker");
    mainLay->addWidget(groupBoxTrack);
    QVBoxLayout* mainTrackLay = new QVBoxLayout(groupBoxTrack);


    QHBoxLayout* thBtnLay = new QHBoxLayout();
    mainTrackLay->addLayout(thBtnLay);
    thBtnLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Maximum));
    btn = new QPushButton("Start");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(StartTracking()));
    thBtnLay->addWidget(btn);

    btn = new QPushButton("Stop");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, &QPushButton::clicked, [&](){emit WriteFrame(FrameSLA::stopTracking(CameraId()));});
    thBtnLay->addWidget(btn);

    btn = new QPushButton("Start report");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(StartReporting()));
    thBtnLay->addWidget(btn);

    btn = new QPushButton("Stop report");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(StopReporting()));
    thBtnLay->addWidget(btn);

    btn = new QPushButton("TestT");
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(TestT()));
    thBtnLay->addWidget(btn);


    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void LogicUISLA::Connected()
{
    cParent->setEnabled(true);
}

void LogicUISLA::Disconnected()
{
    cParent->setEnabled(false);
}

void LogicUISLA::FrameReaded(QSharedPointer<Frame> frame)
{
    frame.isNull();
}

int LogicUISLA::CameraId()
{
    return sbCameraId->value();
}

void LogicUISLA::StabOn()
{
    SLASetStabilizationParameters_t temp;
    memset(temp.bytes, 0u, sizeof(temp));
    temp.val.cameraIndex = CameraId();
    temp.val.mode=0x1u;
    temp.val.rate=0u;
    emit WriteFrame(FrameSLA::setStabilizationParameters(temp));

    SLAStabilizationBias_t temp2;
    memset(temp2.bytes, 0u, sizeof(temp2));
    temp2.val.cameraIndex = CameraId();
    temp2.val.autoBias = 1u;
    temp2.val.updateRate = 0u;
    emit WriteFrame(FrameSLA::stabilizationBias(temp2));
}

void LogicUISLA::StabMid()
{
    SLASetStabilizationParameters_t temp;
    memset(temp.bytes, 0u, sizeof(temp));
    temp.val.cameraIndex = CameraId();
    temp.val.mode=0x1u;
    temp.val.rate=70u;
    emit WriteFrame(FrameSLA::setStabilizationParameters(temp));

    SLAStabilizationBias_t temp2;
    memset(temp2.bytes, 0u, sizeof(temp2));
    temp2.val.cameraIndex = CameraId();
    temp2.val.autoBias = 1u;
    temp2.val.updateRate = 70u;
    emit WriteFrame(FrameSLA::stabilizationBias(temp2));
}

void LogicUISLA::StabOff()
{
    SLASetStabilizationParameters_t temp;
    memset(temp.bytes, 0u, sizeof(temp));
    temp.val.cameraIndex = CameraId();
    temp.val.mode=0x0u;
    emit WriteFrame(FrameSLA::setStabilizationParameters(temp));

    emit WriteFrame(FrameSLA::resetStabilizationParameters(CameraId()));
}

void LogicUISLA::GetStabilizationBias()
{
    emit WriteFrame(FrameSLA::getParameters(FrameSLA::PARAM_ID_STABILIZATION_BIAS, CameraId()));
}

void LogicUISLA::StartTracking()
{
    SLASetTrackingParameters_t tempt;
    memset(tempt.bytes, 0u, sizeof(tempt));
    tempt.val.cameraIndex = CameraId();
    tempt.val.objectSize = 80;
    tempt.val.mode = 0x68u;//inteligent assist
    tempt.val.maxMisses = 0x2du;
    tempt.val.nearVal = 0x00ffu;
    emit WriteFrame(FrameSLA::setTrackingParameters(tempt));

    SLAStartTracking_t temp;
    memset(temp.bytes, 0u, sizeof(temp));
    temp.val.cameraIndex = CameraId();
    temp.val.col=320;
    temp.val.row=240;
    temp.val.width=00;
    temp.val.height=00;
    temp.val.flags=6;
    emit WriteFrame(FrameSLA::startTracking(temp));
}

void LogicUISLA::DemoMode()
{
    SLASetSystemValue_t temp;
    memset(temp.bytes, 0u, sizeof(temp));
    temp.val.systemValue = FrameSLA::SYSTEM_VALUE_DEMO_MODE;
    temp.val.value0 = 1;
    emit WriteFrame(FrameSLA::setSystemValue(temp));
}

void LogicUISLA::StartReporting()
{
    SLACoordinateReportingMode_t temp;
    memset(temp.bytes, 0u, sizeof(temp));
    temp.val.framePeriod = 10u;
    temp.val.flags = 1u;
    temp.val.cameraIdx = CameraId();
    emit WriteFrame(FrameSLA::coordinatingReportingMode(temp));
}

void LogicUISLA::StopReporting()
{
    SLACoordinateReportingMode_t temp;
    memset(temp.bytes, 0u, sizeof(temp));
    temp.val.framePeriod = 00u;
    temp.val.flags = 0u;
    temp.val.cameraIdx = CameraId();
    emit WriteFrame(FrameSLA::coordinatingReportingMode(temp));
}

void LogicUISLA::TestT()
{
}


