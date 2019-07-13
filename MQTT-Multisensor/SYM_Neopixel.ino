// ----------------------------------------------
//  Control Loop
// ----------------------------------------------

void NeoPixelLoop() {

  if (currentMillis - neoPixeltimerMillis >= neoPixeltimer || currentMillis < neoPixeltimerMillis) {
    neoPixeltimerMillis = currentMillis;
    if (neoPixelModus == 1) {
      NeoPixelOneColor();
    }
    else if (neoPixelModus == 2) {
      NeoPixelFade();
    }
    else if (neoPixelModus == 3) {
      NeoPixelCircleDot();
    }
    else {
      NeoPixelOff();
    }
  } // if (currentMillis - neoPixeltimerMillis >= neoPixeltimer || currentMillis < neoPixeltimerMillis)
} // void NeoPixelLoop()

// ----------------------------------------------
//  Off
// ----------------------------------------------

void NeoPixelOff() {
  pixels.begin();
  pixels.setBrightness(neoPixelbrightness);
  for (int i = 0; i <= 15; i++) {
    pixels.setPixelColor(i, 0x000000);
  }
  pixels.show();
}

// ----------------------------------------------
//  One Color
// ----------------------------------------------

void NeoPixelOneColor() {
  pixels.begin();
  pixels.setBrightness(neoPixelbrightness);
  for (int i = 0; i <= 15; i++) {
    pixels.setPixelColor(i, neoPixelPriColor);
  }
  pixels.show();
} // void NeoPixelOneColor() {

// ----------------------------------------------
//  Fade one color
// ----------------------------------------------

void NeoPixelFade() {

  static byte FadeBrightness = 0;
  static boolean FadeUp;

  if (neoPixelbrightness >= 20) {
    if (FadeBrightness == 0 || FadeBrightness > neoPixelbrightness) {
      FadeBrightness = neoPixelbrightness;
      FadeUp = false;
    }
    else if (FadeBrightness == 10) {
      FadeUp = true;
    }

    if ( FadeUp == true) FadeBrightness++;
    else FadeBrightness--;

    pixels.begin();
    pixels.setBrightness(FadeBrightness);
    for (int i = 0; i <= 15; i++) {
      pixels.setPixelColor(i, neoPixelPriColor);
    }
    pixels.show();

  } // if (neoPixelbrightness >= 20) {

} // void NeoPixelFade() {

// ----------------------------------------------
//  Circle one dot one Color
// ----------------------------------------------

void NeoPixelCircleDot() {

  static byte DotPosition = 255;
  static byte DotDelay = 0;

  DotDelay++;
  if (DotDelay == 6) DotDelay = 0;
  if (DotDelay == 0) {
    if (DotPosition == 255 || DotPosition == 15) {
      DotPosition = 0;
    }
    else {
      DotPosition++;
    }

    pixels.begin();
    pixels.setBrightness(neoPixelbrightness);
    if (DotPosition == 0) pixels.setPixelColor(15, 0x000000);
    else pixels.setPixelColor(DotPosition - 1, 0x000000);
    pixels.setPixelColor(DotPosition, neoPixelPriColor);
    pixels.show();

  }

}
