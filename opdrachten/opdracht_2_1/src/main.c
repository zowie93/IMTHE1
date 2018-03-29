/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 2 - Count me in
 * Datum: 21-02-2018
 */

#include <avr/io.h>
#include <util/delay.h>

#define DELAY_TIME_MS 500
/*
* ---- DIGIT RIGHT ----
*        --------- 
*       | A = PD2 |
*        ---------
* ------           ----- 
*| F   |          | B   |
*| =   |          | =   |
*| PC1 |          | PD3 |
* -----            -----
*        --------- 
*       | G = PC2 |
*        ---------
* ------           ----- 
*| E   |          | C   |
*| =   |          | =   |
*| PC0 |          | PD4 |
* -----            -----
*        --------- 
*       | D = PC5 |
*        ---------
*/

// Functie voor de C poort met integer in de callback
void useCport (int digit) {
    // Poort C gebruikt input van digit die bitshift die 4 keer naar links en 8 keer naar rechts zodat die leeg begint en dan met de bitwise operator NOT draai ik ze om
    PORTC =~ (((digit) << 4) >> 8);
}

// Functie voor de D poort met integer in de callback
void useDport (int digit) {
    // Poort D gebruikt input van digit die bitshift die 4 keer naar links en 8 keer naar rechts zodat die leeg begint en dan met de bitwise operator NOT draai ik ze om
    PORTD =~ (((digit) << 8) >> 6);
}

int main(void)
{
    // Zet alle pinnen van de C bank aan
    DDRC = 0b11111111;

    // Zet alle pinnen van de D bank aan
    DDRD = 0b11111111;

    // teller van i op 0
    int i = 0;

    // Alle digits in een array
    int digits[10] = {
        0b00111111, // digit 0
        0b00000110, // digit 1
        0b01011011, // digit 2
        0b01001111, // digit 3
        0b01100110, // digit 4
        0b01101101, // digit 5
        0b01111101, // digit 6
        0b00000111, // digit 7
        0b01111111, // digit 8
        0b01101111  // digit 9

    };

    // While loop
    while (1)
    {
        // Functie om de C poort te gebruiken die teller modulo array van alle digits doorloopt
        useCport(digits[i % 10]);

        // Functie om de D poort te gebruiken die teller modulo array van alle digits doorloopt
        useDport(digits[i % 10]);
        
        // Delay van het tellen defineerd bij DEFINE
        _delay_ms(DELAY_TIME_MS);

        // Teller van i ++
        i++;
    }

    return 0;
}
