// Board: LOLIN(WEMOS) D1 R2 & mini
// Blue-PIR-MQTT-Multisensor

// https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
// https://github.com/adafruit/DHT-sensor-library
// https://pubsubclient.knolleary.net/

// ----------------------------------------------
//  Hilfsvariablen / Timer
// ----------------------------------------------
unsigned long currentMillis   = 0;

// ----------------------------------------------
//  Wifi
// ----------------------------------------------
#include <ESP8266WiFi.h>
const char* ssid     = "SSID";
const char* password = "PASSWORD";
WiFiClient espClient;

// ----------------------------------------------
//  PubSub Client MQTT
// ----------------------------------------------
#include <PubSubClient.h>
const char* mqtt_server     = "mqtt.server.net";
const char* mqtt_name       = "ESP-WZMultiSensor";
const char* mqtt_user       = "user";
const char* mqtt_pass       = "pass";

#define topicTemperature  "/WZ/ESP-WZMultiSensor/Temp"
#define topicHumidity     "/WZ/ESP-WZMultiSensor/Huma"
#define topicLight        "/WZ/ESP-WZMultiSensor/Light"
#define topicMotion       "/WZ/ESP-WZMultiSensor/Motion"

char TopicBuf[30];
PubSubClient client(espClient);

// ----------------------------------------------
//  NeoPixel
// ----------------------------------------------
#include <Adafruit_NeoPixel.h>
#define neoPixelPIN D5
#define neoPixeltimer 10
unsigned long neoPixeltimerMillis = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, neoPixelPIN);
int       neoPixelModus       = 0;
uint32_t  neoPixelPriColor    = 0x1E1EF0;
byte      neoPixelbrightness  = 100;


// ----------------------------------------------
//  PIR-Motionsenor
// ----------------------------------------------
#define PIR_PIN D0
boolean PIR_STAT;

// ----------------------------------------------
//  DHT
// ----------------------------------------------
#include <DHT.h>
#define DHTPIN D2       // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
float varH      = 0;    // Luftfeuchtigkeit
float varT      = 0;    // Temperatur
float varHIC    = 0;    // Temperaturindex
#define DHTtimer 5000
unsigned long DHTtimerMillis = 0;
float DHToffset   = -6.5;

// ----------------------------------------------
// LDR - Lightsensor
// ----------------------------------------------
#define LDRPIN A0       // analog pin we're the LDR is connected
float varL      = 0;    // Helligkeit
#define Lighttimer 10000
unsigned long LighttimerMillis = 0;


// ======================================================================================================
//  Setup
// ======================================================================================================

void setup() {

  Serial.begin(115200);
  delay(1000);
  Serial.println("");
  Serial.println("Blue PIR – MQTT Bewegunsmelder");
  Serial.println("");

  NeoPixelOff();
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);

}


// ======================================================================================================
//  Loop
// ======================================================================================================

void loop() {
  currentMillis = millis();
  WIFILoop();
  MQTTLoop();

  MotionLoop();
  DHTLoop();
  LightLoop();

  NeoPixelLoop();
}
