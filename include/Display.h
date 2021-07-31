#ifndef TELA_H
#define TELA_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Olhos.h"
#include "Bateria.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4     // Reset pin # (or -1 if sharing Arduino reset pin)

unsigned int DELAY = 330;
unsigned int _DELAY = 35;
unsigned int _DELAY2 = 30;


Adafruit_SSD1306 d(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Incializar o display
boolean inicializarDisplay()
{
    if (d.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        return true;
    else
        return false;    
}


/*
*   Display ON
*/
void displayON()
{
    Serial.println("Ligar display");
    d.displayON();
}

/*
*   Display ON
*/
void displayOFF()
{
    Serial.println("Desligar display");
    d.displayOFF();
}

/*
*   Display clear
*/
void limpar()
{
    Serial.println("Limpar display");
    d.clearDisplay();
}

/*
*   Display ON
*/
void show()
{
    Serial.println("Show display");
    d.display();
}

/*
*   Reduzir brilho
*/
void reduzirBrilho(boolean reduzir)
{
    Serial.print("Reduzir brilho? ");
    Serial.println(reduzir == 1 ? "SIM" : "NÃO");
    d.dim(reduzir);
}

/*
*   Bateria fraca
*/
void bateriaFraca()
{
    d.clearDisplay();
    d.drawBitmap(0, 0, BATERIA_FRACA_1, 128, 64, WHITE);
    d.display();
    delay(DELAY);

    d.clearDisplay();
    d.drawBitmap(0, 0, BATERIA_FRACA_2, 128, 64, WHITE);
    d.display();
    delay(DELAY);
}

/*    
 *  Acordada 
 */
void acordada()
{
    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_ABERTOS, 128, 64, WHITE);
    d.display();
    delay(2300);

    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_SEMI_CERRADOS, 128, 64, WHITE);
    d.display();

    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_CERRADOS, 128, 64, WHITE);
    d.display();

    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
    d.display();

    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_CERRADOS, 128, 64, WHITE);
    d.display();

    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_SEMI_CERRADOS, 128, 64, WHITE);
    d.display();
}

/*    
 *  Desconfiada 
 */
void desconfiada()
{
    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_SEMI_CERRADOS, 128, 64, WHITE);
    d.display();
    delay(2300);

    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_CERRADOS, 128, 64, WHITE);
    d.display();

    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
    d.display();

    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_CERRADOS, 128, 64, WHITE);
    d.display();
}

/*
*   Dormindo
*/
void dormindo()
{
    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
    d.display();
    delay(400);

    d.clearDisplay();
    d.drawBitmap(0, -5, OLHOS_FECHADOS, 128, 64, WHITE);
    d.display();
    delay(500);

    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
    d.display();
    delay(500);

    d.clearDisplay();
    d.drawBitmap(0, 5, OLHOS_FECHADOS, 128, 64, WHITE);
    d.display();
    delay(500);
}

/*
*   Sonolenta
*/
void sonolenta()
{
    for (byte i = 0; i < 5; i++)
    {
        d.clearDisplay();
        d.drawBitmap(0, 0, OLHOS_SEMI_CERRADOS, 128, 64, WHITE);
        d.display();
        delay(200);

        d.clearDisplay();
        d.drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
        d.display();
        delay(800);
    }
}

/*
*   Brava
*/
void brava()
{
    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_BRAVA, 128, 64, WHITE);
    d.display();
    delay(2000);

    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
    d.display();
}

/*
*   Piscada
*/
void piscada()
{
    for (byte i = 0; i < 2; i++)
    {
        d.clearDisplay();
        d.drawBitmap(0, 0, OLHOS_ABERTOS, 128, 64, WHITE);
        d.display();
        delay(1800);

        d.clearDisplay();
        d.drawBitmap(0, 0, OLHOS_PISCADA, 128, 64, WHITE);
        d.display();
        delay(200);
    }
}

/*
*   Feliz
*/
void feliz()
{
    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_ABERTOS, 128, 64, WHITE);
    d.display();
    delay(1000);
    d.clearDisplay();
    d.drawBitmap(0, 0, OLHOS_SORRIDENTES, 128, 64, WHITE);
    d.display();
    delay(1500);
}

/*
*   SIM
*/
void sim(){
    for (byte i = 0; i < 5; i++)
    {
        d.clearDisplay();
        d.drawBitmap(0, 0, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        delay(_DELAY);

        d.clearDisplay();
        d.drawBitmap(0, 10, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        delay(_DELAY);

        d.clearDisplay();
        d.drawBitmap(0, 0, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        delay(_DELAY);

        d.clearDisplay();
        d.drawBitmap(0, -10, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        delay(_DELAY);
    }
}

/*
*   NÃO
*/
void nao(){
     for (byte i = 0; i < 5; i++)
    {
        d.clearDisplay();
        d.drawBitmap(0, 0, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        delay(_DELAY2);

        d.clearDisplay();
        d.drawBitmap(15, 0, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        delay(_DELAY2);

        d.clearDisplay();
        d.drawBitmap(0, 0, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        delay(_DELAY2);

        d.clearDisplay();
        d.drawBitmap(-15, 0, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        delay(_DELAY2);        
    }
}


#endif