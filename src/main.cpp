/* =================================================================
*   Projeto:    Robô interativo Daise
*   Autor:      Paulo Sérgio do Nascimento
*   Plataforma: Arduino Mini Pro 5V
*   Ano:        2021
*   Versão:     1.1
* =================================================================*/
#include <Arduino.h>

#include "GerenciadorSono.h"
#include "Interrupcao.h"
#include "Sensor.h"
#include "Display.h"
#include "Memoria.h"
#include "Som.h"

// Variáveis globais ----------------
byte segundos = 0;
byte nivel_luz = 2;
byte situacao = 0;
byte estado_bateria = 2;
boolean perguntou = false;
boolean deep_sleep = false;
boolean display_inicializado = false;
unsigned long tempo_exibir_dados_hardware;

// Setup Geral ------------------------
void setup()
{
  Serial.begin(9600);

  display_inicializado = inicializarDisplay();
  configGeral();
  somOFF();

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
}

void loop()
{

  switch (estado_bateria)
  {
  case BATERIA_DESCARREGADA:
    desabilitarInterrupcaoTimer();
    desabilitarInterrupcaoExterna();
    limpar();
    show();
    displayOFF();

    while (estado_bateria != BATERIA_BOA)
    {
      sonoProfundo(120);
      estado_bateria = leituraTensaoBateria();
    }

    perguntou = false;
    displayON();
    limpar();
    show();
    habilitarInterrupcaoTimer();
    habilitarInterrupcaoExterna();
    break;

  case BATERIA_FRACA:
    bateriaFraca();
    // Se passou o tempo passou de 3 segundos e o botão de interrupção continua pressionado
    if ((millis() - tempo_exibir_dados_hardware) >= 3000 && (digitalRead(2) == LOW))
    {
      imprimirDadosHardware((millis() / 1000) / 60, tensaoBateria(), nivelLuz());
      delay(10000);
    }
    break;

  case BATERIA_BOA:
    if (nivel_luz == CLARO || nivel_luz == MUITO_CLARO)
    {
      if (display_inicializado)
      {
        // Se passou o tempo passou de 3 segundos e o botão de interrupção continua pressionado
        if ((millis() - tempo_exibir_dados_hardware) >= 3000 && (digitalRead(2) == LOW))
        {
          imprimirDadosHardware((millis() / 1000) / 60, tensaoBateria(), nivelLuz());
          delay(10000);
        }

        switch (situacao)
        {
        case 0:
          feliz();
          break;
        case 1:
          feliz();
          break;
        case 2:
          feliz();
          break;
        case 3:
          desconfiada();
          break;
        case 4:
          desconfiada();
          break;
        case 5:
          brava();
          break;
        case 6:
          piscada();
          break;
        case 7:
          piscada();
          break;
        default:
          acordada();
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
        // Tempo dormindo até entrar em deep sleep...
        if ((millis() - tempo_corrente) / 1000 >= (60 * 30)) // após meia hora...
        {
          if (nivel_luz == ESCURO) // verifica se está escuro ainda...
          {
            desabilitarInterrupcaoTimer();
            desabilitarInterrupcaoExterna();
            limpar();
            show();
            displayOFF();
          }

          while (nivel_luz == ESCURO) // Entra em deep sleep
          {

            sonoProfundo(60);              // Dormir por 60 segundos
            nivel_luz = leituraNivelLuz(); // medir nível de luz

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

          perguntou = false;
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

/* =================================================================
*
* Rotina de interrupção WatchDog
*
* =================================================================*/
ISR(WDT_vect)
{
  wdt_reset(); // reset do WatchDog
}

/* =================================================================
*
* Rotina de interrupção enxterna do pino 2 INT0 
*
* =================================================================*/
ISR(INT0_vect)
{
  tempo_exibir_dados_hardware = millis();
  perguntou = true;
}

/* =================================================================
*
* Rotina de interrupção Timer1 
*
* =================================================================*/
ISR(TIMER1_OVF_vect)
{
  TCNT1 = 0xC2F7; // Renicia TIMER
  segundos++;
  if (segundos % 5 == 0)
  {
    estado_bateria = leituraTensaoBateria();
    nivel_luz = leituraNivelLuz();
    situacao = random(0, 21);
  }

  if (segundos >= 60)
    segundos = 0;
}