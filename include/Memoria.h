#include <Arduino.h>
#include <EEPROM.h>

void salvarTempo(byte posicao, unsigned int valor)
{

    if (posicao < 200)
    {
        byte pos = posicao * 4;
        byte buf[4];
        buf[pos] = (byte)valor;
        buf[pos + 1] = (byte)valor >> 8;
        buf[pos + 2] = (byte)valor >> 16;
        buf[pos + 3] = (byte)valor >> 24;

        for (size_t i = 0; i < 4; i++)
        {
            EEPROM.write(i, buf[i]);
        }
    }
}

unsigned int recuperarTempo(byte posicao)
{
    if (posicao < 200)
    {
        byte pos = posicao * 4;
        unsigned long tempo = (EEPROM.read(pos + 3) << 24) | (EEPROM.read(pos + 2) << 16) | (EEPROM.read(pos + 1) << 8) | EEPROM.read(pos);
        return tempo;
    }
    else
    {
        return 0;
    }
}