
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
#include "NEW.h"

#define PIN 9 //matrix connection pin 
#define mw 16 // ширина
#define mh 8 // высота
#define NUMMATRIX (mw*mh) //количество светодиодов в матрице

#define DISABLE_WHITE //для заполнения белым при старте - закомментировать, для выключения - разкомментировать

int NEWMATRIX = 14; //количество светодиодов в матрице щек
// Max is 255, 32 is a conservative value to not overload
// a USB power supply (500mA) for 12x12 pixels.
int BRIGHTNESS = 16; //яркость

CRGB leds[NUMMATRIX];
CRGB cheeks[14];
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
  FastLED.addLeds<NEOPIXEL, 8>(cheeks, 14).setCorrection(TypicalLEDStrip);

  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setBrightness(30);
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

  if (Serial1.available() > 0)
  {
    condition = Serial1.read();
    Serial.println(condition);
    Serial1.write(condition);
  }

  switch (condition)
  {
    case 2:
      Serial.println("case 1");
      if (millis() % 1000 > 500)
      {
        matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
        matrix->show();
      }
      else
      {
        matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
        matrix->show();
      }
      break;
    case 4:
      if (millis() % 1000 > 500)
      {
        matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
        matrix->show();
      }
      else
      {
        matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
        matrix->show();
      }
      break;
    case 5: matrix->drawRGBBitmap(0, 0, (const uint16_t *) smile, 16, 8); matrix->show(); break;
    case 7: matrix->drawRGBBitmap(0, 0, (const uint16_t *) sad, 16, 8); matrix->show(); break;
    case 9: matrix->drawRGBBitmap(0, 0, (const uint16_t *) surprised, 16, 8); matrix->show(); break;
    case 11: matrix->drawRGBBitmap(0, 0, (const uint16_t *) angry, 16, 8); matrix->show(); break;
    case 13:
      matrix->drawRGBBitmap(0, 0, (const uint16_t *) NEW, 16, 8);
      matrix->show();
      for ( int i = 0; i < 15; i++)
      {
        cheeks[i] = 0x901010;
        matrix->show();
      }
      break;
    case 15: matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8); matrix->show();
      for ( int i = 0; i < 15; i++)
      {
        cheeks[i] = 0x000000;
        matrix->show();
      }
      break;
    case 18:
      if (millis() % 1000 > 500)
      {
        matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
        matrix->show();
      }
      else
      {
        matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
        matrix->show();
      }
      break;
    case 20:
      if (millis() % 1000 > 500)
      {
        matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
        matrix->show();
      }
      else
      {
        matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
        matrix->show();
      }
      break;

    default: break;
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
