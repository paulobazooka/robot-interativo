#ifndef GERENCIADOR_SONO_H
#define GERENCIADOR_SONO_H

#include <avr/wdt.h>
#include <avr/sleep.h>

/*----------------------------------------------------------------
  Função para dormir o microcontrolador
  tempoSono [segundos]
-----------------------------------------------------------------*/
void sonoProfundo(int tempoSono)
{
  cli();                          // desabilita globalmente as interrupções
  MCUSR = 0;                      // clear reset status
  WDTCSR |= 0b00011000;           // WDCE y WDE = 1 --> config mode
  WDTCSR = 0b01000000 | 0b100001; // set WDIE (interrupt mode enabled), clear WDE (reset mode disabled) and set interval to 8 seconds
  sei();                          // habilita globalmente as interrupções
  
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