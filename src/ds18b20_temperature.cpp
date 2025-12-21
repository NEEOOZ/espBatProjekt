#include "ds18b20_temperature.h"

#include <cstring>        // memcpy
#include "sensesp.h"      // event_loop()

namespace sensesp {

DS18B20Temperature::DS18B20Temperature(uint8_t pin,
                                       const DeviceAddress& address,
                                       uint32_t read_delay_ms)
    : one_wire_(pin), sensors_(&one_wire_) {
  // spara adressen lokalt
  memcpy(address_, address, 8);

  sensors_.begin();

  event_loop()->onRepeat(read_delay_ms, [this]() {
    sensors_.requestTemperatures();
    float c = sensors_.getTempC(address_);
    emit(c);
  });
}

}  // namespace sensesp
