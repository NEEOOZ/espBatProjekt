// Signal K application template file.
//
// This application demonstrates core SensESP concepts in a very
// concise manner. You can build and upload the application as is
// and observe the value changes on the serial port monitor.
//
// You can use this source file as a basis for your own projects.
// Remove the parts that are not relevant to you, and add your own code
// for external hardware libraries.

#include <memory>

#include "sensesp.h"
#include "sensesp/sensors/analog_input.h"
#include "sensesp/sensors/digital_input.h"
#include "sensesp/sensors/sensor.h"
#include "sensesp/signalk/signalk_output.h"
#include "sensesp/system/lambda_consumer.h"
#include "sensesp_app_builder.h"
#include "ds18b20_temperature.h"
#include <OneWire.h>
#include <DallasTemperature.h>

using namespace sensesp;

// The setup function performs one-time application initialization.
DeviceAddress addr_engine_sb   = {0x28, 0xFF, 0x64, 0x1F, 0x5B, 0xC8, 0x39, 0xBE};
DeviceAddress addr_engine_bb   = {0x28, 0xFF, 0x64, 0x1F, 0x5B, 0xCC, 0x1B, 0x1A};
DeviceAddress addr_engine_room = {0x28, 0xFF, 0x64, 0x1F, 0x5B, 0xAA, 0xC8, 0x5F};


void setup() {
  SetupLogging(ESP_LOG_DEBUG);
  // Construct the global SensESPApp() object
  SensESPAppBuilder builder;
  sensesp_app = (&builder)
                    // Set a custom hostname for the app.
                    ->set_hostname("mitt-sensesp-projekt-251219")
                    // Optionally, hard-code the WiFi and Signal K server
                    // settings. This is normally not needed.
                    //->set_wifi_client("My WiFi SSID", "my_wifi_password")
                    //->set_wifi_access_point("My AP SSID", "my_ap_password")
                    //->set_sk_server("10.0.0.5", 3000)
                    ->get_app();


  // ===== DS18B20 SCAN START =====
 
debugD("=== NICKLAS TEST BUILD 251221-19:50 ===");
const uint8_t kTempDataPin = 4;

auto temp_engine_sb = std::make_shared<sensesp::DS18B20Temperature>(
    kTempDataPin, addr_engine_sb, 1000);

auto temp_engine_bb = std::make_shared<sensesp::DS18B20Temperature>(
    kTempDataPin, addr_engine_bb, 1000);

auto temp_engine_room = std::make_shared<sensesp::DS18B20Temperature>(
    kTempDataPin, addr_engine_room, 1000);


    temp_engine_sb->connect_to(new sensesp::SKOutputFloat(
    "environment.engine.sb.temperature", "C"));

    temp_engine_bb->connect_to(new sensesp::SKOutputFloat(
    "environment.engine.bb.temperature", "C"));

    temp_engine_room->connect_to(new sensesp::SKOutputFloat(
    "environment.engineRoom.temperature", "C"));

    temp_engine_sb->attach([temp_engine_sb](){
  //debugD("temp_engine_sb: %f C", temp_engine_sb->get());
});

temp_engine_bb->attach([temp_engine_bb](){
  //debugD("temp_engine_bb: %f C", temp_engine_bb->get());
});

temp_engine_room->attach([temp_engine_room](){
  //debugD("temp_engine_room: %f C", temp_engine_room->get());
});


}




void loop() {
  event_loop()->tick();
}
