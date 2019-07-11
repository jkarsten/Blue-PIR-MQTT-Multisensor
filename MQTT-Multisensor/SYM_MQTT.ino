// ----------------------------------------------
//  Control Loop
// ----------------------------------------------

void MQTTLoop() {
  if (!client.connected()) reconnect_mqtt(); // MQTT Verbindung prüfen und ggf. neu Verbinden.
  client.loop();
}


// ------------------------------------------------------------------------------------------
// Reconnect WIFI und MQTT
// ------------------------------------------------------------------------------------------

void reconnect_mqtt() {
  neoPixelbrightness = 50;
  neoPixelPriColor = 0x1E001E;
  neoPixelModus = 1;
  NeoPixelOneColor();
  delay(1000);
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection ... ");
    // Attempt to connect
    if (client.connect(mqtt_name, mqtt_user, mqtt_pass)) {
      Serial.println("connected");
      //client.subscribe("/BZamp/Volume");
      //client.subscribe("/BZamp/Mute");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  neoPixelModus = 0;
  NeoPixelOff();
}
