#include "Sensor.h"

Sensor::Sensor(){
};
Sensor::~Sensor(){};

void Sensor::configurarLeituraAnalogica()
{
   Serial.println("Configurando a referência interna leitura analógica...");
   delay(20);
   analogReference(INTERNAL);
}

byte Sensor::leituraNivelLuz()
{
   ldr1 = analogRead(LDR1);
   ldr2 = analogRead(LDR2);
   ldrTotal = (ldr1 + ldr2) / 2;

   if (ldrTotal <= 10)
      return ESCURO;

   if (ldrTotal > 10 && ldrTotal <= 30)
      return CLARO;

   return MUITO_CLARO;
}

byte Sensor::leituraTensaoBateria()
{
   float total = 0.0;

   for (byte i = 0; i < NUMERO_AMOSTRAS_TENSAO; i++)
   {
      total += analogRead(PINO_BATERIA);
      delay(10);
   }

   tensao = (((total / NUMERO_AMOSTRAS_TENSAO) * 6.074) / 1024);

   if (tensao >= 3.1)
      return BATERIA_BOA;

   if (tensao < 3.1 && tensao >= 3)
      return BATERIA_FRACA;

   return BATERIA_DESCARREGADA;
}

float Sensor::tensaoBateria()
{
   return tensao;
}

unsigned int Sensor::nivelLuz()
{
   return ldrTotal;
}
