/***************************************************************************  
Get notifications when the international space station is passing over you

Author: Mohit Bhoite
Project Repository: https://github.com/mohitbhoite/spark-iss-monitor
IFTTT Recipe: https://ifttt.com/recipes/236873-iss-tracker

MIT license, all text above must be included in any redistribution
****************************************************************************/
#include "Adafruit_GFX/Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"

#ifndef _BV
  #define _BV(bit) (1<<(bit))
#endif

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

static const uint8_t  smile_bmp[] =
  { 0B00111100,
    0B01000010,
    0B10100101,
    0B10000001,
    0B10100101,
    0B10011001,
    0B01000010,
    0B00111100 };
static const uint8_t  neutral_bmp[] =
  { 0B00111100,
    0B01000010,
    0B10100101,
    0B10000001,
    0B10111101,
    0B10000001,
    0B01000010,
    0B00111100 };
static const uint8_t  frown_bmp[] =
  { 0B00111100,
    0B01000010,
    0B10100101,
    0B10000001,
    0B10011001,
    0B10100101,
    0B01000010,
    0B00111100 };
static const uint8_t  cloud_bmp[] =
  { 0B00000000,
    0B00000000,
    0B00110100,
    0B01111110,
    0B11111111,
    0B11111111,
    0B00000000,
    0B00000000 };

uint8_t counter = 0;

int issPassingOver(String command);
int passing = 0;


// This function is executed when the IFTTT receipe calls it
int issPassingOver(String command)
{
    if(command == "iss")
    {
     passing = 1;
     return 1;   
    }
    else return -1;
}

void setup() {
    // Setup the 8x8 matrix led controller backpack  
    matrix.begin(0x70);  // pass in the address
    Spark.function("iss",issPassingOver);
}

void loop() {

    matrix.clear();
    matrix.setRotation(0);
    
    // Play the scrolling cloud animation
    for (int8_t x=20; x>=-20; x--) {
            matrix.clear();
            matrix.drawBitmap(x, 0, cloud_bmp, 8, 8, LED_ON);
            matrix.writeDisplay();
            delay(100);
        }

    //If the ISS is passing over, execute the following
    if (passing)
    {
        // Blink the entire display 
        for (int i =0;i<5;i++)
        {
            matrix.fillRect(0,0, 8,8, LED_ON);
            matrix.writeDisplay();  
            delay(200);
        
            matrix.clear();
            matrix.writeDisplay();
            delay(200);
        }
        
        // Display a smiling face
        matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
        matrix.writeDisplay();
        delay(1000);
        
        // Print a scrolling message
        for (int8_t x=0; x>=-100; x--) {
            matrix.clear();
            matrix.setCursor(x,0);
            matrix.print("ISS passing over! ");
            matrix.writeDisplay();
            delay(80);
        }
        
        // Clear the display
        matrix.clear();
        matrix.writeDisplay();
        delay(500);
    }
    
    passing = 0;

}