#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Bateria.h>

unsigned int DELAY = 280;

void bateriaFraca(Adafruit_SSD1306 *display){
    display->clearDisplay();
    display->drawBitmap(0, 0, BATERIA_FRACA_1, 128, 64, WHITE);
    display->display();
    delay(DELAY);

    display->clearDisplay();
    display->drawBitmap(0, 0, BATERIA_FRACA_2, 128, 64, WHITE);
    display->display();
    delay(DELAY);
}