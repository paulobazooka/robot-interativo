#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Olhos.h"

#define ACORDADA    0 
#define DESCONFIADA 1 
#define BRAVA       2 
#define FELIZ       3
#define PISCADA     4

void acordada(Adafruit_SSD1306 *display){
  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_ABERTOS, 128, 64, WHITE);
  display->display();
  delay(2300);

  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_SEMI_CERRADOS, 128, 64, WHITE);
  display->display();

  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_CERRADOS, 128, 64, WHITE);
  display->display();
 
  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
  display->display();

  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_CERRADOS, 128, 64, WHITE);
  display->display();

  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_SEMI_CERRADOS, 128, 64, WHITE);
  display->display();
}

void desconfiada(Adafruit_SSD1306 *display){
  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_SEMI_CERRADOS, 128, 64, WHITE);
  display->display();
  delay(2300);

  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_CERRADOS, 128, 64, WHITE);
  display->display();
 
  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
  display->display();

  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_CERRADOS, 128, 64, WHITE);
  display->display();
}

void dormindo(Adafruit_SSD1306 *display){
  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
  display->display();
  delay(400);

  display->clearDisplay();
  display->drawBitmap(0, -5, OLHOS_FECHADOS, 128, 64, WHITE);
  display->display();
  delay(500);

  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
  display->display();
  delay(500);

  display->clearDisplay();
  display->drawBitmap(0, 5, OLHOS_FECHADOS, 128, 64, WHITE);
  display->display();
  delay(500);
}

void sonolenta(Adafruit_SSD1306 *display){

  for (byte i = 0; i < 5; i++)
  {
  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_SEMI_CERRADOS, 128, 64, WHITE);
  display->display();
  delay(200);

  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
  display->display();
  delay(800);
  }
}

void brava(Adafruit_SSD1306 *display){
  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_CERRADOS, 128, 64, WHITE);
  display->display();
  delay(2000);

  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
  display->display();
}

void piscada(Adafruit_SSD1306 *display){
  
  for (byte i = 0; i < 2; i++)
  {
  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_ABERTOS, 128, 64, WHITE);
  display->display();
  delay(1800);

  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_PISCADA, 128, 64, WHITE);
  display->display();
  delay(200);
  }
}

void feliz(Adafruit_SSD1306 *display){
  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_ABERTOS, 128, 64, WHITE);
  display->display();
  delay(1000);
  display->clearDisplay();
  display->drawBitmap(0, 0, OLHOS_SORRIDENTES, 128, 64, WHITE);
  display->display();
  delay(1500);
}