// ----------------------------------------------
//  Control Loop
// ----------------------------------------------
void LightLoop() {
  if (currentMillis - LighttimerMillis >= Lighttimer || currentMillis < LighttimerMillis) {
    LighttimerMillis = currentMillis;

    read_Light();

  }
}

// ------------------------------------------------------------------------------------------
// Helligkeit auslesen
// ------------------------------------------------------------------------------------------

void read_Light() {

  int varLread = analogRead(A0);   // read the input on analog pin 0
  if (varL - varLread <= -20 || varL - varLread >= 20) {
    varL = varLread;
    client.publish(topicLight, String(varL, 1).c_str());
    //    Serial.print("Helligkeit ");
    //    Serial.println(varL);
  }
}
