#include <Arduino.h>
#include <avr/interrupt.h>

#include "Display.h"
#include "GerenciadorSono.h"
#include "Interrupcao.h"

// Definições -------------------------
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4     // Reset pin # (or -1 if sharing Arduino reset pin)
#define LDR1 A0          // pino leitura analógica do primeiro LDR
#define LDR2 A1          // pino leitura analógica do segundo LDR
#define BATTERY_PIN A3   // pino de leitura de tensão

#define BATTERY_HIGH 2   // status da bateria carregada
#define BATTERY_LOW 1    // status da bateria descarregada
#define BATTERY_DANGER 0 // status da bateria crítico

#define PINO_INTERRUPCAO 2 // pino de interrupção

// Variáveis Globais ------------------
unsigned int ldr1 = 100;
unsigned int ldr2 = 100;
unsigned int ldrTotal = 100;
unsigned int segundos = 0;
byte batteryStatus = 2;
boolean claro = true;
unsigned int situacao = 0; // Quando acordado, 0 = normal, 1 = desconfiada ...
float tensao = 0.0;
float maiorTensao = 0.0;
const byte NUMERO_AMOSTRAS_TENSAO = 10;
boolean perguntou = false;
boolean deep_sleep = false;

// Objetos ----------------------------
Adafruit_SSD1306 d(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Display display;
GerenciadorSono mestreDosSonhos;
Interrupcao interrupcao;

// Declaração de funções --------------
void lerSensores();
void medirTensao();
void acordado();
void dormindo();
void sonolento();
void responderPergunta();
void sonoProfundo();

// Setup Geral ------------------------
void setup()
{
  Serial.begin(9600);

  interrupcao.configurarInterrupcaoTimer();
  interrupcao.habilitarInterrupcaoTimer();

  interrupcao.configurarInterrupcaoExterna();
  interrupcao.habilitarInterrupcaoExterna();

  interrupcao.configurarInterrupcaoWatchDog();

  analogReference(INTERNAL);

  display = Display(&d);
  display.displayON();
  display.reduzirBrilho(false);
  display.limpar();
  display.show();
}

void loop()
{
  /* if (batteryStatus == BATTERY_DANGER)
    sonoProfundo();*/

  while (batteryStatus == BATTERY_LOW)
    display.bateriaFraca();

  while (batteryStatus == BATTERY_HIGH)
  {
    if (!claro)
    {
      display.sonolenta();
      display.reduzirBrilho(true);
      while (!claro && batteryStatus == BATTERY_HIGH)
        display.dormindo();

      display.sonolenta();
      display.reduzirBrilho(false);
    }

    while (claro && batteryStatus == BATTERY_HIGH && perguntou == false)
    {
      switch (situacao)
      {
      case 0:
        display.acordada();
        break;
      case 1:
        display.acordada();
        break;
      case 2:
        display.acordada();
        break;
      case 3:
        display.acordada();
        break;
      case 4:
        display.feliz();
        break;
      case 5:
        display.feliz();
        break;
      case 6:
        display.feliz();
        break;
      case 7:
        display.desconfiada();
        break;
      case 8:
        display.desconfiada();
        break;
      case 9:
        display.brava();
        break;
      case 10:
        display.piscada();
        break;
      case 11:
        display.piscada();
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
        display.sim();
      else
        display.nao();
    }
  }
}

void lerSensores()
{
  ldr1 = analogRead(LDR1);
  ldr2 = analogRead(LDR2);
  ldrTotal = (ldr1 + ldr2) / 2;
  if (ldrTotal <= 10)
    claro = false;
  else
    claro = true;
}


// Rotina de interrupção do watchdog
ISR(WDT_vect)
{
  wdt_reset();  // reset do WatchDog
}

// Rotina de interrupção enxterna do pino 2 INT0
ISR(INT0_vect)
{
  if (deep_sleep == false && claro == true)
    perguntou = true;
  else
  {
    batteryStatus = 2;
    deep_sleep = false;
  }
}

//  Rotina de interrupção do timer1
ISR(TIMER1_OVF_vect)
{
  TCNT1 = 0xC2F7; // Renicia TIMER
  segundos++;

  if (segundos % 7 == 0)
  {
    lerSensores();
    medirTensao();
  }

  if (segundos % 5 == 0)
    situacao = random(0, 12);

  if (segundos > 1000)
    segundos = 0;

  if (segundos % 17 == 0)
  {
    Serial.print("tempo: ");
    Serial.print(millis() / 1000);
    Serial.print(" segundos\ttensão: ");
    Serial.print(tensao);
    Serial.print("\tmaior tensão: ");
    Serial.print(maiorTensao);
    Serial.print("\nsituação: ");
    Serial.print(situacao);
    Serial.print("\nclaro: ");
    Serial.print(claro);
    Serial.print("\tLDR 1: ");
    Serial.print(ldr1);
    Serial.print("\tLDR 2: ");
    Serial.print(ldr2);
    Serial.print("\tLDR TOTAL: ");
    Serial.println(ldrTotal);
  }
}


void medirTensao()
{
  float total = 0.0;

  for (byte i = 0; i < NUMERO_AMOSTRAS_TENSAO; i++)
  {
    total += analogRead(BATTERY_PIN);
    delay(5);
  }

  float read = (total / NUMERO_AMOSTRAS_TENSAO);
  tensao = ((read * 6.074) / 1024);

  if (tensao > maiorTensao)
    maiorTensao = tensao;

  if (tensao >= 3.4)
    batteryStatus = BATTERY_HIGH;
  else if (tensao < 3.1 && tensao >= 3)
    batteryStatus = BATTERY_LOW;
  /* else if (tensao < 3)
    batteryStatus = BATTERY_DANGER;*/
}

void responderPergunta()
{
  if (deep_sleep == false && claro == true)
    perguntou = true;
  else
  {
    batteryStatus = 2;
    deep_sleep = false;
  }
}

void sonoProfundo()
{
  deep_sleep = true;
  display.limpar();
  display.show();
  display.displayOFF();
  mestreDosSonhos.dormirPorBateriaFraca();
  display.displayON();
  display.reduzirBrilho(false);
}