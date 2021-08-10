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
boolean salvou = false;
unsigned long tempo_exibir_dados_hardware;
unsigned int temp;

// Funções --------------------------
void exibirDadosHardware();

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

  temp = recuperarTempo(0);
}

void loop()
{

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
      salvarTempo(0, (millis() / 1000) / 60);
      salvou = true;

      while (estado_bateria == BATERIA_DESCARREGADA)
      {
        sonoProfundo(120); // Dormir por 120 segundos
        estado_bateria = leituraTensaoBateria();
      }

      displayON();
      limpar();
      show();
      habilitarInterrupcaoTimer();
      habilitarInterrupcaoExterna();
    }
    break;
  case BATERIA_FRACA:
    bateriaFraca();
    // Se passou o tempo passou de 3 segundos e o botão de interrupção continua pressionado
    if ((millis() - tempo_exibir_dados_hardware) >= 3000 && (digitalRead(2) == LOW))
    {
      imprimirDadosHardware((millis() / 1000) / 60, tensaoBateria(), nivelLuz(), temp);
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
          imprimirDadosHardware((millis() / 1000) / 60, tensaoBateria(), nivelLuz(), temp);
          delay(10000);
        }

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
        case 12:
          acordada();
          break;
        case 13:
          acordada();
          break;
        case 14:
          acordada();
          break;
        case 15:
          acordada();
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

            sonoProfundo(60); // Dormir por 60 segundos

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
    situacao = random(0, 16);

    /*Serial.print("tempo: ");
    Serial.print(millis() / 1000);
    Serial.print(" segundos\ntensão: ");
    Serial.print(tensaoBateria());
    Serial.print("\nsituação: ");
    Serial.print(situacao);
    Serial.print("\nLuz: ");
    Serial.println(nivelLuz());
    Serial.print("\n");*/
  }

  if (segundos >= 60)
    segundos = 0;
}