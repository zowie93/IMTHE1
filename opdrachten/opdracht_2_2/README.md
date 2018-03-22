# Opdracht 2.2 - Count	me	in

Breidt de eerste deel-opdracht uit zodat de twee segmenten samen van 0 t/m 99 tellen.

# Samenvatting

Voor de opdracht heb ik gebruik gemaakt van de [Data Sheet] voor het 7-segment display. Hiermee wist ik welke pinnen gebruikt werden voor ieder segment. Met de ground heb ik gecontroleerd of deze ook echt de juiste waren en heb ik deze genoteerd in een schema welke segmenten ik nodig had voor een bepaald cijfer. Verder heb ik een [Youtube] filmpje gevonden die het display uitlegd.  Voor de rest heb ik een functies gemaakt die d.m.v. bitshifting de C, B en D bank activeerd. 

# Afbeelding Setup

Hieronder zie je afbeelding van de setup die ik gemaakt heb.
[![Opdracht 2 - Setup](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_2/assets/img/opdracht2_2_setup.JPG?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_2/assets/img/opdracht2_2_setup.JPG?raw=true)

# Afbeelding Fritzing

Hieronder zie je de afbeelding van de fritzing tekening die ik gemaakt heb.
[![Opdracht 2 - Fritzing](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_2/assets/img/opdracht2_2_fritzing_bb.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_2/assets/img/opdracht2_2_fritzing_bb.png?raw=true)

# Video URL

De [video] is te vinden op de onderstaande url:
[![Opdracht 2.2](https://img.youtube.com/vi/https://youtu.be/NQaIskqfxnc/maxresdefault.jpg)](https://youtu.be/NQaIskqfxnc)

# Code gebruikt voor de opdracht

```c
/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 2.2 - Count me in
 */

#include <avr/io.h>
#include <util/delay.h>

#define DELAY_TIME_MS 300
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
*
* ---- DIGIT LEFT ----
*
*        ---------          
*       | A = PB0 |        
*        ---------         
* ------           ----- 
*| F   |          | B   |
*| =   |          | =   |
*| PC4 |          | PB1 |
* -----            -----
*        --------- 
*       | G = PC5 |
*        ---------
* ------           ----- 
*| E   |          | C   |
*| =   |          | =   |
*| PC3 |          | PB2 |
* -----            -----
*        --------- 
*       | D = PB3 |
*        ---------
*/

// Functie voor de C poort met integer in de callback
void useCport (int left, int right) {
    // Zorgen met bitshifting dat bij de linker en rechter digits begint op 0 zodat je kan optellen vanaf 0
    PORTC = ~((((left << 1) >> 5) << 3) | ((right << 1) >> 5));
}

// Functie voor de D poort met integer in de callback
void useDport (int left) {
    // Poort D gebruikt input van digit die bitshift die 4 keer naar links en 8 keer naar rechts zodat die leeg begint en dan met de bitwise operator NOT draai ik ze om
    PORTD =~ (((left) << 8) >> 4);
}

// Functie voor de B poort met integer in de callback
void useBport (int right) {
    // Poort B gebruikt input van digit die bitshift die 4 keer naar links en 4 keer naar rechts zodat die leeg begint en dan met de bitwise operator NOT draai ik ze om
    PORTB =~ (((right) << 4) >> 4);
}

int main(void)
{
    // Zet alle pinnen van de C bank aan
    DDRC = 0b11111111;

    // Zet alle pinnen van de D bank aan
    DDRD = 0b11111111;

    // Zet alle pinnen van de B bank aan
    DDRB = 0b11111111;

    // teller van i op 0
    int i = 0;

    // Alle digits in een array
    int digits[10] = {
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111  // 9

    };

    // While loop
    while (1)
    {
        int left = digits[i / 10];
        int right = digits[i % 10];

        // Gebruik B pinnen
        useBport(left);

        // Gebruik C pinnen
        useCport(left, right);

        // Gebruik D pinnen
        useDport(right);

        // Wacht 0.3 seconden
        _delay_ms(DELAY_TIME_MS);

        // i als teller optellen.
        i++;

        // Reset naar 0 als die boven 99 gaat
        if (1 > 99)
        {
            i = 0;
        }
    }

    return 0;
}
```

[Data Sheet]: http://www.datasheetarchive.com/A/d5621A/B*-datasheet.html?q=A/d5621A/B*&amp;amp;amp;amp;p=11
[video]: https://youtu.be/NQaIskqfxnc
[Youtube]: https://www.youtube.com/watch?v=yWwvUUZ4-Xs