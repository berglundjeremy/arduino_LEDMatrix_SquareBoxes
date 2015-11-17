#include <FastLED.h>

#define DATA_PIN 6
#define BRIGHTNESS 20
#define COLOR_ORDER RGB
#define CHIPSET     WS2811
#define DELAY 25

// Params for width and height
const uint8_t kMatrixWidth = 10;
const uint8_t kMatrixHeight = 7;
// Param for different pixel layouts


// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = false;
// Set 'kMatrixSerpentineLayout' to false if your pixels are
// laid out all running the same way, like this:
//
//     0 >  1 >  2 >  3 >  4
//                         |
//     .----<----<----<----'
//     |
//     5 >  6 >  7 >  8 >  9
//                         |
//     .----<----<----<----'
//     |
//    10 > 11 > 12 > 13 > 14
//                         |
//     .----<----<----<----'
//     |
//    15 > 16 > 17 > 18 > 19
//
// Set 'kMatrixSerpentineLayout' to true if your pixels are
// laid out back-and-forth, like this:
//
//     0 >  1 >  2 >  3 >  4
//                         |
//                         |
//     9 <  8 <  7 <  6 <  5
//     |
//     |
//    10 > 11 > 12 > 13 > 14
//                        |
//                        |
//    19 < 18 < 17 < 16 < 15
//
// Bonus vocabulary word: anything that goes one way
// in one row, and then backwards in the next row, and so on
// is call "boustrophedon", meaning "as the ox plows."
// This function will return the right 'led index number' for
// a given set of X and Y coordinates on your matrix.
// IT DOES NOT CHECK THE COORDINATE BOUNDARIES.
// That's up to you.  Don't pass it bogus values.
//
// Use the "XY" function like this:
//
//    for( uint8_t x = 0; x < kMatrixWidth; x++) {
//      for( uint8_t y = 0; y < kMatrixHeight; y++) {
//
//        // Here's the x, y to 'led index' in action:
//        leds[ XY( x, y) ] = CHSV( random8(), 255, 255);
//
//      }
//    }
//
//
uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  if ( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }
  if ( kMatrixSerpentineLayout == true) {
    if ( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }
  return i;
}
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* leds( leds_plus_safety_pixel + 1);
uint16_t XYsafe( int x, int y)
{
  if ( x >= kMatrixWidth) return -1;
  if ( y >= kMatrixHeight) return -1;
  if ( x < 0) return -1;
  if ( y < 0) return -1;
  return XY(x, y);
}



byte colorR;
byte colorG;
byte colorB;
byte rr;

void setup() { 
   FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
   FastLED.setBrightness(BRIGHTNESS);
   randomSeed(analogRead(0)); 
 }

void loop() {
  //Pick a box size
byte BoxSize = random(2, 4);


if (rr > 12) rr = 0;

rr = (rr + 1);
if (rr == 1) colorR = 255, colorG = 0, colorB = 0;
if (rr == 2) colorR = 255, colorG = 128, colorB = 0;
if (rr == 3) colorR = 255, colorG = 128, colorB = 128;
if (rr == 4) colorR = 128, colorG = 255, colorB = 0;
if (rr == 5) colorR = 0, colorG = 255, colorB = 0;
if (rr == 6) colorR = 0, colorG = 255, colorB = 128;
if (rr == 7) colorR = 0, colorG = 255, colorB = 255;
if (rr == 8) colorR = 0, colorG = 128, colorB = 255;
if (rr == 9) colorR = 0, colorG = 0, colorB = 255;
if (rr == 10) colorR = 128, colorG = 0, colorB = 255;
if (rr == 11) colorR = 255, colorG = 0, colorB = 255;
if (rr == 12) colorR = 255, colorG = 0, colorB = 128;

  

int x = random((0 - BoxSize), (kMatrixWidth - BoxSize));
int y = random((0 - BoxSize), (kMatrixHeight - BoxSize));

    // Turn the LED on, then pause 


for(byte on = 1; on <= BoxSize; on++) {
  if (on == 1) {
    leds[ XYsafe((x + 2), (y + 2))] = CRGB(colorR, colorG, colorB); 
    FastLED.show();
    delay(DELAY);
    }  
  else if (on == 2){
    leds[ XYsafe((x + 1), (y + 1))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 1), (y + 2))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 1), (y + 3))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 2), (y + 1))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 2), (y + 3))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 3), (y + 1))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 3), (y + 2))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 3), (y + 3))] = CRGB(colorR, colorG, colorB);
    FastLED.show();
    delay(DELAY);
    }
  else { 
    leds[ XYsafe(x, y)] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe(x, (y + 1))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe(x, (y + 2))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe(x, (y + 3))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe(x, (y + 4))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 1), y)] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 1), (y + 4))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 2), y)] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 2), (y + 4))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 3), y)] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 3), (y + 4))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 4), y)] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 4), (y + 1))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 4), (y + 2))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 4), (y + 3))] = CRGB(colorR, colorG, colorB);
    leds[ XYsafe((x + 4), (y + 4))] = CRGB(colorR, colorG, colorB);
    FastLED.show();
    delay(DELAY);
    } 
   delay(DELAY * 2);  
 } 
  


     // Turn the LED off, then pause 

for(byte off = BoxSize; off > 0; off--) {
  if (off == 1) {
      leds[ XYsafe((x + 2), (y + 2))] = CRGB::Black; 
      FastLED.show();
      delay(30);
      }
  else if (off == 2) {
      leds[ XYsafe((x + 1), (y + 1))] = CRGB::Black;
      leds[ XYsafe((x + 1), (y + 2))] = CRGB::Black;
      leds[ XYsafe((x + 1), (y + 3))] = CRGB::Black;
      leds[ XYsafe((x + 2), (y + 1))] = CRGB::Black;
      leds[ XYsafe((x + 2), (y + 3))] = CRGB::Black;
      leds[ XYsafe((x + 3), (y + 1))] = CRGB::Black;
      leds[ XYsafe((x + 3), (y + 2))] = CRGB::Black;
      leds[ XYsafe((x + 3), (y + 3))] = CRGB::Black;
      FastLED.show();
      delay(30);
      }
  else { 
      leds[ XYsafe(x, y)] = CRGB::Black;
      leds[ XYsafe(x, (y + 1))] = CRGB::Black;
      leds[ XYsafe(x, (y + 2))] = CRGB::Black;
      leds[ XYsafe(x, (y + 3))] = CRGB::Black;
      leds[ XYsafe(x, (y + 4))] = CRGB::Black;
      leds[ XYsafe((x + 1), y)] = CRGB::Black;
      leds[ XYsafe((x + 1), (y + 4))] = CRGB::Black;
      leds[ XYsafe((x + 2), y)] = CRGB::Black;
      leds[ XYsafe((x + 2), (y + 4))] = CRGB::Black;
      leds[ XYsafe((x + 3), y)] = CRGB::Black;
      leds[ XYsafe((x + 3), (y + 4))] = CRGB::Black;
      leds[ XYsafe((x + 4), y)] = CRGB::Black;
      leds[ XYsafe((x + 4), (y + 1))] = CRGB::Black;
      leds[ XYsafe((x + 4), (y + 2))] = CRGB::Black;
      leds[ XYsafe((x + 4), (y + 3))] = CRGB::Black;
      leds[ XYsafe((x + 4), (y + 4))] = CRGB::Black;
      FastLED.show();
      delay(30);
      } 
   delay(DELAY);  
 }

}
