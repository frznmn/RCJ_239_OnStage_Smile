#include <Adafruit_GFX.h>
#include <FastLED_NeoMatrix.h>
#include <FastLED.h>

#ifndef ESP32
#define delay FastLED.delay
#endif

#if defined(ESP32) or defined(ESP8266)
#define PIN 12 // GPIO5 = D1
#else
#define PIN 8
#endif

static const uint8_t PROGMEM
    mono_bmp[][8] =
    {
  {   // 0: checkered 1
      B10101010,
      B01010101,
      B10101010,
      B01010101,
      B10101010,
      B01010101,
      B10101010,
      B01010101,
      },

  {   // 1: checkered 2
      B01010101,
      B10101010,
      B01010101,
      B10101010,
      B01010101,
      B10101010,
      B01010101,
      B10101010,
      },

  {   // 2: smiley
      B00111100,
      B01000010,
      B10100101,
      B10000001,
      B10100101,
      B10011001,
      B01000010,
      B00111100 },

  {   // 3: neutral
      B00111100,
      B01000010,
      B10100101,
      B10000001,
      B10111101,
      B10000001,
      B01000010,
      B00111100 },

  {   // 4; frowny
      B00111100,
      B01000010,
      B10100101,
      B10000001,
      B10011001,
      B10100101,
      B01000010,
      B00111100 },
    };

void count_pixels() {
    matrix->clear();
    for (uint16_t i=0; i<mh; i++) {
  for (uint16_t j=0; j<mw; j++) {
      matrix->drawPixel(j, i, i%3==0?(uint16_t)LED_BLUE_HIGH:i%3==1?(uint16_t)LED_RED_HIGH:(uint16_t)LED_GREEN_HIGH);
      // depending on the matrix size, it's too slow to display each pixel, so
      // make the scan init faster. This will however be too fast on a small matrix.
      #ifdef ESP8266
      if (!(j%3)) matrix->show();
      yield(); // reset watchdog timer
      #elif ESP32
      delay(1);
      matrix->show();
      #else 
      matrix->show();
      #endif
  }
    }
}

// Fill the screen with multiple levels of white to gauge the quality
void display_four_white() {
    matrix->clear();
    matrix->fillRect(0,0, mw,mh, LED_WHITE_HIGH);
    matrix->drawRect(1,1, mw-2,mh-2, LED_WHITE_MEDIUM);
    matrix->drawRect(2,2, mw-4,mh-4, LED_WHITE_LOW);
    matrix->drawRect(3,3, mw-6,mh-6, LED_WHITE_VERYLOW);
    matrix->show();
}

void display_bitmap(uint8_t bmp_num, uint16_t color) { 
    static uint16_t bmx,bmy;

    // Clear the space under the bitmap that will be drawn as
    // drawing a single color pixmap does not write over pixels
    // that are nul, and leaves the data that was underneath
    matrix->fillRect(bmx,bmy, bmx+8,bmy+8, LED_BLACK);
    matrix->drawBitmap(bmx, bmy, mono_bmp[bmp_num], 8, 8, color);
    bmx += 8;
    if (bmx >= mw) bmx = 0;
    if (!bmx) bmy += 8;
    if (bmy >= mh) bmy = 0;
    matrix->show();
}

void display_rgbBitmap(uint8_t bmp_num) { 
    static uint16_t bmx,bmy;

    fixdrawRGBBitmap(bmx, bmy, RGB_bmp[bmp_num], 8, 8);
    bmx += 8;
    if (bmx >= mw) bmx = 0;
    if (!bmx) bmy += 8;
    if (bmy >= mh) bmy = 0;
    matrix->show();
}

