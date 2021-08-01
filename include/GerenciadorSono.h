#ifndef GERENCIADOR_SONO_H
#define GERENCIADOR_SONO_H

#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

void funcaoGerenciadorSono(unsigned long tempoSono)
{
  for (byte i = 0; i < 5; i++)
  {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
  }
  wdt_disable();
}

void dormirComDespertador()
{
  Serial.println("Indo dormir com hora pra acordar com o despertador...");
  funcaoGerenciadorSono(20);
}

void dormirPorBateriaFraca()
{
  Serial.println("Hibernar feito urso...");
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable(); 
}

#endif