/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 3.2 - ADC Baby!
 */


#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

// Initialiseer de potential meter.
void initADC () {
    
    // 5 volt
    ADMUX  |= (1 << REFS0);
    
    // Divider op 128 voor 10 bit precisie.
    ADCSRA |= ((1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
    
    // AD enable.
    ADCSRA |= (1 << ADEN);
}

// Functie voor potential meter die de waarde returned
uint16_t readADC () {
    
    // Lezen van de meter
    ADCSRA |= (1 << ADSC);
    
    // Loop tot er bits terug gegeven worden
    loop_until_bit_is_clear(ADCSRA, ADSC);
    
    // return waarde
    return ADC;
}

// Functie voor timeout
void delay (uint16_t time) {

    // Loop voor de delay
    for (uint16_t i = 0; i < time; i++) {

        // 1 microseconde wachten
        _delay_us(1);
    }
}

// Functie voor round
double round(double d)
{
    // Returnen van afgeronde waarde
    return floor(d + 0.5);
}

// Het mappen van aantal hertz gevonden op stackoverflow https://stackoverflow.com/a/5732390/3227342

float map(int input, int input_start, int input_end, int output_start, int output_end)
{
    // De slope krijgt constant nummers terug door de binnenkomende output values en dit zorgt ervoor dat die het 1 keer berekend.
    double slope = 1.0 * (output_end - output_start) / (input_end - input_start);
    // afgeronde waarde terug geven van de slope
    return output_start + round(slope * (input - input_start));
}

int main(void)
{
    // B bank activeren
    DDRB  = (1 << PB5);

    // D pin activeren
    PORTD = (1 << PD2);

    // potentie meter functie
    initADC();

    // Oneindige loop
    while (1)
    {
        // Lees de waarde van de potential meter uit.
        uint16_t pwm = readADC();

        // Nieuwe variabel voor de nieuwe pwm value
        double pwmval;

        //Mappen
        pwmval = map(pwm, 1, 1024, 10000, 100) / 2;

        // B pin activeren
        PORTB = (1 << PB5);

        // delay pwmval
        delay(pwmval);

        // B pin uit
        PORTB = 0;

        // Wacht voor een X aantal ms.
        delay(pwmval);
    }

    return 0;
}