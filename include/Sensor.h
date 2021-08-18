#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

#define LDR1 A0                   // pino leitura analógica do primeiro LDR
#define LDR2 A1                   // pino leitura analógica do segundo LDR
#define PINO_BATERIA A3           // pino de leitura de tensão
#define NUMERO_AMOSTRAS_TENSAO 10 // define o numero de amostras para leitura de tensão bateria

unsigned int valorADC;
double temperatura;
unsigned int ldr1 = 100;
unsigned int ldr2 = 100;
unsigned int ldrTotal = 100;
float tensao = 0.0;
const byte ESCURO = 0;
const byte CLARO = 1;
const byte MUITO_CLARO = 2;
const byte BATERIA_DESCARREGADA = 0;
const byte BATERIA_FRACA = 1;
const byte BATERIA_BOA = 2;

void configurarLeituraAnalogica()
{
    delay(20);
    analogReference(INTERNAL);
}

byte leituraNivelLuz()
{
    ldr1 = analogRead(LDR1);
    ldr2 = analogRead(LDR2);
    ldrTotal = (ldr1 + ldr2) / 2;

    if (ldrTotal <= 20)
        return ESCURO;

    if (ldrTotal > 20 && ldrTotal <= 31)
        return CLARO;

    return MUITO_CLARO;
}

byte leituraTensaoBateria()
{
    float total = 0.0;

    for (byte i = 0; i < NUMERO_AMOSTRAS_TENSAO; i++)
    {
        total += analogRead(PINO_BATERIA);
        delay(10);
    }

    tensao = (((total / NUMERO_AMOSTRAS_TENSAO) * 6.074) / 1024);

    if (tensao >= 3.2)
        return BATERIA_BOA;

    if (tensao < 3.2 && tensao >= 3)
        return BATERIA_FRACA;

    return BATERIA_DESCARREGADA;
}

float tensaoBateria()
{
    return tensao;
}

unsigned int nivelLuz()
{
    return ldrTotal;
}

#endif