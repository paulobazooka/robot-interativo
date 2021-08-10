#ifndef SOM_H
#define SOM_H

void somON()
{
    PORTD |= (1 << PORTD4);
}

void somOFF()
{
    PORTD &= ~(1 << PORTD4);
}

#endif