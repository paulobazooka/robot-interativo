#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Olhos.h>

unsigned int _DELAY = 35;
unsigned int _DELAY2 = 30;

void respostaSIM(Adafruit_SSD1306 *display)
{
    for (byte i = 0; i < 5; i++)
    {
        display->clearDisplay();
        display->drawBitmap(0, 0, OLHOS_CENTRO, 128, 64, WHITE);
        display->display();
        delay(_DELAY);

        display->clearDisplay();
        display->drawBitmap(0, 10, OLHOS_CENTRO, 128, 64, WHITE);
        display->display();
        delay(_DELAY);

        display->clearDisplay();
        display->drawBitmap(0, 0, OLHOS_CENTRO, 128, 64, WHITE);
        display->display();
        delay(_DELAY);

        display->clearDisplay();
        display->drawBitmap(0, -10, OLHOS_CENTRO, 128, 64, WHITE);
        display->display();
        delay(_DELAY);
    }
}

void respostaNAO(Adafruit_SSD1306 *display)
{
     for (byte i = 0; i < 5; i++)
    {
        display->clearDisplay();
        display->drawBitmap(0, 0, OLHOS_CENTRO, 128, 64, WHITE);
        display->display();
        delay(_DELAY2);

        display->clearDisplay();
        display->drawBitmap(15, 0, OLHOS_CENTRO, 128, 64, WHITE);
        display->display();
        delay(_DELAY2);

        display->clearDisplay();
        display->drawBitmap(0, 0, OLHOS_CENTRO, 128, 64, WHITE);
        display->display();
        delay(_DELAY2);

        display->clearDisplay();
        display->drawBitmap(-15, 0, OLHOS_CENTRO, 128, 64, WHITE);
        display->display();
        delay(_DELAY2);        
    }
}