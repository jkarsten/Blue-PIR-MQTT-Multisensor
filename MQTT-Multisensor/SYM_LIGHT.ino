// ----------------------------------------------
//  Control Loop
// ----------------------------------------------
void LightLoop() {
    if (currentMillis - LighttimerMillis >= Lighttimer || currentMillis < LighttimerMillis) {
    LighttimerMillis = currentMillis;
    
    read_Light();

  }
}


void read_Light() {

  const char* topic = "Light";
  strcpy(TopicBuf,mqtt_Pubtopic);
  strcat(TopicBuf,topic);
  
  int varLread = analogRead(A0);   // read the input on analog pin 0
  if (varL - varLread <= -20 || varL - varLread >= 20) {
    varL = varLread;
    client.publish(TopicBuf, String(varL, 1).c_str());
//    Serial.print("Helligkeit ");
//    Serial.println(varL);
  }
}
