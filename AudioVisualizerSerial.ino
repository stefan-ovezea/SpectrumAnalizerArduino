#include <FastLED.h>

#define BAUD_RATE 115200
#define COLUMNS 32
#define ROWS 8

#define NUM_LEDS 256
#define DATA_PIN 5
#define SERIALRATE 115200
#define CALIBRATION_TEMPERATURE TypicalLEDStrip
#define MAX_BRIGHTNESS 255 // 0-255

int incomingData[COLUMNS];
CRGB leds[NUM_LEDS];

int singleRow[COLUMNS];
int spectrumRepresentation[NUM_LEDS];
// Test data: "6,6,5,5,4,3,3,3,3,2,2,3,3,3,3,3,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,0"

void setup() {
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setTemperature( CALIBRATION_TEMPERATURE );
    FastLED.setBrightness( MAX_BRIGHTNESS );
    Serial.begin(BAUD_RATE);
    for (int i = 0; i < COLUMNS; i++) {
      if (i == 0) singleRow[i] = 0;
      else if (i % 2 == 1)
        singleRow[i] = (singleRow[i - 1] + 16) - 1;
      else
        singleRow[i] = singleRow[i - 1] + 1;
    }
    singleRow;

    for (int i = 0; i < NUM_LEDS; i++) {
      spectrumRepresentation[i] = i;
    }
}

void loop() {
    if (Serial.available() > 0) {
        for (int i = 0; i < COLUMNS; i++) {
          if (Serial.read() != '\n')
            incomingData[COLUMNS - 1 - i] = Serial.parseInt();
        }
//        Serial.print("End:" + Serial.read());

//        for (int i = 0; i < COLUMNS; i++) {
//          Serial.print(incomingData[i] + ", ");
//        }
        
//        if (Serial.read() == -1)
        for (int i = 0; i < COLUMNS; i++) {
            if (i % 2 == 0) {
              for (int j = singleRow[i]; j < singleRow[i] + (ROWS - 1); j++) {
                if (j < singleRow[i] + incomingData[i])
                  leds[spectrumRepresentation[j]] = CRGB::Red;
                else {
                  leds[spectrumRepresentation[j]] = CRGB::Black;
                }
              }
            } else {
              for (int j = singleRow[i]; j > singleRow[i] - (ROWS - 1); j--) {
                if (j > singleRow[i] - incomingData[i])
                  leds[spectrumRepresentation[j]] = CRGB::Red;
                else {
                  leds[spectrumRepresentation[j]] = CRGB::Black;
                }
              }
            }
        }
//        FastLED.show();
    } else {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[spectrumRepresentation[i]] = CRGB::Black;  
      }
    }
    FastLED.show();
//    delay(30);
}
