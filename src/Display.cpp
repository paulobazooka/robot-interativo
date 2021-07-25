#include "Display.h"

Display::~Display() {}

Display::Display() {}

Display::Display(Adafruit_SSD1306 *d)
{
    display = d;
    if (!display->begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }

    Serial.println("Display iniciado com sucesso!");
    /* display->clearDisplay();
    display->display(); */
}

/*
*   Display ON
*/
void Display::displayON()
{
    Serial.println("Ligar display");
    display->displayON();
}

/*
*   Display ON
*/
void Display::displayOFF()
{
    Serial.println("Desligar display");
    display->displayOFF();
}

/*
*   Display clear
*/
void Display::limpar()
{
    Serial.println("Limpar display");
    display->clearDisplay();
}

/*
*   Display ON
*/
void Display::show()
{
    Serial.println("Show display");
    display->display();
}

/*
*   Reduzir brilho
*/
void Display::reduzirBrilho(boolean reduzir)
{
    Serial.print("Reduzir brilho? ");
    Serial.println(reduzir == 1 ? "SIM" : "NÃO");
    display->dim(reduzir);
}

/*
*   Bateria fraca
*/
void Display::bateriaFraca()
{
    display->clearDisplay();
    display->drawBitmap(0, 0, BATERIA_FRACA_1, 128, 64, WHITE);
    display->display();
    delay(DELAY);

    display->clearDisplay();
    display->drawBitmap(0, 0, BATERIA_FRACA_2, 128, 64, WHITE);
    display->display();
    delay(DELAY);
}

/*    
 *  Acordada 
 */
void Display::acordada()
{
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

/*    
 *  Desconfiada 
 */
void Display::desconfiada()
{
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

/*
*   Dormindo
*/
void Display::dormindo()
{
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

/*
*   Sonolenta
*/
void Display::sonolenta()
{
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

/*
*   Brava
*/
void Display::brava()
{
    display->clearDisplay();
    display->drawBitmap(0, 0, OLHOS_CERRADOS, 128, 64, WHITE);
    display->display();
    delay(2000);

    display->clearDisplay();
    display->drawBitmap(0, 0, OLHOS_FECHADOS, 128, 64, WHITE);
    display->display();
}

/*
*   Piscada
*/
void Display::piscada()
{
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

/*
*   Feliz
*/
void Display::feliz()
{
    display->clearDisplay();
    display->drawBitmap(0, 0, OLHOS_ABERTOS, 128, 64, WHITE);
    display->display();
    delay(1000);
    display->clearDisplay();
    display->drawBitmap(0, 0, OLHOS_SORRIDENTES, 128, 64, WHITE);
    display->display();
    delay(1500);
}

/*
*   SIM
*/
void Display::sim(){
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

/*
*   NÃO
*/
void Display::nao(){
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