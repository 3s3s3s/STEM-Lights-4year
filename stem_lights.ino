#include "arduino_secrets.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif


#define LED_PIN    13
#define LED_PIN_2    11

#define LED_COUNT 9
#define LED_COUNT_2 13

Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT_2, LED_PIN_2, NEO_GRB + NEO_KHZ800);
int trigPin = 10;
int echoPin = 12;
bool someoneNearby = false;
long duration;
long distance;
int currentMillis;
int previousMillis;
int difference;
bool proceed=false;
int Bpin=4;
int Lpin=9;
int BHpin=2;
int DHpin=7;
//Pin 3 doesn't work
void setup() {

  pinMode(Bpin, OUTPUT);
  pinMode(Lpin, OUTPUT);
  pinMode(BHpin, OUTPUT);
  pinMode(DHpin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  normalLightsOf();
  strip1.begin();
  strip1.show();
  strip1.setBrightness(25);

  strip2.begin();
  strip2.show();
  strip2.setBrightness(25);
}


//This repeats over and over untill the arduino has no power 
void loop() {
  digitalWrite(Lpin,HIGH);
  if(checkNearby()){
    colorWipe2(strip2.Color(rand()%256,rand()%100,rand()%256),10);
    colorWipe(strip1.Color(rand()%256,rand()%256,rand()%100),10);
    delay(1000);
  }
}

bool checkNearby() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if(distance<100){
    normalLightsOn();
    return true;
  }
  if(distance>150){
    strip1.clear();
    strip2.clear();
    strip1.show();
    strip2.show();
    if(checkMillis(500)){
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2;
      if(distance>10){
        delay(100+rand()%100);
        normalLightsOf();
      }
    }
    return false;
  }
}

bool checkMillis(int difference) {
  currentMillis = millis();
  if (currentMillis>previousMillis) {
    if(difference<=currentMillis-previousMillis){
      return true;
    }else{
      return false;
    }
    currentMillis=previousMillis;
    return currentMillis;
  }
}

void normalLightsOn() {
  digitalWrite(Bpin, HIGH);
  delay(100+rand()%900);
  digitalWrite(BHpin, HIGH);
  delay(100+rand()%900);
  digitalWrite(DHpin, HIGH);
}

void normalLightsOf() {
  digitalWrite(Bpin, LOW);
  delay(100+rand()%900);
  digitalWrite(BHpin, LOW);
  delay(100+rand()%900);
  digitalWrite(DHpin, LOW);
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, color);
    strip1.show();
    delay(wait);  
  }
}

void colorWipe2(uint32_t color, int wait) {
  for(int i=0; i<strip2.numPixels(); i++) {
    strip2.setPixelColor(i, color);
    strip2.show();
    delay(wait);  
  }
}

void theaterChase(uint32_t color, int wait, Adafruit_NeoPixel strip) {
  for(int a=0; a<10; a++) {
    for(int b=0; b<3; b++) {
      strip.clear();
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color);
      }
      strip.show();
      delay(wait);
    }
  }
}

void rainbow(int wait, Adafruit_NeoPixel strip) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue);
    strip.show();
    delay(wait);
  }
}

void theaterChaseRainbow(int wait, Adafruit_NeoPixel strip) {
  int firstPixelHue = 0;
  for (int a = 0; a < 30; a++) {
    for (int b = 0; b < 3; b++) {
      strip.clear();
      for (int c = b; c < strip.numPixels(); c += 3) {
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue));
        strip.setPixelColor(c, color);
      }
      strip.show();
      delay(wait);
      firstPixelHue += 65536 / 90;
    }
  }
}