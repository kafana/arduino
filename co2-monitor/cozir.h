//
//    FILE: Cozir.h
//  AUTHOR: DirtGambit & Rob Tillaart
// VERSION: 0.1.06
// PURPOSE: library for COZIR range of sensors for Arduino
//          Polling Mode
//     URL: http://forum.arduino.cc/index.php?topic=91467.0
//
// READ DATASHEET BEFORE USE OF THIS LIB !
//
// Released to the public domain
//

#ifndef Cozir_h
#define Cozir_h

#include "Arduino.h"
#include "SoftwareSerial.h"

#define COZIR_LIB_VERSION "0.1.07"

// OUTPUTFIELDS
// See datasheet for details.
// These defines can be OR-ed for the SetOutputFields command
#define CZR_LIGHT 			0x2000
#define CZR_HUMIDITY		0x1000
#define CZR_FILTLED			0x0800
#define CZR_RAWLED			0x0400
#define CZR_MAXLED			0x0200
#define CZR_ZEROPOINT		0x0100
#define CZR_RAWTEMP			0x0080
#define CZR_FILTTEMP		0x0040
#define CZR_FILTLEDSIGNAL	0x0020
#define CZR_RAWLEDSIGNAL	0x0010
#define CZR_SENSTEMP		0x0008
#define CZR_FILTCO2			0x0004
#define CZR_RAWCO2			0x0002
#define CZR_NONE			0x0001

// easy default setting for streaming
#define CZR_HTC			(CZR_HUMIDITY | CZR_RAWTEMP | CZR_RAWCO2)
// not in datasheet for debug only
#define CZR_ALL				0x3FFE

// OPERATING MODES
#define CZR_COMMAND			0x00
#define CZR_STREAMING		0x01
#define CZR_POLLING			0x02


class COZIR
{
public:
    COZIR(Stream*);
    void init();

    float Celsius();
    float Fahrenheit();
    float Humidity();
    float Light();
    uint32_t CO2();

    void ReadAll();
    float ra_Celsius();
    float ra_Fahrenheit();
    float ra_Humidity();
    uint32_t ra_CO2();

    uint16_t FineTuneZeroPoint(uint16_t , uint16_t);
    uint16_t CalibrateFreshAir();
    uint16_t CalibrateNitrogen();
    uint16_t CalibrateKnownGas(uint16_t );
    uint16_t CalibrateManual(uint16_t );
    uint16_t SetSpanCalibrate(uint16_t );
    uint16_t GetSpanCalibrate();

    void SetDigiFilter(uint8_t );
    uint8_t GetDigiFilter();

    void SetOutputFields(uint16_t );
    void GetRecentFields();

    void SetEEPROM(uint8_t , uint8_t );
    uint8_t GetEEPROM(uint8_t );

    void GetVersionSerial();
    void GetConfiguration();

private:
    Stream *ser;
    char buffer[30];
    float ra_temperature = 0.0;
    float ra_humidity = 0.0;
    uint32_t ra_co2 = 0.0;

    void SetOperatingMode(uint8_t mode);
    void Command(const char* );
    uint32_t Request(const char* );
};

#endif
// -- END OF FILE --
