#include <Arduino.h>

#include "GerenciadorSono.h"
#include "Interrupcao.h"
#include "Sensor.h"
#include "Display.h"
#include "Memoria.h"

// Variáveis globais ----------------
byte segundos = 0;
byte nivel_luz = 2;
byte situacao = 0;
byte estado_bateria = 2;
boolean perguntou = false;
boolean deep_sleep = false;
boolean display_inicializado = false;
boolean salvou = false;

// Setup Geral ------------------------
void setup()
{
  Serial.begin(9600);

  display_inicializado = inicializarDisplay();

  if (display_inicializado)
  {
    Serial.println("Display inicializado com sucesso!");
    displayON();
    reduzirBrilho(true);
    limpar();
    show();
  }
  else
    Serial.println("Falha ao inicializar o display");

  Serial.println("");

  configGeral();
  Serial.print("Tempo decorrido até a bateria acabar: ");
  Serial.print(recuperarTempo(0));
  Serial.println(" segundos");
  Serial.println("");
}

void loop()
{

  while (deep_sleep)
  {
    for (size_t i = 0; i < 10; i++)
    {
      dormirPorBateriaFraca();
    }

    estado_bateria = leituraTensaoBateria();

    if (estado_bateria == BATERIA_BOA)
    {
      deep_sleep = false;
      displayON();
      limpar();
      show();
      habilitarInterrupcaoTimer();
      habilitarInterrupcaoExterna();
    }
  }

  switch (estado_bateria)
  {
  case BATERIA_DESCARREGADA:
    if (salvou == false)
    {
      desabilitarInterrupcaoTimer();
      desabilitarInterrupcaoExterna();
      limpar();
      show();
      displayOFF();
      salvarTempo(0, millis() / 1000);
      salvou = true;
      deep_sleep = true;
    }
    break;
  case BATERIA_FRACA:
    bateriaFraca();
    break;
  case BATERIA_BOA:
    if (nivel_luz == CLARO || nivel_luz == MUITO_CLARO)
    {
      if (display_inicializado)
      {
        switch (situacao)
        {
        case 0:
          acordada();
          break;
        case 1:
          acordada();
          break;
        case 2:
          acordada();
          break;
        case 3:
          acordada();
          break;
        case 4:
          feliz();
          break;
        case 5:
          feliz();
          break;
        case 6:
          feliz();
          break;
        case 7:
          desconfiada();
          break;
        case 8:
          desconfiada();
          break;
        case 9:
          brava();
          break;
        case 10:
          piscada();
          break;
        case 11:
          piscada();
          break;
        default:
          break;
        }
      }
      break;
    }
    else
    {
      unsigned long tempo_corrente = millis();
      sonolenta();
      while (nivel_luz == ESCURO && estado_bateria == BATERIA_BOA)
      {
        dormindo();
        if ((millis() - tempo_corrente) / 1000 >= 3600)
        {
          tempo_corrente = millis();

          if (nivel_luz == ESCURO)
          {
            desabilitarInterrupcaoTimer();
            desabilitarInterrupcaoExterna();
            limpar();
            show();
            displayOFF();
          }

          while (nivel_luz == ESCURO)
          {
            for (size_t i = 0; i < 10; i++)
            {
              dormirPorBateriaFraca();
            }

            nivel_luz = leituraNivelLuz();

            if (nivel_luz == CLARO || nivel_luz == MUITO_CLARO)
            {
              deep_sleep = false;
              displayON();
              limpar();
              show();
              habilitarInterrupcaoTimer();
              habilitarInterrupcaoExterna();
            }
          }
        }
      }
      sonolenta();
    }
  }

  if (perguntou)
  {
    perguntou = false;
    byte op = random(0, 2);
    if (op == 1)
      sim();
    else
      nao();
  }
}

/* 
*  Rotina de interrupção do watchdog 
*/
ISR(WDT_vect)
{
  wdt_reset(); // reset do WatchDog
}

/* 
*  Rotina de interrupção enxterna do pino 2 INT0 
*/
ISR(INT0_vect)
{
  perguntou = true;
}

/* 
*  Rotina de interrupção do timer1
*/
ISR(TIMER1_OVF_vect)
{
  TCNT1 = 0xC2F7; // Renicia TIMER
  segundos++;
  if (segundos % 5 == 0)
  {
    estado_bateria = leituraTensaoBateria();
    nivel_luz = leituraNivelLuz();
    situacao = random(0, 12);

    Serial.print("tempo: ");
    Serial.print(millis() / 1000);
    Serial.print(" segundos\ntensão: ");
    Serial.print(tensaoBateria());
    Serial.print("\nsituação: ");
    Serial.print(situacao);
    Serial.print("\nLuz: ");
    Serial.println(nivelLuz());
    Serial.print("\n");
  }

  if (segundos >= 60)
    segundos = 0;
}