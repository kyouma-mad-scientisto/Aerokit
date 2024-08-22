SCD30 airSensor;

static uint32_t sensorReadTime = 0;
const uint32_t sensorReadTimeout = 500;

void sensorDatenAuswerten() {
  if(int16_t(airSensor.getCO2() - startCO2Wert) >= 1550) {setLEDColor(255,0,0); ampelFarbe = ampelRot;}
    else {if(int16_t(airSensor.getCO2() - startCO2Wert) >= 1050) {setLEDColor(255,63,0); ampelFarbe = ampelGelb;}
            else {if(int16_t(airSensor.getCO2() - startCO2Wert) >= 550) {setLEDColor(255,255,0); ampelFarbe = ampelOliv;}
                    else {if(int16_t(airSensor.getCO2() - startCO2Wert) < 350) {setLEDColor(0,255,0); ampelFarbe = ampelGruen;}}
            }
    }
}
void sensorSetup() {
  Wire1.begin(sensorSDA, sensorSCL);
  if (airSensor.begin(Wire1) == false)
  {
    Serial.println("Air sensor not detected. Please check wiring.");
  }
}
void sensorReadLoop() {
  if((millis() - sensorReadTime) >= sensorReadTimeout) {
    sensorReadTime = millis();
    if (airSensor.dataAvailable())
    {
      co2Gehalt = airSensor.getCO2();
      Serial.print("CO2(ppm):");
      Serial.print(airSensor.getCO2());

      temperatur = airSensor.getTemperature();
      Serial.print(" Temperatur(C):");
      Serial.print(airSensor.getTemperature(), 1);

      luftfeuchte = airSensor.getHumidity();
      Serial.print(" Feuchte(%):");
      Serial.print(airSensor.getHumidity(), 1);
  
      Serial.println();
      sensorDatenAuswerten();
      displaySensorData();
    }
    else {/*Serial.println("Waiting for new data");*/}  
  }
}

void setupDisplay() {
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Hallo!");
  Heltec.display->display();
}
void displaySensorData() {
      Heltec.display->clear();
      
      String co2 = "CO2(ppm): ";
      co2 += airSensor.getCO2();
      Heltec.display->drawString(0, 0, co2);
      
      String tempC = "Temperatur(°C): ";
      tempC += airSensor.getTemperature();
      Heltec.display->drawString(0, 10, tempC);
      
      String humidity = "Feuchtigkeit(%): ";
      humidity += airSensor.getHumidity();
      Heltec.display->drawString(0, 20, humidity);
      
      Heltec.display->display();
}

void setupAmpel() {
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);

  ledcAttachPin(pinRot, 0);
  ledcAttachPin(pinGruen, 1);
  ledcAttachPin(pinBlau, 2);

  ledcWrite(0, 0);
  ledcWrite(1, 255);
  ledcWrite(2, 0);
}
void setLEDColor(uint8_t red, uint8_t green, uint8_t blue) {
  ledcWrite(0, red);
  ledcWrite(1, green);
  ledcWrite(2, blue);
}
