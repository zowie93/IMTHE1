# Opdracht 3.1 - ADC baby!

Maak een digitale dobbelsteen met 9 leds (zie plaatje). Als je op een knop drukt geven de leds een random waarde tussen 1 en 6 weer op de leds zoals je dat kent op een echte dobbelsteen. Hou bij het programma rekening met dender-gedrag.

# Samenvatting

Voor de opdracht heb ik gebruik gemaakt van de ledjes die in de box inbegrepen zaten. Voor elke combinatie van een cijfer heb ik een functie gemaakt die de ledjes aanspreekt. Hierdoor heb ik 6 functies die elk een cijfer vertegenwoordigen. Ik maak gebruik van random die een nummer bij elke klik tussen de 1 en 6 berekend. Vervolgens gaat deze door de switch die elk 1 van de bovenste functies aanspreekt per random getal. Aan de volgende [Youtube][Youtube] video heb ik veel gehad deze ging gepaard met een [arduino][arduino] tutorial. Hierdoor ben ik op een switch gekomen.

# Afbeelding Setup

Hieronder zie je afbeelding van de setup die ik gemaakt heb.
[![Opdracht 3.1 - Setup](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_3_1/assets/img/opdracht3_1_setup.JPG?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_3_1/assets/img/opdracht3_1_setup.JPG?raw=true)

# Afbeelding Fritzing

Hieronder zie je de afbeelding van de fritzing tekening die ik gemaakt heb.
[![Opdracht 3.1 - Fritzing](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_3_1/assets/img/opdracht3_1_fritzing_bb.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_3_1/assets/img/opdracht3_1_fritzing_bb.png?raw=true)

# Video URL

De [video] is te vinden op de onderstaande url:
[![Opdracht 3_1](https://img.youtube.com/vi/H6loFRx4bV4/maxresdefault.jpg)](https://youtu.be/H6loFRx4bV4)

# Code gebruikt voor de opdracht

```c
/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 3 - ADC Baby!
 * Datum: 29-02-2018
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
```


[video]: https://youtu.be/H6loFRx4bV4
[Youtube]: https://www.youtube.com/watch?v=-CuFiuR8h20
[arduino]: https://jaydlawrence.co.uk/a-beginner-arduino-project-digital-dice-roll/