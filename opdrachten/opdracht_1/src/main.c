/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 1 - Blink once to accept
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Pin D5 & D6 zijn de output pins voor de leds
    DDRD = 0b01100000;

    while (1)
    {
        PORTD ^= 1 << 5;
        _delay_ms(1200);
        PORTD ^= 1 << 6;
    }

    return 0;
}
