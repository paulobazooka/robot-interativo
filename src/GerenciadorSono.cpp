#include "GerenciadorSono.h"

GerenciadorSono::GerenciadorSono(/* args */)
{
}

GerenciadorSono::~GerenciadorSono()
{
}

void GerenciadorSono::dormirComDespertador()
{
  Serial.println("Indo dormir com hora pra acordar com o despertador...");
  delay(100);
  funcaoGerenciadorSono(20);
}

void GerenciadorSono::dormirPorBateriaFraca()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
}

void GerenciadorSono::funcaoGerenciadorSono(unsigned long tempoSono)
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
