#include <Adafruit_GFX.h>

#include <SPI.h>
#include <ILI9341_t3n.h>

#include "ili9341_t3n_font_Arial.h"
#include "ili9341_t3n_font_ArialBold.h"
#include "ili9341_t3n_font_ComicSansMS.h"
#include "ili9341_t3n_font_OpenSans.h"

#define ILI9341_CS 10
#define ILI9341_DC 9
#define ILI9341_RST 8
ILI9341_t3n tft = ILI9341_t3n(ILI9341_CS, ILI9341_DC, ILI9341_RST);
uint8_t test_screen_rotation = 0;


void setup() {
  Serial.begin(38400);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  Serial.println("Setup");
  tft.begin();

  tft.setRotation(4);
  tft.fillWindow(ILI9341_BLACK);

  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_14);
  tft.println("Arial_14");
  displayStuff();

  tft.setTextColor(ILI9341_YELLOW);
  tft.setFont(Arial_14_Bold);
  tft.println("ArialBold 14");
  displayStuff();

  tft.setTextColor(ILI9341_GREEN);
  tft.setFont(ComicSansMS_14);
  tft.println("ComicSansMS 14");
  displayStuff(); 

  nextPage();
  
  Serial.println("Basic Font Display Complete");
  Serial.println("Loop test for alt colors + font");
}

void loop()
{
  Serial.printf("\nRotation: %d\n", test_screen_rotation);
  tft.setRotation(test_screen_rotation);
  test_screen_rotation = (test_screen_rotation + 1) & 0x3;
  
  nextPage();

  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_14);
  tft.println("Arial_14");
  displayStuff1();

  tft.setTextColor(ILI9341_YELLOW);
  tft.setFont(Arial_14_Bold);
  tft.println("ArialBold 14");
  displayStuff1();

  nextPage();

  tft.setTextColor(ILI9341_GREEN);
  tft.setFont(ComicSansMS_14);
  tft.println("ComicSansMS 14");
  displayStuff1(); 

  nextPage();
}

uint32_t displayStuff()
{
  elapsedMillis elapsed_time = 0;
  tft.println("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  tft.println("abcdefghijklmnopqrstuvwxyz");
  tft.println("0123456789");
  tft.println("!@#$%^ &*()-");
  tft.println(); tft.println();
  return (uint32_t) elapsed_time;
}

uint32_t displayStuff1()
{
  elapsedMillis elapsed_time = 0;
  tft.println("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  tft.println("abcdefghijklmnopqrstuvwxyz");
  tft.println("0123456789");
  tft.println("!@#$%^ &*()-");
  static const char alternating_text[] = "AbCdEfGhIjKlMnOpQrStUvWxYz\raBcDeFgHiJkLmNoPqRsTuVwXyZ";
 
  for (uint8_t i = 0; i < sizeof(alternating_text); i++) {
    if (i & 1) tft.setTextColor(ILI9341_WHITE, ILI9341_RED);
    else tft.setTextColor(ILI9341_YELLOW, ILI9341_BLUE);
    tft.write(alternating_text[i]);
  }
  tft.println(); tft.println();
  return (uint32_t) elapsed_time;
}

void nextPage()
{
  Serial.println("Press anykey to continue");
  while (Serial.read() == -1) ;
  while (Serial.read() != -1) ;

  tft.fillWindow(ILI9341_BLACK);
  tft.setCursor(0, 0);
}
