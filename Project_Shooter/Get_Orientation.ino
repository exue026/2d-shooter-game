#include <Wire.h>

void WireRequestArray(int address, uint32_t* buffer, uint8_t amount);
void WireWriteRegister(int address, uint8_t reg, uint8_t value);
void WireWriteByte(int address, uint8_t value);

static int const  sensitivity = 7;
static float const    SensorMaximumReading = 512.0;
static float const    SensorMaximumAccel  = 9.81 * 4.0;
static uint8_t const  SensorAccelerometer = 0x1D;

bool trigSPState = 0;
float trigYOrien = 0;
float x, y, z = 0;

static bool isLower(float a, float b) {
  //only true when a is lower than b and within -20 (half a cirle)
  //with possibility of a crossing vertical (positive 10)
  float lowerBound = b - 20;
  if (lowerBound <= -30)
    lowerBound += 40;
  if (b <= -10) {
    if (a >= lowerBound && a <= 10)
      a -= 40;
    if (a <= b)
      return 1;
    else
      return 0;
  }
  if (a <= b)
    return 1;
  else
    return 0;

}

void OrienInit()
{
  WireWriteRegister(SensorAccelerometer, 0x31, 1);
  WireWriteRegister(SensorAccelerometer, 0x2D, 1 << 3);
}

void OrienTick()
{
  size_t const DataLength = 6;
  uint32_t data[DataLength] = { 0 };

  WireWriteByte(SensorAccelerometer, 0x32);
  WireRequestArray(SensorAccelerometer, data, DataLength);

  uint16_t xi = (data[1] << 8) | data[0];
  uint16_t yi = (data[3] << 8) | data[2];
  uint16_t zi = (data[5] << 8) | data[4];
  x = *(int16_t*)(&xi) / SensorMaximumReading * SensorMaximumAccel;
  y = *(int16_t*)(&yi) / SensorMaximumReading * SensorMaximumAccel;
  z = *(int16_t*)(&zi) / SensorMaximumReading * SensorMaximumAccel;

  //modifies rawY to a range from 10 to -30
  if (z < 0)
    y = -20 - y;
  bool previousSPTrigState = trigSPState;
  trigSPState = isLower(y, trigYOrien);
  gameController.setSPTrig(!previousSPTrigState && trigSPState);
}


void Calib() {
  trigYOrien = (y - sensitivity <= -30) ? y - sensitivity + 40 : y - sensitivity;
}
