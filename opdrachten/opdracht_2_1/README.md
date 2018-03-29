# Opdracht 2.1 - Count me in

Maak	een	programma	dat	op	het	7-segment	LED	
display	 herhalend	telt	 van	 0	t/m	 9.	 Gebruik het	
rechter	display	van	de	 twee	en	verwerk functies	
en	bit-shifting	in	je	oplossing

# Samenvatting

Voor de opdracht heb ik gebruik gemaakt van de [Data Sheet] voor het 7-segment display (A/D5621A/B). Hiermee wist ik welke pinnen gebruikt werden voor ieder segment van het display. Zowel het linkse en rechts segment bevat een layout van 7 streepjes om een getal te maken. Er zijn 2 pinnen voor de 5 volt en 2 voor de ground.  De punt heeft ook een aparte pin maar die heb ik niet gebruikt voor de opdracht. Vervolgens heb ik uitgezocht welke waardes aangezet moeten worden voor elk getal dit heb ik gedaan met behulp van binaire getallen. Hier heb ik een array mee gevult zodat je gewoon langs de waardes kan loopen. Vervolgens heb ik ook uitgezocht of het een common anode of cathode was dit heb gedaan met behulp van de ground en de 5v pin. De meest linker pin van het rechtse segment was namelijk de 5v pin. Toen kwam ik eral snel achter dat we te maken hadden met een common anode display.  Ik heb voor mezelf in de code een digit (getekend) zodat ik wist op welke pinnen ik stroom moest zetten voor een bepaald getal en op welke pinnen deze zat aangesloten zodat ik met bitshifting de getallen of kon gaan. Verder heb ik een [Youtube] filmpje gevonden die het display uitlegd.  Voor de rest heb ik een functies gemaakt die d.m.v. bitshifting de C en D bank activeerd. 

# Afbeelding Setup

Hieronder zie je afbeelding van de setup die ik gemaakt heb.
[![Opdracht 2 - Setup](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_1/assets/img/opdracht2_setup.JPG?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_1/assets/img/opdracht2_setup.JPG?raw=true)

# Afbeelding Fritzing

Hieronder zie je de afbeelding van de fritzing tekening die ik gemaakt heb.
[![Opdracht 2 - Fritzing](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_1/assets/img/opdracht2_1_fritzing_bb.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_1/assets/img/opdracht2_1_fritzing_bb.png?raw=true)

# Video URL

De [video] is te vinden op de onderstaande url:
[![Opdracht 1](https://img.youtube.com/vi/xxDyX3eZft4/maxresdefault.jpg)](https://youtu.be/xxDyX3eZft4)

# Code gebruikt voor de opdracht

```c
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
```

# Technische tekening display
Hieronder zie je welke technische tekening ik gebruikt heb voor het opzoeken van de juiste pinnen per segment.
[![Technische tekening display](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_1/assets/img/matrix-technisch.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_1/assets/img/matrix-technisch.png?raw=true)

[Data Sheet]: http://www.datasheetarchive.com/A/d5621A/B*-datasheet.html?q=A/d5621A/B*&amp;amp;amp;p=11
[video]: https://youtu.be/xxDyX3eZft4
[Youtube]: https://www.youtube.com/watch?v=yWwvUUZ4-Xs