void display_lines() {
    matrix->clear();

    // 4 levels of crossing red lines.
    matrix->drawLine(0,mh/2-2, mw-1,2, LED_RED_VERYLOW);
    matrix->drawLine(0,mh/2-1, mw-1,3, LED_RED_LOW);
    matrix->drawLine(0,mh/2,   mw-1,mh/2, LED_RED_MEDIUM);
    matrix->drawLine(0,mh/2+1, mw-1,mh/2+1, LED_RED_HIGH);

    // 4 levels of crossing green lines.
    matrix->drawLine(mw/2-2, 0, mw/2-2, mh-1, LED_GREEN_VERYLOW);
    matrix->drawLine(mw/2-1, 0, mw/2-1, mh-1, LED_GREEN_LOW);
    matrix->drawLine(mw/2+0, 0, mw/2+0, mh-1, LED_GREEN_MEDIUM);
    matrix->drawLine(mw/2+1, 0, mw/2+1, mh-1, LED_GREEN_HIGH);

    // Diagonal blue line.
    matrix->drawLine(0,0, mw-1,mh-1, LED_BLUE_HIGH);
    matrix->drawLine(0,mh-1, mw-1,0, LED_ORANGE_MEDIUM);
    matrix->show();
}

void display_boxes() {
    matrix->clear();
    matrix->drawRect(0,0, mw,mh, LED_BLUE_HIGH);
    matrix->drawRect(1,1, mw-2,mh-2, LED_GREEN_MEDIUM);
    matrix->fillRect(2,2, mw-4,mh-4, LED_RED_HIGH);
    matrix->fillRect(3,3, mw-6,mh-6, LED_ORANGE_MEDIUM);
    matrix->show();
}

void display_circles() {
    matrix->clear();
    matrix->drawCircle(mw/2,mh/2, 2, LED_RED_MEDIUM);
    matrix->drawCircle(mw/2-1-min(mw,mh)/8, mh/2-1-min(mw,mh)/8, min(mw,mh)/4, LED_BLUE_HIGH);
    matrix->drawCircle(mw/2+1+min(mw,mh)/8, mh/2+1+min(mw,mh)/8, min(mw,mh)/4-1, LED_ORANGE_MEDIUM);
    matrix->drawCircle(1,mh-2, 1, LED_GREEN_LOW);
    matrix->drawCircle(mw-2,1, 1, LED_GREEN_HIGH);
    if (min(mw,mh)>12) matrix->drawCircle(mw/2-1, mh/2-1, min(mh/2-1,mw/2-1), LED_CYAN_HIGH);
    matrix->show();
}

/*void display_scrollText() {
    uint8_t size = max(int(mw/8), 1);
  //  matrix->clear();
    matrix->setTextWrap(false);  // we don't wrap text so it scrolls nicely
    matrix->setTextSize(1);
    matrix->setRotation(0);
    for (int8_t x=7; x>=-42; x--) {
  yield();
  matrix->clear();
  matrix->setCursor(x,0);
  matrix->setTextColor(LED_GREEN_HIGH);
  matrix->print("Hello");
  if (mh>11) {
      matrix->setCursor(-20-x,mh-7);
      matrix->setTextColor(LED_ORANGE_HIGH);
      matrix->print("World");
  }
  matrix->show();
       delay(50);
    }

    matrix->setRotation(3);
    matrix->setTextSize(size);
    matrix->setTextColor(LED_BLUE_HIGH);
    for (int16_t x=8*size; x>=-6*8*size; x--) {
  yield();
  matrix->clear();
  matrix->setCursor(x,mw/2-size*4);
  matrix->print("Rotate");
  matrix->show();
  delay(50/size);
    }
    matrix->setRotation(0);
    matrix->setCursor(0,0);
    matrix->show();
}
}
*/
void loop() {
#if 0
    // 200 displays in 13 seconds = 15 frames per second for 4096 pixels
    for (uint8_t i=0; i<100; i++) { 
  matrix->fillScreen(LED_BLUE_LOW);
  matrix->show();
  matrix->fillScreen(LED_RED_LOW);
  matrix->show();
    }
#endif

#ifdef BM32
    Serial.println("bounce 32 bitmap");
    display_panOrBounceBitmap(32);
#endif
    // pan a big pixmap
    Serial.println("pan/bounce 24 bitmap");
    display_panOrBounceBitmap(24);
    // bounce around a small one
    Serial.println("pan/bounce 8 bitmap");
    display_panOrBounceBitmap(8);//взять
}

void setup() {
    // Time for serial port to work?
    matrix->begin();
    matrix->setTextWrap(false);
    matrix->setBrightness(BRIGHTNESS);
#ifndef DISABLE_WHITE
    matrix->fillScreen(LED_WHITE_HIGH);
    matrix->show();
    delay(3000);
    matrix->clear();
#endif
}
