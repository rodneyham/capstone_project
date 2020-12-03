//Includes
#include "Particle.h"

// Defines
#define BAUD_RATE           9600  //bps
#define SERIAL_TIMEOUT      500 //ms
#define BUFFER_SIZE         60 //bytes

// Typedefs
typedef void (*UpdateFunction)(const float pm25_avg, const float pm10_avg);

class AirParticleSensor {

public:
  AirParticleSensor(UpdateFunction _updateCallback);

  void
    begin(),
    handle();


private:
  void
    listen(),
    update();

  float
    scaleRawValue(byte _low_byte, byte _high_byte);

  int
    sample_number;

  unsigned long
    serial_listen_timer,
    refresh_timer;

  float
    pm25_buffer[BUFFER_SIZE], // buffer to hold PM2.5 samples before pushing to caller
    pm10_buffer[BUFFER_SIZE]; // buffer to hold PM10 samples before pushing to caller

  UpdateFunction updateCallback;
};
