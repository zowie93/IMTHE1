/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 3 - ADC Baby!
 */

#include <avr/io.h>
#include <util/delay.h>

#define DELAY_TIME_MS 300

// Functie voor middelste led met behulp van bitshiften op de D bank
void one() {
    PORTD ^= 1 << 6;
}

// Functie voor led Linksboven en Rechtsonder met behulp van bitshiften op de D en B bank
void two() {
    PORTD ^= 1 << 3;
    PORTB ^= 1 << 1;
}

// Functie voor Linksboven, Rechtersonder en Middelste led met behulp van bitshiften op de D en B bank
void three() {
    PORTD ^= 1 << 6;
    PORTD ^= 1 << 3;
    PORTB ^= 1 << 1;
}

// Functie voor Linksboven, Rechtsboven, Linksonder en Rechtsonder led met behulp van bitshiften op de D en B bank
void four() {
    PORTD ^= 1 << 3;
    PORTD ^= 1 << 5;
    PORTD ^= 1 << 7;
    PORTB ^= 1 << 1;
}

// Functie voor Linksboven, Rechtsboven, Linksonder, Rechtsonder en Middelste led met behulp van bitshiften op de D en B bank
void five() {
    PORTD ^= 1 << 3;
    PORTD ^= 1 << 5;
    PORTD ^= 1 << 6;
    PORTD ^= 1 << 7;
    PORTB ^= 1 << 1;
}

// Functie voor alle leds behalve de middelste met behulp van bitshiften op de D en B bank
void six() {
    PORTD ^= 1 << 3;
    PORTD ^= 1 << 4;
    PORTD ^= 1 << 5;
    PORTD ^= 1 << 7;
    PORTB ^= 1 << 0;
    PORTB ^= 1 << 1;
}

// Functie voor het opschonen van de bits (op 0 zetten)
void clear() {
    PORTB = 0b00000000;
    PORTD = 0b00000000;

    // De knop zit op PD2 dus die moet blijven
    PORTD = (1 << PD2);
}

// Functie voor random roll tijdens het dobbelen
void randomRoll() {
    // random integer tussen de 1 en de 6
    int number = ((rand() % 6) + 1);
            // switch die de random integer invult en hierbij de case afspeelt
            switch(number) {
                // case 1 spreekt nummer 1 aan
                case 1:
                    one();
                    break;
                // case 2 spreekt nummer 2 aan
                case 2:
                    two();
                    break;
                // case 3 spreekt nummer 3 aan
                case 3:
                    three();
                    break;
                // case 4 spreekt nummer 4 aan
                case 4:
                    four();
                    break;
                // case 5 spreekt nummer 5 aan
                case 5:
                    five();
                    break;
                // case 6 spreekt nummer 6 aan
                case 6:
                    six();
                    break;
            }
}

int main(void)
{
    // Gebruikte pinnen op de B bank
    DDRB = 0b00000111;

    // Aanzetten PD2 pin voor de button
    PORTD = (1 << PD2);
    // Gebruikte pinnen op de D bank
    DDRD = 0b11111100;

    // While loop
    while (1)
    {
        // Als de bit schoon is van PD2 op de D bank voert die dit uit
        if(bit_is_clear(PIND, PD2)) {
            // Loop voor het dendergedrag van het dobbelen
            for(int i = 0; i < 6; i++){
                // Opschonen bits
                clear();
                // Randomroll uitvoeren
                randomRoll();
                // Delay na elke roll
                _delay_ms(DELAY_TIME_MS);
            }
        }
    }

    return 0;
}
