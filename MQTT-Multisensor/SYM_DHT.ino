// ----------------------------------------------
//  Control Loop
// ----------------------------------------------
void DHTLoop() {
  if (currentMillis - DHTtimerMillis >= DHTtimer || currentMillis < DHTtimerMillis) {
    DHTtimerMillis = currentMillis;

    read_temperature();

  }
}


// ------------------------------------------------------------------------------------------
// Temperatur
// ------------------------------------------------------------------------------------------

void read_temperature() {

  const char* topicT = "Temp";
  const char* topicH = "Huma";

  float varHread   = 0;    // Luftfeuchtigkeit
  float varTread   = 0;    // Temperatur
  float varHICread = 0;    // Temperaturindex

  varHread = dht.readHumidity();
  varTread = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(varHread) || isnan(varTread) ) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    if (varH - varHread <= -0.5 || varH - varHread >= 0.5) {
      varH = varHread;
      strcpy(TopicBuf, mqtt_Pubtopic);
      strcat(TopicBuf, topicH);
      client.publish(TopicBuf, String(varH, 1).c_str());
//      Serial.print("Read Humidity from ");
//      Serial.println(varH);
    }
    if (varT - varTread <= -0.2 || varT - varTread >= 0.2) {
      varT = varTread;
      strcpy(TopicBuf, mqtt_Pubtopic);
      strcat(TopicBuf, topicT);      
      client.publish(TopicBuf, String(varT + DHToffset, 1).c_str());
//      Serial.print("Read Temperature from ");
//      Serial.println(varT + DHToffset);
    }
    varHICread = dht.computeHeatIndex(varTread, varHread, false);
    if (varHIC - varHICread <= -0.2 || varHIC - varHICread >= 0.2) {
      varHIC = varHICread;
      //      client.publish("/AEGlobe/Heatindex", String(varHIC, 1).c_str());
      //      Serial.print("Read Heatindex from ");
      //      Serial.println(varT);
    }
  }
}
