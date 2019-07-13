// ----------------------------------------------
//  Control Loop
// ----------------------------------------------
void MotionLoop() {

  if (digitalRead(PIR_PIN) == LOW) //low = no motion, high = motion
  {
    if (PIR_STAT == true)
    {
      PIR_STAT = false;
      //      Serial.println("No motion");
      client.publish(topicMotion, "OFF");
    }
    neoPixelModus = 0;
  }
  else
  {
    if (PIR_STAT == false)
    {
      PIR_STAT = true;
      //      Serial.println("Motion detected  ALARM");
      client.publish(topicMotion, "ON");
    }
    neoPixelPriColor    = 0x1E1EF0;
    neoPixelbrightness  = 5;
    neoPixelModus = 1;
  }

}
