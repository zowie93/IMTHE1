/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 1 - Blink once to accept
 * Datum: 15-02-2018
 */

#include <avr/io.h>
#include <util/delay.h>

// Define voor blink delay tijd in ms (1200)
#define DELAY_BLINK_MS 1200

int main(void)
{
    // Pin D5 & D6 zijn de output pins voor de leds
    DDRD = 0b01100000;

    // While loop
    while (1)
    {
        // Zet led aan op D5 en D6 uit indien die aan was
        PORTD ^= 1 << 5;

        // Wacht 1.2 seconden
        _delay_ms(DELAY_BLINK_MS);

        // Zet led uit op D5 en zet led aan op D6
        PORTD ^= 1 << 6;
    }

    return 0;
}
