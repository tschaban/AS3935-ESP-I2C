#ifndef AS3935_h
#define AS3935_h
#include "Arduino.h"

#ifdef DEBUG
#include <Streaming.h>
#endif

static const uint8_t AS3935_INT_STRIKE = 0x08;
static const uint8_t AS3935_INT_DISTURBER = 0x04;
static const uint8_t AS3935_INT_NOISE = 0x01;
static const int8_t AS3935_DISTANCE_OUT_OF_RANGE = -2;
static const uint8_t AS3935_AFE_INDOOR = 0b10010;
static const uint8_t AS3935_AFE_OUTDOOR = 0b01110;

enum AS3935_REGISTER_MASKS {

  WIPE_ALL = 0x0,
  INTERUPTION_MASK = 0xF, //
  ENERGY_MASK = 0xF,
  TUNING_CAPACITOR_MASK = 0xF, //
  SPI_READ_M = 0x40,
  CALIB_MASK = 0x40,
  OSC_MASK = 0x1F,
  DISPLAY_SRCO = 0x20,
  DISTANCE_MASK = 0x3F, //
  DIV_MASK = 0x3F,
  NOISE_FLOOR_MASK = 0x8F,
  AFE_GAIN_MASK = 0xC1, //
  STATISTICS_MASK = 0xBF,
  DISTURB_MASK = 0xDF,
  MINIMUM_LIGHTNING_MASK = 0xCF,
  SPIKE_MASK = 0xF0,
  THRESH_MASK = 0xF0,
  CAP_MASK = 0xF0,
  POWER_MASK = 0xFE

};

enum AS3935_AFE_GAIN { INDOOR = 0x12, OUTDOOR = 0xE };

class AS3935SENSOR {
public:
  AS3935SENSOR();
  ~AS3935SENSOR(void);
  void begin(int sda, int scl, uint8_t address, uint8_t interruptPin);
  uint8_t readRegister(uint8_t reg);
  uint8_t readRegisterWithMask(uint8_t reg, uint8_t mask);
  uint8_t readRegisterWithMask(uint8_t reg, uint8_t mask, uint8_t bit);
  void writeRegisterWithMask(uint8_t reg, uint8_t mask, uint8_t value);
  void writeRegister(uint8_t reg, uint8_t value);
  void setDefault(void);
  void calibrateRCO(void);
  void disableOscillators(void);
  uint8_t getIntrruptReason(void);
  int8_t getDistance(void);
  bool isIndoor(void);
  bool isOutdoor(void);
  bool setIndoor(bool enable);
  uint8_t getMinimumLightning(void);
  bool setMinimumLightning(uint8_t);
  void clearStats(void);
  uint8_t getNoiseFloor(void);
  bool setNoiseFloor(int level);
  uint8_t increaseNoiseFloor(void);
  uint8_t descreseNoiseFloor(void);
  uint8_t setTuningCapacitor(uint8_t);
  void calibrate(uint8_t);

private:
  uint8_t _address;
  uint8_t _interruptPin;
  const uint8_t _defaultSDA = SDA; // D4
  const uint8_t _defaultSCL = SCL; // D5
  uint8_t _getShift(uint8_t mask);
};

#endif
