// Includes
#include "AirParticleSensor.h"


AirParticleSensor::AirParticleSensor(UpdateFunction _updateCallback) {
  updateCallback = _updateCallback;
}

void AirParticleSensor::begin() {
  Serial1.begin(BAUD_RATE);
  Serial1.setTimeout(SERIAL_TIMEOUT);

  sample_number = 0;

  // Reset timers
  serial_listen_timer = millis();
}

void AirParticleSensor::handle() {

  listen();

  update();

}

void AirParticleSensor::listen() {

  // check if serial has data
  if (!Serial1.available()) {
    return;
  }

  // read serial port into buffer
  // break if we haven't totally filled the buffer
  byte sensor_buffer[11];
  if (!Serial1.readBytes((char*)sensor_buffer, 11)) {
    return;
  }

  // check crc
  byte crc = 0;
  for (int i = 2; i < 8; i++) {
    crc += sensor_buffer[i];
  }

  // return if calculated crc doesn't match client's crc
  if (crc != sensor_buffer[8]) {
    return;
  }

  // increment sample number for each successful query
  pm25_buffer[sample_number] = scaleRawValue(sensor_buffer[2], sensor_buffer[3]);
  pm10_buffer[sample_number] = scaleRawValue(sensor_buffer[4], sensor_buffer[5]);
  sample_number++;

}

void AirParticleSensor::update() {

  // only call update when buffer is full
  if (sample_number < BUFFER_SIZE) {
    return;
  }

  // average samples
  int counter = 0;
  float pm25_sum = 0;
  float pm10_sum = 0;
  for (int index = 0; index < BUFFER_SIZE; index++) {
    pm25_sum += pm25_buffer[index];
    pm10_sum += pm10_buffer[index];
  }

  float pm25_avg = pm25_sum / BUFFER_SIZE;
  float pm10_avg = pm10_sum / BUFFER_SIZE;

  // call callback function
  updateCallback(pm25_avg, pm10_avg);

  // reset sample number
  sample_number = 0;
}

float AirParticleSensor::scaleRawValue(byte _low_byte, byte _high_byte) {
  return ((float) (_high_byte * 256) + _low_byte) / 10;
}
