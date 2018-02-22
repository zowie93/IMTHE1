# Opdracht 2 - Count	me	in

Maak	een	programma	dat	op	het	7-segment	LED	
display	 herhalend	telt	 van	 0	t/m	 9.	 Gebruik het	
rechter	display	van	de	 twee	en	verwerk functies	
en	bit-shifting	in	je	oplossing

# Samenvatting

Voor de opdracht heb ik gebruik gemaakt van de [Data Sheet] voor het 7-segment display. Hiermee wist ik welke pinnen gebruikt werden voor ieder segment. Met de ground heb ik gecontroleerd of deze ook echt de juiste waren en heb ik deze genoteerd in een schema welke segmenten ik nodig had voor een bepaald cijfer. Verder heb ik een [Youtube] filmpje gevonden die het display uitlegd.  Voor de rest heb ik een functies gemaakt die d.m.v. bitshifting de C en D bank activeerd. 

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

[Data Sheet]: http://www.datasheetarchive.com/A/d5621A/B*-datasheet.html?q=A/d5621A/B*&amp;amp;p=11
[video]: https://youtu.be/xxDyX3eZft4
[Youtube]: https://www.youtube.com/watch?v=yWwvUUZ4-Xs