//#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>
#include "sensesp/system/valueproducer.h"

namespace sensesp {

class DS18B20Temperature : public FloatProducer {
 public:
 // pin = DATA-pin (samma för alla sensorer)
  // address = unik DS18B20-adress (8 byte)
  DS18B20Temperature(uint8_t pin,
                     const DeviceAddress& address,
                     uint32_t read_delay_ms = 1000);
 private:
  OneWire one_wire_;
  DallasTemperature sensors_;
  DeviceAddress address_;
};

}  // namespace sensesp
