// ----------------------------------------------
//  Control Loop
// ----------------------------------------------

void WIFILoop() {
  if (WiFi.status() != WL_CONNECTED) setup_wifi(); // Verbindung zum Netzwerk testen ... ggf. Wifi neu initialisieren.
}


// ------------------------------------------------------------------------------------------
// WIFI Setup
// ------------------------------------------------------------------------------------------

void setup_wifi() {
  delay(500);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  neoPixelbrightness = 200;
  neoPixelPriColor = 0x001E00;
  neoPixelModus = 3;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    currentMillis = millis();
    NeoPixelLoop();
    delay(10);
  }

  Serial.println("");
  Serial.println("WiFi is connected. IP address is: ");
  Serial.println(WiFi.localIP());
  neoPixelPriColor = 0x001E00;
  neoPixelModus = 2;
  for (int i = 0; i <= 300; i++) {
    currentMillis = millis();
    NeoPixelLoop();
    delay(10);
  }
  neoPixelModus = 0;
  NeoPixelOff();
}
