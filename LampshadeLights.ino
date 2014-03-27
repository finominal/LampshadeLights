#include <TimerOne.h>
#include "LPD6803.h"

#define pl(x) Serial.println(x)
#define p(x) Serial.print(x)

enum programs {   wipe, randomPixels, firecrackerSame, firecrackerDifferent,  fadeMono, fadeMonoPaused, rainbowCircle, strobe, purple};
programs program = wipe;

//Example to control LPD6803-based RGB LED Modules in a strand
// Original code by Bliptronics.com Ben Moyes 2009
//Use this as you wish, but please give credit, or at least buy some of my LEDs!

// Code cleaned up and Object-ified by ladyada, should be a bit easier to use

/*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
int dataPin = 3;       // 'yellow' wire
int clockPin = 4;      // 'green' wire
// Don't forget to connect 'blue' to ground and 'red' to +5V

const int stripLength = 24;
const int brightness = 12;
unsigned long lastButtonToggle;


#define BLUE Color(brightness,0,0)
#define RED Color(0,brightness,0)
#define GREEN Color(0,0,brightness)
#define LIGHTBLUE Color(brightness,0,brightness) 
#define  PURPLE  Color(brightness/2,brightness/2,0)//light blue
#define ORANGE Color(0,brightness,brightness)
// Timer 1 is also used by the strip to send pixel clocks

// Set the first variable to the NUMBER of pixels. 20 = 20 pixels in a row
LPD6803 strip = LPD6803(stripLength, dataPin, clockPin);


void setup() {
  //setup the toggle switch
  pinMode(2,INPUT);
  digitalWrite(2, HIGH);
  attachInterrupt(0, InterruptTottleProgram, FALLING);
  
  Serial.begin(57600);
  pl();
  pl("**ARDUINO RESTART**");
  
  strip.setCPUmax(100);  // start with 50% CPU usage. up this if the strand flickers or is slow
  strip.begin();
  strip.show();
}


void loop() {
  
  switch(program)
{
  case wipe:
    testWipe(40);
    break;
  case purple:
    JustPurple();
    break; 
  case randomPixels:
    randomOn(500, 100);
    break;
  case firecrackerSame:
    FirecrackersSameColor(70, 3);
    break;
  case firecrackerDifferent:
    FirecrackersDifferentColor(25, 3);
    break;
  case fadeMono:
    FadeInOutMono(25, 1);
    break;
    case fadeMonoPaused:
    FadeInOutMonoPaused(20, 20);
    break;
  case rainbowCircle:
    rainbowCycle(30);
    break;
  case strobe:
    Strobe();
    break;
}
}

void InterruptTottleProgram()
{
  if( (lastButtonToggle + 500) < millis() ) //pseudo debounce
  {
    switch(program)
    {
      case wipe:
        program = purple;
        break;
      case purple:
        program = randomPixels;
        break;
      case randomPixels:
        program = firecrackerSame;
        break;
      case firecrackerSame:
        program = firecrackerDifferent;
        break;
      case firecrackerDifferent:
        program = fadeMono;
        break;
      case fadeMono:
        program = fadeMonoPaused;
        break;
      case fadeMonoPaused:
        program = rainbowCircle;
        break;
      case rainbowCircle:
        program = strobe;
        break;
      case strobe:
        program = wipe;
        break;
    }

    lastButtonToggle = millis();
        p("StateChangedTo: "); p(program); p(" - millis: "); pl(lastButtonToggle);
  }
}

void Strobe()
{
 unsigned int colorOff = 0; 
 
  PushToAllLEDs(Color(31, 31, 31));
  delay(50);
    PushToAllLEDs(colorOff);
  delay(50);
//    PushToAllLEDs(BLUE);
//  delay(100);
//      PushToAllLEDs(colorOff);
//  delay(100);
//      PushToAllLEDs(GREEN);
//  delay(100);
//      PushToAllLEDs(colorOff);
//  delay(100);
  
}

void JustPurple()
{
  PushToAllLEDs(PURPLE);
}



void FadeInOutMonoPaused(int wait, int pause)
{
  unsigned int b = 21;
  unsigned int r = 0;
  unsigned int g = 0;
  
  while(b >10 && program==fadeMonoPaused)//fade BLUE to RED
  {
    r++;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
    b--;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
  }
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  
    while(b >0 && program==fadeMonoPaused)//fade BLUE to RED
  {
    r++;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
    b--;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
  }
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  
  
  while(r >12 && program==fadeMonoPaused)//fade RED to GREEN
  {    
    g++;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
    r--;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
  }
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  
    while(r >0 && program==fadeMonoPaused)//fade RED to GREEN
  {    
    g++;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
    r--;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
  }
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  
  
  while(g >12 && program==fadeMonoPaused)//fade blue to red
  {
    b++;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
    g--;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
  }
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  
    while(g >0 && program==fadeMonoPaused)//fade blue to red
  {
    b++;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
    g--;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
  }
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  if(program!=fadeMonoPaused) return;
  delay(pause*30);
  
}


void FadeInOutMono(int wait, int pause)
{
  unsigned int b = 21;
  unsigned int r = 0;
  unsigned int g = 0;
  
  while(b >0 && program==fadeMono)//fade BLUE to RED
  {
    r++;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
    b--;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
  }

  while(r >0 && program==fadeMono)//fade RED to GREEN
  {    
    g++;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
    r--;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
  }  delay(wait);
  while(g >0 && program==fadeMono)//fade blue to red
  {
    b++;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
    g--;
    PushToAllLEDs(Color(b,r,g));
    delay(wait);
  }

}


void PushToAllLEDs(unsigned int color)
{
  for (int i = 0; i<stripLength;i++)
  {
    strip.setPixelColor(i,color);
  }
      strip.show();
    delay(1);
}


void FirecrackersDifferentColor(int wait, int cycles)
{
  FirecrackerDiffernt(BLUE, wait, stripLength*cycles);
  FirecrackerDiffernt(PURPLE, wait, stripLength*cycles);
  FirecrackerDiffernt(GREEN, wait, stripLength*cycles);
  FirecrackerDiffernt(RED, wait, stripLength*cycles);
}

void FirecrackersSameColor(int wait, int cycles)
{
  Firecracker(BLUE, wait, stripLength*cycles);
  Firecracker(PURPLE, wait, stripLength*cycles);
  Firecracker(GREEN, wait, stripLength*cycles);
  Firecracker(RED, wait, stripLength*cycles);
}


void FirecrackerDiffernt(unsigned int color, int wait, int steps)
{
  
  unsigned int dulledColour;
  
  //calculate dull persistent color
  if(color == RED)dulledColour = Color(brightness/2,0,0);
  if(color == PURPLE )dulledColour = Color(0,brightness/2,0);
  if(color == BLUE  )dulledColour = Color(0,0,brightness/2);
  if(color == GREEN )dulledColour = Color(brightness/2,brightness/2,0);
  
  //execute the loop
  for(int i = 0; i < steps; i++)
  {
    if(program != firecrackerDifferent) break;
    //strip.setPixelColor(i % stripLength, 0);//turn off previous
    strip.setPixelColor(i % stripLength, color); //turn up next
    strip.show();
    delay(wait);
    strip.setPixelColor(i % stripLength, dulledColour); //turn down current
    strip.setPixelColor(i+1 % stripLength, dulledColour); //turn up next current
    strip.show();
    delay(wait);
  }
}

void Firecracker(unsigned int color, int wait, int steps)
{
  
  unsigned int dulledColour;
  
  //calculate dull persistent color
  if(color == BLUE)dulledColour = color/2;
  if(color == RED)dulledColour = Color(0,brightness/2,0);
  if(color == GREEN)dulledColour = Color(0,0,brightness/2);
  if(color == PURPLE)dulledColour = Color(brightness/4,brightness/4,0);
  
  //execute the loop
  for(int i = 0; i < steps; i++)
  {
    if(program != firecrackerSame) break;
    
    strip.setPixelColor(i % stripLength, color); //turn up next
    strip.show();
    delay(wait);
    strip.setPixelColor(i % stripLength, dulledColour); //turn down current
    strip.setPixelColor(i+1 % stripLength, dulledColour); //turn up next current
    strip.show();
    delay(wait);
    
  }
}



void testWipe(int wait)
{
  if(program == wipe) colorWipe(BLUE, wait*1.1);
  if(program == wipe) colorWipe(Color(0, 0, 0), wait*1.1);
  if(program == wipe) colorWipe(RED, wait);
  if(program == wipe) colorWipe(Color(0, 0, 0), wait);
  if(program == wipe) colorWipe(GREEN, wait);
  if(program == wipe) colorWipe(Color(0, 0, 0), wait);
}

void randomOn(int wait, int repeat)
{
  for(int i = 0; i < repeat;i++)
  {
    if(program != randomPixels)break;
    RandomFlipPixel(RED);
    RandomFlipPixel(GREEN);
    RandomFlipPixel(BLUE);
    RandomFlipPixel(PURPLE);
    RandomFlipPixel(ORANGE);
    
    strip.show();
    delay(wait);
  }
}

void RandomFlipPixel(unsigned int color)
{
    int randomPixel = 0;
    randomPixel = random(0,strip.numPixels()-1); //pick a pixel to turn on or off
    if(strip.getPixelColor(randomPixel) != -32768)
    {
      strip.setPixelColor(randomPixel,0);
    }
    else
    {
     strip.setPixelColor(randomPixel, color);
    }
}

unsigned int randomColor()
{
 return Color(random(0,brightness), random(0,brightness), random(0,brightness));
}


// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 96 * 5; j++) {     // 5 cycles of all 96 colors in the wheel
  // while(true) {//run indefinately 
     if(program != rainbowCircle) break;
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      if(program != rainbowCircle) break;
      strip.setPixelColor(i, Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint16_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
       if(program != wipe) break;
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/* Helper functions */

