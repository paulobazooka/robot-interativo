#ifndef TELA_H
#define TELA_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Olhos.h"
#include "Bateria.h"
#include "Som.h"

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
    d.displayON();
}

/*
*   Display ON
*/
void displayOFF()
{
    d.displayOFF();
}

/*
*   Display clear
*/
void limpar()
{
    d.clearDisplay();
}

/*
*   Display ON
*/
void show()
{
    d.display();
}

/*
*   Reduzir brilho
*/
void reduzirBrilho(boolean reduzir)
{
    d.dim(reduzir);
}


void imprimirDadosHardware(int tempo, float tensao, byte nivel_luz, int tempo_bateria){
    
    d.clearDisplay();
    d.display();
    d.setTextColor(WHITE);
    d.setTextSize(1);
    d.setCursor(0,0);
    
    d.print("Tempo: ");
    d.print(tempo);
    d.println(" minutos");

    d.print("Bateria: ");
    d.print(tempo_bateria);
    d.println(" minutos");

    d.print("Tensao: ");
    d.print(tensao);
    d.println(" volts");

    d.print("Luz: ");
    d.println(nivel_luz);
    
    d.display();
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
void sim()
{
    for (byte i = 0; i < 5; i++)
    {
        d.clearDisplay();
        d.drawBitmap(0, 0, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        somON();
        delay(_DELAY);

        d.clearDisplay();
        d.drawBitmap(0, 10, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        delay(_DELAY);

        d.clearDisplay();
        d.drawBitmap(0, 0, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        somOFF();
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
void nao()
{
    for (byte i = 0; i < 5; i++)
    {
        d.clearDisplay();
        d.drawBitmap(0, 0, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        somON();
        delay(_DELAY2);

        d.clearDisplay();
        d.drawBitmap(15, 0, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        somOFF();
        delay(_DELAY2);

        d.clearDisplay();
        d.drawBitmap(0, 0, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        somON();
        delay(_DELAY2);

        d.clearDisplay();
        d.drawBitmap(-15, 0, OLHOS_CENTRO, 128, 64, WHITE);
        d.display();
        somOFF();
        delay(_DELAY2);
    }
}

#endif