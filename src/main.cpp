#include <Arduino.h>
#include <avr/interrupt.h>

#include "GerenciadorSono.h"
#include "Interrupcao.h"
#include "Sensor.h"
#include "Display.h"

// Variáveis globais ----------------
byte segundos = 0;
byte nivel_luz = 2;
byte situacao = 0;
byte estado_bateria = 2;
boolean perguntou = false;
boolean deep_sleep = false;

// Objetos ----------------------------
Sensor sensor;
Interrupcao interrupcao;
GerenciadorSono mestreDosSonhos;


// Setup Geral ------------------------
void setup()
{
  Serial.begin(9600);
  delay(100);

  if (inicializarDisplay())
  {
    Serial.println("Display inicializado com sucesso!");
    displayON();
    reduzirBrilho(true);
    limpar();
    show();
  }

  interrupcao.configurarInterrupcaoTimer();
  interrupcao.habilitarInterrupcaoTimer();

  interrupcao.configurarInterrupcaoExterna();
  interrupcao.habilitarInterrupcaoExterna();

  interrupcao.configurarInterrupcaoWatchDog();

  sensor.configurarLeituraAnalogica();
}

void loop()
{
  acordada();
  if (estado_bateria == sensor.BATERIA_DESCARREGADA)
    mestreDosSonhos.dormirPorBateriaFraca();

  while (estado_bateria == sensor.BATERIA_FRACA)
    bateriaFraca();

   while (estado_bateria == sensor.BATERIA_BOA)
  {

    if (nivel_luz == sensor.ESCURO) // Entra no laço de sono
    {
      while ((nivel_luz == sensor.CLARO || nivel_luz == sensor.MUITO_CLARO) && estado_bateria == sensor.BATERIA_BOA)  // permanece no sono até ficar claro
        dormindo();
    }

    while ((nivel_luz == sensor.CLARO || nivel_luz == sensor.MUITO_CLARO) && estado_bateria == sensor.BATERIA_BOA && perguntou == false)
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

  if (segundos > 60)
    segundos = 0;

  if (segundos % 7 == 0)
  {
    estado_bateria = sensor.leituraTensaoBateria();

    nivel_luz = sensor.leituraNivelLuz();

    /* if (nivel_luz == sensor.MUITO_CLARO)
      reduzirBrilho(false);
    else
      reduzirBrilho(true);*/
  }

  if (segundos % 5 == 0)
    situacao = random(0, 12);

  if (segundos % 17 == 0)
  {
    Serial.print("tempo: ");
    Serial.print(millis() / 1000);
    Serial.print(" segundos\ntensão: ");
    Serial.print(sensor.tensaoBateria());
    Serial.print("\nsituação: ");
    Serial.print(situacao);
    Serial.print("\nLuz: ");
    Serial.println(sensor.nivelLuz());
    Serial.println("");
  }
}