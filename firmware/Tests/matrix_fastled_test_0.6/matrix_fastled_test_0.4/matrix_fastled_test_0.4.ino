
#include <Adafruit_GFX.h>
#include <FastLED_NeoMatrix.h>
#include <FastLED.h>
#include "colors.h" //цвета 
int myTimer2 = millis();
//подключение массивов картинок
#include "SMILE.h"
#include "dvizh.h"
#include "SAD.h"
#include "angry.h"
#include "default.h"
#include "UDIVLENIE.h"

#define PIN 9 //matrix connection pin 
#define mw 16 // ширина
#define mh 8 // высота
#define NUMMATRIX (mw*mh) //количество светодиодов в матрице
// Max is 255, 32 is a conservative value to not overload
// a USB power supply (500mA) for 12x12 pixels.
#define BRIGHTNESS 16 //яркость
#define DISABLE_WHITE //для заполнения белым при старте - закомментировать
//дла выключения - закомментировать
CRGB leds[NUMMATRIX];
// Define matrix width and height.
FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(leds, mw, mh,
    NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);

void setup() {
  // Time for serial port to work?
  delay(1000);
  Serial.begin(9600);
  Serial.print("Init on pin: ");
  Serial.println(PIN);
  Serial.print("Matrix Size: ");
  Serial.print(mw);
  Serial.print(" ");
  Serial.print(mh);
  Serial.print(" ");
  Serial.println(NUMMATRIX);

  Serial1.begin(9600);

  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUMMATRIX  ).setCorrection(TypicalLEDStrip);


  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setBrightness(BRIGHTNESS);
  Serial.println("If the code crashes here, decrease the brightness or turn off the all white display below");
  // Test full bright of all LEDs. If brightness is too high
  // for your current limit (i.e. USB), decrease it.
  //#define DISABLE_WHITE
#ifndef DISABLE_WHITE
  matrix->fillScreen(LED_WHITE_HIGH);
  matrix->show();
  delay(100);
  matrix->clear();
#endif
}

int condition = 0;
uint32_t myTimer1 = millis();

void loop() {
  // clear the screen after X bitmaps have been displayed and we
  // loop back to the top left corner
  // 8x8 => 1, 16x8 => 2, 17x9 => 6
  static uint8_t pixmap_count = ((mw + 7) / 8) * ((mh + 7) / 8);

  int bmx = 0, bmy = 0;
  matrix->fillRect(bmx, bmy, bmx + 16, bmy + 8, LED_BLACK); //очистка матрицы
  //matrix->drawBitmap();
  /*!
    @brief   Draw a PROGMEM-resident 16-bit image (RGB 5/6/5) at the specified
    (x,y) position. For 16-bit display devices; no color reduction performed.
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with 16-bit color bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Height of bitmap in pixels
  */
  //drawRGBBitmap(x координата верхнего левого угла,y координата верхнего левого угла, bitmap byte массив 16бит цветной, ширина в пикселях, высота в пикселях)
  /*    matrix->drawRGBBitmap(0, 0, (const uint16_t *) smile, 16, 8);
      matrix->show();
      delay(3000);
      matrix->drawRGBBitmap(0, 0, (const uint16_t *) sad, 16, 8);
      matrix->show();
      delay(3000);
      matrix->drawRGBBitmap(0, 0, (const uint16_t *) angry, 16, 8);
      matrix->show();
      delay(3000);*/
  if (Serial1.available() > 0)
  {
    condition = Serial1.read();
    switch (condition)
    {
      case 1:
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          break;
      case 3:
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
          matrix->show();
          delay(500);
          matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
          matrix->show();
          delay(500);
          
          break;
      case 5: matrix->drawRGBBitmap(0, 0, (const uint16_t *) smile, 16, 8); matrix->show(); break;
      case 7: matrix->drawRGBBitmap(0, 0, (const uint16_t *) sad, 16, 8); matrix->show(); break;
      case 9: matrix->drawRGBBitmap(0, 0, (const uint16_t *) surprised, 16, 8); matrix->show(); break;
      case 11: matrix->drawRGBBitmap(0, 0, (const uint16_t *) angry, 16, 8); matrix->show(); break;
      case 13: matrix->drawRGBBitmap(; break;
      case 15: matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8); matrix->show(); break;
      case 17: matrix->clear();  matrix->show(); break;
      default: break;
    }
    Serial.println(condition);
  }
}

/*void traffic()
  {
  if (millis() - myTimer1 > 500)
  {
    myTimer1 = millis();
    matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
    matrix->show();
  }
  if (millis() - myTimer1 > 1000)
  {
    myTimer1 = millis();
    matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
    matrix->show();
  }

  }*/
