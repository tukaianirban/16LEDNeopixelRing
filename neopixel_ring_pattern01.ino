#include <Adafruit_NeoPixel.h>
 
#define PIN 6
#define NUM_LEDS 16

#define LOOP_COUNT 10



Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  strip.begin();
  strip.setBrightness(200); //adjust brightness here; (max=256)
  strip.show(); // Initialize all pixels to 'off'
}
 
void loop() {

  randomiZer();
  
  ledNspeeder();

  colorWipeRainbowSlow();
  
  wheelofColors();

  colorWipeRainbowAggressive();

  
}

/************* META FUNCTIONS ****************/

void randomiZer(){

  WipeBlank();
  
  for (uint32_t i=0;i<LOOP_COUNT;i++){
    for (uint32_t j=0;j<256;j+=8){
      int r = random(strip.numPixels());
      strip.setPixelColor(r, Wheel(j));
      strip.show();
      delay(50);

      strip.setPixelColor(r, 0);
      strip.show();
      delay(50);
    }
  }
}
void colorWipeRainbowSlow(){

  for (uint8_t k=0;k<LOOP_COUNT*3;k++){
    for (uint32_t i=0;i<256;i+=32){
      colorWipe(Wheel(i), 100);
      delay(500);
    }
  }
}

void colorWipeRainbowAggressive(){

  for (uint8_t k=0;k<LOOP_COUNT*5;k++){
    for (uint32_t i=0;i<256;i+=32){
      colorWipe(Wheel(i), 50);
    }
  }
}

void wheelofColors(){
  uint8_t repeats=10, waittime=100;

  for (uint8_t k=0;k<LOOP_COUNT;k++){
    for (uint32_t i=0;i<256;i+=16){
      for (uint32_t j=0;j<repeats;j++){
        spinningWheel(Wheel(i), waittime);
      }
    }
  }
}

void ledNspeeder(){
  uint8_t wait=30,N=3;
  for (uint8_t k=0;k<LOOP_COUNT;k++){
    for (uint32_t i=0;i<256;i+=8){
      for (uint8_t j=0;j<strip.numPixels();j++)
        // leds at j,j+1 will glow; all else will be off
        glowNleds(j,N, Wheel(i),wait);
    }
  }
}



/********************************************/

// glow  leds only
void glowNleds(uint8_t pos, uint8_t n, uint32_t c, uint8_t wait){
  // blank all leds before pos1
  for (uint8_t i=0;i<pos;i++){
    strip.setPixelColor(i,strip.Color(0,0,0));  
  }

  // glow the N leds
  for (uint8_t i=0;i<n;i++){
    strip.setPixelColor((pos+i)%strip.numPixels(), c);
  }

  // blank all leds after pos+N
  for (uint8_t i=pos+n;i<strip.numPixels();i++){
    strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
  delay(wait);
}

// spinning wheel
void spinningWheel(uint32_t c, uint8_t wait){

  // set color on all even numbered pixels
  for (uint8_t j=0;j<strip.numPixels(); j+=2){
      strip.setPixelColor(j,c);
    }
  strip.show();
  delay(wait);
  
  // wipe all pixels
  WipeBlank();
  
  // set color on all odd numbered pixels
  for (uint8_t j=1;j<strip.numPixels(); j+=2){
      strip.setPixelColor(j,c);
    }
  strip.show();
  delay(wait);
 
  // wipe all pixels
  WipeBlank();
}

void WipeBlank(){
  for (uint8_t i=0;i<strip.numPixels();i++){
    strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
