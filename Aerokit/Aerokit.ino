#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include "SparkFun_SCD30_Arduino_Library.h"
#include "heltec.h"
//LoRa
#include <SPI.h>
#include <Speck.h>

#define serielleBaudrate 500000

#define pinRot    17
#define pinGruen  12
#define pinBlau   13

#define sensorSDA 21
#define sensorSCL 22

#define IDA1 350    //gruen
#define IDA2 550    //gruen/gelb
#define IDA3 1050   //gelb
#define IDA4 1550   //rot

#define ampelGruen 0x70ad47
#define ampelOliv 0xa8d08d
#define ampelGelb 0xffff00
#define ampelRot 0xff0000

uint32_t ampelFarbe = ampelGruen;

uint16_t startCO2Wert = 1900;
//Nummer des Klassenraumes der ueberwacht wird
uint16_t roomNumber = 303;

static uint16_t co2Gehalt = 0;
static float luftfeuchte = 0;
static float temperatur = 0;

void setup() {
  Serial.begin(seriellBaudrate);
  Heltec.begin(true /*DisplayEnable Enable*/, true /*LoRa Enable*/, false /*Serial Enable*/, true, 868E6);
  sensorSetup();
  setupWebServer();
  setupDisplay();
  setupAmpel();
  setLEDColor(0,0,0);
  setupLoRa();
}

void loop() {
  sensorReadLoop();
  webServerWork();
  receivePacket();
}
