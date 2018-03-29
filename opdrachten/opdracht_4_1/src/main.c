/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 4.1 - Led there be light
 * Datum: 16-03-2018
 */


#include <avr/io.h>
#include <avr/interrupt.h>

// Array van RGB waardes.
int RGBPattern[3] = {0, 0, 0};

// int voor de kleur
int kleur = 0;

// functie voor bereken kleur
int berekenKleur () {
    // modulo op ingegeven kleur RGB
    return kleur % 3;
}

ISR(TIMER0_OVF_vect)
{
    // if voor als de kleur kleiner is dan 255
    if (RGBPattern[berekenKleur()] < 255) {
        // tel de kleur op met +5 tot 255
        RGBPattern[berekenKleur()] = RGBPattern[berekenKleur()] + 5;
    }

    else {
        // kleur weer op 0 zetten
        RGBPattern[berekenKleur()] = 0;
        // kleur int optellen 
        kleur++;
    }


    OCR1A = ~RGBPattern[0];    // R-Led waarde.
    OCR1B = ~RGBPattern[1];    // G-Led waarde.
    OCR2A = ~RGBPattern[2];    // B-Led waarde.
}

void initTimerOverflow()
{
    // Mask van de timer
    TIMSK0 |= (1 << TOIE0);

    // Instellingen timer
    TCCR0B |= (1 << CS02) | (1 << CS00);
    sei();
}

void intPWMTimerLED()
{
    // Timer 1 R-Led en G-Led
    TCCR1A |= (1 << WGM10) | (1 << WGM12); // Fast PWM.
    TCCR1B |= (1 << CS11);                 // PWM freq.

    // Timer 2 B-Led
    TCCR2A |= (1 << WGM20) | (1 << WGM21); // Fast PWM.
    TCCR2B |= (1 << CS21);                 // PWM freq.

    // R-Led en G-Led
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1);

    // B-Led
    TCCR2A |= (1 << COM2A1);
}

int main(void)
{

    // RGB pinnen initialiseren
    DDRB = (1 << PB1) | (1 << PB2) | (1 << PB3);

    // Functie van de overflow timer
    initTimerOverflow();

    // Functie van de led timer
    intPWMTimerLED();

    while (1) {
        
    }

    return 0;
}