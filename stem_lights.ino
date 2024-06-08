#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif


#define LED_PIN    6
#define LED_PIN_2    5

#define LED_COUNT 9
#define LED_COUNT_2 13

Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT_2, LED_PIN_2, NEO_GRB + NEO_KHZ800);
int trigPin = 7;
int echoPin = 0;
bool someoneNearby = false;
long duration;
long distance;
int stripCount = LED_COUNT;
int strip2Count = LED_COUNT_2;
int currentMillis;
int previousMillis;
int difference;
bool proceed=false;
int a=0;
int b=0;
int c;
int i=0;

void setup() {

  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  normalLightsOf();
  strip1.begin();
  strip1.show();
  strip1.setBrightness(51);

  strip2.begin();
  strip2.show();
  strip2.setBrightness(51);
}



void loop() {
  digitalWrite(1,LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}

void checkNearby() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 200;
  if (distance < 1 && !someoneNearby) {
    someoneNearby = true;
    normalLightsOn();
  }
  if (distance > 1 && someoneNearby) {
    someoneNearby = false;
    normalLightsOf();
  }
}

void checkMillis(int difference) {
  currentMillis = millis();
  if (currentMillis>previousMillis) {
    if(difference<=currentMillis-previousMillis){
      proceed=true;
    }else{
      proceed=false;
    }
    previousMillis = currentMillis;
  }
  return proceed;
}

void normalLightsOn() {
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(1, HIGH);
}

void normalLightsOf() {
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  digitalWrite(1, LOW);
}

void colorWipe(uint32_t color, int wait, Adafruit_NeoPixel strip) {
  for (i = 0 ; i < strip.numPixels();i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void theaterChase(uint32_t color, int wait, Adafruit_NeoPixel strip) {
  if (a < 10) {
    if (b < 3) {
      b++;
      strip.clear();
      if (c < strip.numPixels()) {
        c;
        strip.setPixelColor(c, color);
        return c;
      }
      strip.show();
      delay(wait);
      return c;
      return b;
    }
    return c;
    return b;
    return a++;
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