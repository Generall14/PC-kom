#ifndef FRAMESLA_HPP
#define FRAMESLA_HPP

#include <QByteArray>
#include "../Frame.hpp"
#include "FrameTransparent.hpp"

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
}SLASetStabilizationParameters_t;

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
}SLAStabilizationBias_t;

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
    static QSharedPointer<Frame> getParameters(uint8_t id, uint8_t payload0=0u, uint8_t payload1=0u, uint8_t payload2=0u);
    static QSharedPointer<Frame> stabilizationBias(SLAStabilizationBias_t params);

    static const uint16_t PARAM_ID_STABILIZATION_BIAS = 0x9FU;

private:
    static const uint16_t CMD_GET_VERSION_NUMBER = 0x00U;
    static const uint16_t CMD_RESET_ALL_PARAMETERS = 0x01U;
    static const uint16_t CMD_SET_STABILIZATION_PARAMETERS = 0x02U;
    static const uint16_t CMD_GET_STABILIZATION_PARAMETERS = 0x03U;
    static const uint16_t CMD_RESET_STABILIZATION_PARAMETERS = 0x04U;
    static const uint16_t CMD_GET_PARAMETERS = 0x28U;
    static const uint16_t CMD_STABILIZATION_BIAS = 0x9FU;

    static uint8_t crc_sla_tab[];
    uint8_t calc_crc();
};

#endif
