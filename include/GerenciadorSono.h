#ifndef GERENCIADOR_SONO_H
#define GERENCIADOR_SONO_H

#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>


class GerenciadorSono
{
private:
    byte dormindo;
    void configWatchDog8Segundos();
    void funcaoGerenciadorSono(unsigned long tempoSono);
public:
    GerenciadorSono();
    ~GerenciadorSono();
    void dormirComDespertador();
    void dormirPorBateriaFraca();
};

#endif