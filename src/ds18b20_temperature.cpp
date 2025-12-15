#include "ds18b20_temperature.h"
#include "sensesp.h"   // för event_loop()

namespace sensesp {

DS18B20Temperature::DS18B20Temperature(uint8_t pin, uint32_t read_delay_ms)
    : one_wire_(pin), sensors_(&one_wire_) {
  sensors_.begin();

  event_loop()->onRepeat(read_delay_ms, [this]() {     // <-- BYT HIT
    sensors_.requestTemperatures();
    float c = sensors_.getTempCByIndex(0);
    this->emit(c);
  });
}

}  // namespace sensesp
