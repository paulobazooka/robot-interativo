#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

#define LDR1 A0                   // pino leitura analógica do primeiro LDR
#define LDR2 A1                   // pino leitura analógica do segundo LDR
#define PINO_BATERIA A3            // pino de leitura de tensão
#define NUMERO_AMOSTRAS_TENSAO 10 // define o numero de amostras para leitura de tensão bateria

class Sensor
{
private:
    unsigned int valorADC;
    double temperatura;
    unsigned int ldr1 = 100;
    unsigned int ldr2 = 100;
    unsigned int ldrTotal = 100;
    float tensao = 0.0;

public:
    Sensor();
    ~Sensor();
    const byte ESCURO = 0;
    const byte CLARO = 1;
    const byte MUITO_CLARO = 2;
    const byte BATERIA_DESCARREGADA = 0;
    const byte BATERIA_FRACA = 1;
    const byte BATERIA_BOA = 2;
    byte leituraNivelLuz();
    byte leituraTensaoBateria();
    void configurarLeituraAnalogica();
    float tensaoBateria();
    unsigned int nivelLuz();
};

#endif