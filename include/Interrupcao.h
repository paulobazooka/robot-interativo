#ifndef INTERRUPCAO_H
#define INTERRUPCAO_H

#include <avr/interrupt.h>

class Interrupcao
{
private:
   
public:
    Interrupcao();
    ~Interrupcao();
    void configurarInterrupcaoTimer();
    void habilitarInterrupcaoTimer();
    void desabilitarInterrupcaoTimer();
    void configurarInterrupcaoExterna();
    void habilitarInterrupcaoExterna();
    void desabilitarInterrupcaoExterna();
    void configurarInterrupcaoWatchDog();
};

#endif