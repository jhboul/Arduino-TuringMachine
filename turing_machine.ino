// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            9

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      24

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int rnd = 1024; // 31, 95, 97, 12!, 14, 21, 30, 35, 56, 1024!, 1025, 78
bool lights[] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
int delayval = 100; //delay
int level = 40; //brightness
int pos = 240;
int card = 0;
//on card     dir      on/off  off card       dir    on/off
//(((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),

int prog[] = {
  (((((0) * 2 + (1)) * 2 + (1)) * 16 + (1)) * 2 + (0)) * 2 + (1),
  (((((1) * 2 + (0)) * 2 + (1)) * 16 + (0)) * 2 + (1)) * 2 + (1),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
  (((((0) * 2 + (0)) * 2 + (0)) * 16 + (0)) * 2 + (0)) * 2 + (0),
};

void tick() {

  greenLight(pos, 40);
  int aCard = thisCard(card, lights[pos % 24]);
  int anotherCard = nextCard(aCard);
  int dir = nextDir(aCard);
  int on = nextOn(aCard);

  lights[pos % 24] = trueFalse(on);
  pos = pos + dir;
  card = anotherCard;
  
  setLights();
  delay(delayval);
  
}

void rndProg() {
  for (int i = 0; i < 16; i++) {
    greenLight(i, 40);
    prog[i] = randomNumber() % 4356;
  }
}

int randomNumber() {
  return rnd = (rnd * 7717) % 7177;
}

int nextOn(int aCard){
  return aCard % 2;
}

int nextDir(int aCard){
  int dir = bitShift(aCard, 1) % 2;
  if (trueFalse(dir)) {
    return 1;
  }
  return -1;
}

int nextCard(int aCard){
  return bitShift(aCard, 2);
}

int thisCard(int aCard, bool on){

  if (on) {
    return bitShift(prog[aCard], 6);
  } else {
    return (prog[aCard] + 640) % 64;
  }
  
}

int bitShift(int aNumber, int shiftNumber) {
  for (int i = 0; i < shiftNumber; i++) {
    aNumber = aNumber / 2;
  }
  return aNumber;
}

int oneZero(bool aBool) {

  if (aBool) {
    return 1;
  }
  return 0;
  
}

bool trueFalse(int number) {

  return number == 1;
  
}

void setLights() {

  for (int i = 0; i < NUMPIXELS; i++){
    blueLight(i, oneZero(lights[i]) * level);
  }
  
}

void resetLights() {

  for (int i = 0; i < NUMPIXELS; i++){
    lights[i] = 0;
  }
  
}

void blueLight (int aLight, int level) {

  aLight = (aLight + NUMPIXELS * 100) % NUMPIXELS;
  pixels.setPixelColor(aLight, pixels.Color(0,0,level));
  pixels.show();
  
}

void greenLight (int aLight, int level) {

  aLight = (aLight + NUMPIXELS * 100) % NUMPIXELS;
  pixels.setPixelColor(aLight, pixels.Color(0,level,0));
  pixels.show();
  delay(100);
  
}

void redLight (int aLight, int level) {

  aLight = (aLight + NUMPIXELS * 100) % NUMPIXELS;
  pixels.setPixelColor(aLight, pixels.Color(level,0,0));
  pixels.show();
  delay(500);
  
}

void setup() {
// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  rndProg();

}

void loop() {

  /*
  rndProg();
  resetLights();
  setLights();
  pos = 240;
  card = 0;
  */
  for (int i = 0; i < 144; i++) {
    tick();
  }

}
