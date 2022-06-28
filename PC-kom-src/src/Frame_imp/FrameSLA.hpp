#ifndef FRAMESLA_HPP
#define FRAMESLA_HPP

#include <QByteArray>
#include "../Frame.hpp"
#include "FrameTransparent.hpp"

#pragma pack(push)
#pragma pack(1)
typedef union
{
    struct
    {
        uint8_t mode;
        uint8_t rate;
        uint8_t translationLimit;
        uint8_t angleLimit;
        uint8_t cameraIndex;
        uint8_t maxStabOff;
    } val;
    uint8_t bytes[sizeof(val)];
} SLASetStabilizationParameters_t;

typedef union
{
    struct
    {
        uint8_t cameraIndex;
        int16_t biasCol;
        int16_t biasRow;
        uint8_t autoBias;
        uint8_t updateRate;
    } val;
    uint8_t bytes[sizeof(val)];
} SLAStabilizationBias_t;

typedef union
{
    struct
    {
        uint8_t cameraIndex;
        uint16_t col;
        uint16_t row;
        uint16_t width;
        uint16_t height;
        uint8_t flags;
        uint16_t nearVal;
        uint8_t userTrackId;
    } val;
    uint8_t bytes[sizeof(val)];
} SLAStartTracking_t;

typedef union
{
    struct
    {
        uint32_t systemValue;
        uint32_t setMode;
        int32_t value0;
        int32_t value1;
        int32_t value2;
        int32_t value3;
    } val;
    uint8_t bytes[sizeof(val)];
} SLASetSystemValue_t;

typedef union
{
    struct
    {
        uint8_t framePeriod;
        uint16_t flags;
        uint8_t cameraIdx;
    } val;
    uint8_t bytes[sizeof(val)];
} SLACoordinateReportingMode_t ;

typedef union
{
    struct
    {
        uint8_t reserved1;
        uint8_t reserved2;
        uint8_t reserved3;
        uint8_t cameraIndex;
    } val;
    uint8_t bytes[sizeof(val)];
} SLAStopTracking_t;

typedef union
{
    struct
    {
        uint8_t objectSize;
        uint8_t mode;
        uint8_t mode2;
        uint8_t maxMisses;
        uint16_t nearVal;
        uint8_t objectHeight;
        uint8_t cameraIndex;
    } val;
    uint8_t bytes[sizeof(val)];
} SLASetTrackingParameters_t;
#pragma pack(pop)

class FrameSLA : public FrameTransparent
{
public:
    FrameSLA(QByteArray ba);
    FrameSLA(uint8_t cmd_id, QByteArray data=QByteArray());
    ~FrameSLA(){}

    static QSharedPointer<Frame> getVersionNumber();
    static QSharedPointer<Frame> resetAllParameters();
    static QSharedPointer<Frame> getStabilizationParameters(uint8_t cameraId);
    static QSharedPointer<Frame> setStabilizationParameters(SLASetStabilizationParameters_t params);
    static QSharedPointer<Frame> resetStabilizationParameters(uint8_t cameraId);
    static QSharedPointer<Frame> startTracking(SLAStartTracking_t params);
    static QSharedPointer<Frame> stopTracking(uint8_t cameraId);
    static QSharedPointer<Frame> getParameters(uint8_t id, uint8_t payload0=0u, uint8_t payload1=0u, uint8_t payload2=0u);
    static QSharedPointer<Frame> setSystemValue(SLASetSystemValue_t params);
    static QSharedPointer<Frame> coordinatingReportingMode(SLACoordinateReportingMode_t params);
    static QSharedPointer<Frame> setTrackingParameters(SLASetTrackingParameters_t params);
    static QSharedPointer<Frame> stabilizationBias(SLAStabilizationBias_t params);

    virtual QString toQString();

    static const uint16_t PARAM_ID_STABILIZATION_BIAS = 0x9FU;
    static const uint16_t SYSTEM_VALUE_DEMO_MODE = 0x01U;

private:
    static const uint16_t CMD_GET_VERSION_NUMBER = 0x00U;
    static const uint16_t CMD_RESET_ALL_PARAMETERS = 0x01U;
    static const uint16_t CMD_SET_STABILIZATION_PARAMETERS = 0x02U;
    static const uint16_t CMD_GET_STABILIZATION_PARAMETERS = 0x03U;
    static const uint16_t CMD_RESET_STABILIZATION_PARAMETERS = 0x04U;
    static const uint16_t CMD_START_TRACKING = 0x08U;
    static const uint16_t CMD_STOP_TRACKING = 0x09U;
    static const uint16_t CMD_COORDINATE_REPORTING_MODE = 0x0BU;
    static const uint16_t CMD_TRACKING_POSITION = 0x43U;
    static const uint16_t CMD_SET_TRACKING_PARAMETERS = 0x0CU;
    static const uint16_t CMD_GET_PARAMETERS = 0x28U;
    static const uint16_t CMD_SET_SYSTEM_VALUE = 0x92U;
    static const uint16_t CMD_STABILIZATION_BIAS = 0x9FU;

    static uint8_t crc_sla_tab[];
    uint8_t calc_crc();
};

#endif