// Create a 15 bit color value from R,G,B
unsigned int Color(byte r, byte g, byte b)
{
  //Take the lowest 5 bits of each value and append them end to end
  return( ((unsigned int)g & 0x1F )<<10 | ((unsigned int)b & 0x1F)<<5 | (unsigned int)r & 0x1F);
}

//Input a value 0 to 127 to get a color value.
//The colours are a transition r - g -b - back to r
unsigned int Wheel(byte WheelPos)
{
  byte r,g,b;
  switch(WheelPos >> 5)
  {
    case 0:
      r=31- WheelPos % 32;   //Red down
      g=WheelPos % 32;      // Green up
      b=0;                  //blue off
      break; 
    case 1:
      g=31- WheelPos % 32;  //green down
      b=WheelPos % 32;      //blue up
      r=0;                  //red off
      break; 
    case 2:
      b=31- WheelPos % 32;  //blue down 
      r=WheelPos % 32;      //red up
      g=0;                  //green off
      break; 
  }
  return(Color(r,g,b));
}

//    unsigned int Wheel(byte WheelPos)
//{
//  byte r,g,b;
//  switch(WheelPos >> 5)
//  {
//    case 0:
//      r=brightness- WheelPos % brightness+1;   //Red down
//      g=WheelPos % 32;      // Green up
//      b=0;                  //blue off
//      break; 
//    case 1:
//      g=brightness- WheelPos % brightness+1;  //green down
//      b=WheelPos % 32;      //blue up
//      r=0;                  //red off
//      break; 
//    case 2:
//      b=brightness- WheelPos % brightness+1;  //blue down 
//      r=WheelPos % 32;      //red up
//      g=0;                  //green off
//      break; 
//  }
//  return(Color(r,g,b));
//}
//    
