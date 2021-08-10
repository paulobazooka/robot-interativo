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
        buf[pos + 2] = (byte)valor >> 8 >> 8;
        buf[pos + 3] = (byte)valor >> 8 >> 8 >> 8;

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
        unsigned long tempo = (EEPROM.read(pos + 3) << 8 << 8 << 8) | (EEPROM.read(pos + 2) << 8 << 8) | (EEPROM.read(pos + 1) << 8) | EEPROM.read(pos);
        return tempo;
    }

    return 0;
}