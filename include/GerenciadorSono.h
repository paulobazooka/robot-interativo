#ifndef GERENCIADOR_SONO_H
#define GERENCIADOR_SONO_H

#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

/*----------------------------------------------------------------
  Função para dormir o microcontrolador
  tempoSono [segundos]
-----------------------------------------------------------------*/
void sonoProfundo(long tempoSono)
{
  for (int i = 0; i < round((float)tempoSono / 8); i++)
  {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
  }
  wdt_disable();
}

#endif