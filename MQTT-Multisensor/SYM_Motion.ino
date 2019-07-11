// ----------------------------------------------
//  Control Loop
// ----------------------------------------------
void MotionLoop() {
  const char* topic = "Motion";
  strcpy(TopicBuf,mqtt_Pubtopic);
  strcat(TopicBuf,topic);
  
  if (digitalRead(PIR_PIN) == LOW) //low = no motion, high = motion
  {
    if (PIR_STAT == true)
    {
      PIR_STAT = false;
      Serial.println("No motion");
      neoPixelModus = 0;
      
      client.publish(TopicBuf, "OFF");
    }
  }
  else
  {
    if (PIR_STAT == false)
    {
      PIR_STAT = true;
      Serial.println("Motion detected  ALARM");
      neoPixelPriColor    = 0x1E1EF0;
      neoPixelbrightness  = 5;
      neoPixelModus = 1;
      client.publish(TopicBuf, "ON");
    }
  }

}
