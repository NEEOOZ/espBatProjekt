//#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>

#include "sensesp/system/valueproducer.h"

namespace sensesp {

class DS18B20Temperature : public FloatProducer {
 public:
  DS18B20Temperature(uint8_t pin, uint32_t read_delay_ms = 1000);

 private:
  OneWire one_wire_;
  DallasTemperature sensors_;
};

}  // namespace sensesp
