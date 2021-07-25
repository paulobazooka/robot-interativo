#include <Arduino.h>

#include <avr/sleep.h>
#include "Display.h"


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

// Declaração de funções --------------
void lerSensores();
void medirTensao();
void acordado();
void dormindo();
void sonolento();
void configuracaoTimer();
void responderPergunta();
void sonoProfundo();

// Setup Geral ------------------------
void setup()
{
  Serial.begin(9600);

  //pinMode(PINO_INTERRUPCAO, INPUT_PULLUP);
  analogReference(INTERNAL);
  configuracaoTimer();
  // attachInterrupt(digitalPinToInterrupt(PINO_INTERRUPCAO), responderPergunta, LOW);
  display = Display(&d);
  display.displayON();
  display.reduzirBrilho(true);
  display.limpar();
  display.show();
}

void loop()
{
  display.acordada();

  /* if (batteryStatus == BATTERY_DANGER)
    sonoProfundo();

  while (batteryStatus == BATTERY_LOW)
    display.bateriaFraca();

  while (batteryStatus == BATTERY_HIGH)
  {
    if (!claro)
    {
      display.sonolenta();
      while (!claro && batteryStatus == BATTERY_HIGH)
        display.dormindo();
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
    }*/

   /* if (perguntou)
    {
      perguntou = false;
      byte op = random(0, 2);
      if (op == 1)
        respostaSIM(&display);
      else
        respostaNAO(&display);
    }
  }*/
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

void configuracaoTimer()
{
  // Configuração do timer1
  TCCR1A = 0;                          //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                          //limpa registrador
  TCCR1B |= (1 << CS10) | (1 << CS12); // configura prescaler para 1024: CS12 = 1 e CS10 = 1

  TCNT1 = 0xC2F7; // incia timer com valor para que estouro ocorra em 1 segundo
                  // 65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7

  TIMSK1 |= (1 << TOIE1); // habilita a interrupção do TIMER1
}

ISR(TIMER1_OVF_vect) //interrupção do TIMER1
{
  TCNT1 = 0xC2F7; // Renicia TIMER
  segundos++;

  if (segundos % 7 == 0)
  {
    // lerSensores();
    medirTensao();
  }

  /*if (segundos % 5 == 0)
    situacao = random(0, 12);*/

  if (segundos > 1000)
    segundos = 0;

  /*Serial.print("situação: ");
  Serial.print(situacao);
  Serial.print("\tclaro: ");
  Serial.print(claro);
  Serial.print("\tLDR 1: ");
  Serial.print(ldr1);
  Serial.print("\tLDR 2: ");
  Serial.print(ldr2);
  Serial.print("\tLDR TOTAL: ");
  Serial.print(ldrTotal);*/

  if (segundos % 13 == 0)
  {
    Serial.print("tempo: ");
    Serial.print(millis()/1000); 
    Serial.print("\ttensão: ");
    Serial.print(tensao);
    Serial.print("\t maior tensão: ");
    Serial.println(maiorTensao);
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
  Serial.println("Dormindo...");
  delay(100);
  /*--- MODO SLEEP PARA REDUÇÃO DO CONSUMO DE ENERGIA ---*/
  //Configura o tipo de sleep (power down)
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  //Habilita a função sleep para que possa ser usada
  sleep_enable();

  //Aciona o modo sleep, para adormecer o microcontrolador
  sleep_mode();

  //Desativa o modo sleep
  sleep_disable();

  Serial.println("Acordando...");
  display.displayON();
}