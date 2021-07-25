#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Olhos.h"
#include "Bateria.h"


class Display
{
private:
    Adafruit_SSD1306 *display;
    unsigned int DELAY = 330;
    unsigned int _DELAY = 35;
    unsigned int _DELAY2 = 30;
public:
    Display(Adafruit_SSD1306 *d);
    Display();
    ~Display();

    void sim();
    void nao();
    void show();
    void feliz();
    void brava();
    void limpar();
    void piscada();
    void dormindo();
    void acordada();
    void sonolenta();
    void displayON();
    void displayOFF();
    void desconfiada();
    void bateriaFraca();
    void reduzirBrilho(boolean reduzir);
};

#endif