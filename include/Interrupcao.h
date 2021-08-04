#ifndef INTERRUPCAO_H
#define INTERRUPCAO_H

#include <Arduino.h>
#include <avr/interrupt.h>

void habilitarInterrupcaoTimer()
{
    TIMSK1 |= (1 << TOIE1); // desabilita a interrupção do TIMER1
}

void desabilitarInterrupcaoTimer()
{
    TIMSK1 &= ~(1 << TOIE1); // desabilita a interrupção do TIMER1
}

void habilitarInterrupcaoExterna()
{
    EIMSK |= (1 << INT0); // desabilita a interrupção no pino 2 on INT0
}

void desabilitarInterrupcaoExterna()
{
    EIMSK &= ~(1 << INT0); // desabilita a interrupção no pino 2 on INT0
}

void configGeral()
{

    DDRD |= (1 << DDD4);                 // Limpar o pino PD4, PD4 como saida

    DDRD &= ~(1 << DDD2);                 // Limpar o pino PD2, PD2 como entrada
    PORTD |= (1 << PORTD2);               // liga o pull-up
    EICRA |= (1 << ISC01) | (0 << ISC00); // configura interrupção externa int 0 - FALLING
    EIMSK |= (1 << INT0);                 // habilita a interrupção no pino 2 on INT0

    TCCR1A = 0;                          //confira timer para operação normal pinos OC1A e OC1B desconectados
    TCCR1B = 0;                          //limpa registrador
    TCCR1B |= (1 << CS10) | (1 << CS12); // configura prescaler para 1024: CS12 = 1 e CS10 = 1
    TCNT1 = 0xC2F7;                      // incia timer com valor para que estouro ocorra em 1 segundo 65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
    TIMSK1 |= (1 << TOIE1);              // habilita a interrupção do TIMER1

    MCUSR = 0;                      // clear reset status
    WDTCSR |= 0b00011000;           // WDCE y WDE = 1 --> config mode
    WDTCSR = 0b01000000 | 0b100001; // set WDIE (interrupt mode enabled), clear WDE (reset mode disabled) and set interval to 8 seconds
    sei();                          // habilita globalmente as interrupções

    analogReference(INTERNAL);
}
#endif