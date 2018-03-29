# Opdracht 3.2 - ADC baby!

Maak een programma dat de waarde van een potentiometer vertaalt in een geluidssignaal tussen 100 en 10.000Hz. Laat dit signaal horen op de speaker.

# Samenvatting

Voor deze opdracht heb ik een deel van de code gebruikt uit de les met de potential meter en het ledje. In de les hadden we de potential meter zo ingesteld dat het ledje feller ging branden als je aan de meter draaide dat is met de speaker hetzelfde geval. Alleen moeten we binnen de range van 100 Hz en 10.000 Hz blijven. Je weet dat 100Hz gelijk is aan 10ms en 10.000us. Als je dat omrekend is 10.000hz gelijk aan 0.1ms en 100us. In de code maak ik gebruik van microseconden omdat ik dit makkelijker vond met berekenen. Hiervoor gebruik ik een functie die 1 t/m 1024 mapt met de waarde 100 en 10.000hz. Deze functie heb ik gevonden op [stackoverflow][stackoverflow] en heb ik iets aangepast. Daarna geef ik in de potential meter aan hoeveel microseconden het weer duurt voordat hij weer stroom krijgt zodat je de juiste toon krijgt. In de code staat dit verder uitgelegd. 

# Afbeelding Setup

Hieronder zie je afbeelding van de setup die ik gemaakt heb.
[![Opdracht 3.2 - Setup](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_3_2/assets/img/opdracht3_2_setup.JPG?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_3_2/assets/img/opdracht3_2_setup.JPG?raw=true)

# Afbeelding Fritzing

Hieronder zie je de afbeelding van de fritzing tekening die ik gemaakt heb.
[![Opdracht 3.2 - Fritzing](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_3_2/assets/img/opdracht3_2_fritzing_bb.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_3_2/assets/img/opdracht3_2_fritzing_bb.png?raw=true)

# Video URL

De [video][video] is te vinden op de onderstaande url:
[![Opdracht 3_1](https://img.youtube.com/vi/MZWNYMROIA0/maxresdefault.jpg)](https://youtu.be/MZWNYMROIA0)

# Code gebruikt voor de opdracht

```c
/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 3.2 - ADC Baby!
 * Datum: 16-03-2018
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
```

[video]: https://youtu.be/MZWNYMROIA0
[stackoverflow]: https://stackoverflow.com/a/5732390/3227342