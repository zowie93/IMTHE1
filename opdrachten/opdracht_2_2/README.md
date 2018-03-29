# Opdracht 2.2 - Count	me	in

Breidt de eerste deel-opdracht uit zodat de twee segmenten samen van 0 t/m 99 tellen.

# Samenvatting

Voor de opdracht is eigenlijk dezelfde uitleg van toepassing als de opdracht hiervoor alleen kom er nu een 2de display erbij het verschil hiermee is dat je voor de ook moet uitzoeken welke pinnen waarbij horen. Dit heb ik genoteerd en (getekend) in de code welke pinnen actief moeten zijn voor het laten zien van het cijfer. Omdat je niet genoeg aansluitingen op de C en D bank hebt moest ik een B bank toevoegen voor het linker display. Vervolgens kijk ik wanneer het getal boven de 99 komt zodat ik hem weer op 0 kan laten beginnen.  

Voor de opdracht heb ik gebruik gemaakt van de [Data Sheet] voor het 7-segment display (A/D5621A/B). Hiermee wist ik welke pinnen gebruikt werden voor ieder segment van het display. Zowel het linkse en rechts segment bevat een layout van 7 streepjes om een getal te maken. Er zijn 2 pinnen voor de 5 volt en 2 voor de ground.  De punt heeft ook een aparte pin maar die heb ik niet gebruikt voor de opdracht. Vervolgens heb ik uitgezocht welke waardes aangezet moeten worden voor elk getal dit heb ik gedaan met behulp van binaire getallen. Hier heb ik een array mee gevult zodat je gewoon langs de waardes kan loopen. Vervolgens heb ik ook uitgezocht of het een common anode of cathode was dit heb gedaan met behulp van de ground en de 5v pin. De meest linker pin van het rechtse segment was namelijk de 5v pin. Toen kwam ik eral snel achter dat we te maken hadden met een common anode display.  Ik heb voor mezelf in de code een digit (getekend) zodat ik wist op welke pinnen ik stroom moest zetten voor een bepaald getal en op welke pinnen deze zat aangesloten zodat ik met bitshifting de getallen of kon gaan. Verder heb ik een [Youtube] filmpje gevonden die het display uitlegd.  Voor de rest heb ik een functies gemaakt die d.m.v. bitshifting de C / D en B bank activeerd. 

# Afbeelding Setup

Hieronder zie je afbeelding van de setup die ik gemaakt heb.
[![Opdracht 2 - Setup](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_2/assets/img/opdracht2_2_setup.JPG?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_2/assets/img/opdracht2_2_setup.JPG?raw=true)

# Afbeelding Fritzing

Hieronder zie je de afbeelding van de fritzing tekening die ik gemaakt heb.
[![Opdracht 2 - Fritzing](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_2/assets/img/opdracht2_2_fritzing_bb.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_2/assets/img/opdracht2_2_fritzing_bb.png?raw=true)

# Video URL

De [video] is te vinden op de onderstaande url:
[![Opdracht 2.2](https://img.youtube.com/vi/https://youtu.be/suMXQRbO9Xg/maxresdefault.jpg)](https://youtu.be/suMXQRbO9Xg)

# Code gebruikt voor de opdracht

```c
/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 2.2 - Count me in
 * Datum: 26-02-2018
 */

#include <avr/io.h>
#include <util/delay.h>

#define DELAY_TIME_MS 300
/*
* ---- DIGIT RECHTS ----
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
* ---- DIGIT LINKS ----
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
void useCport (int links, int rechts) {
    // Zorgen met bitshifting dat bij de linker en rechter digits begint op 0 zodat je kan optellen vanaf 0
    PORTC = ~((((links << 1) >> 5) << 3) | ((rechts << 1) >> 5));
}

// Functie voor de D poort met integer in de callback
void useDport (int links) {
    // Poort D gebruikt input van digit die bitshift die 4 keer naar links en 8 keer naar rechts zodat die leeg begint en dan met de bitwise operator NOT draai ik ze om
    PORTD =~ (((links) << 8) >> 4);
}

// Functie voor de B poort met integer in de callback
void useBport (int rechts) {
    // Poort B gebruikt input van digit die bitshift die 4 keer naar links en 4 keer naar rechts zodat die leeg begint en dan met de bitwise operator NOT draai ik ze om
    PORTB =~ (((rechts) << 4) >> 4);
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
        int links = digits[i / 10];
        int rechts = digits[i % 10];

        // Gebruik B pinnen
        useBport(links);

        // Gebruik C pinnen
        useCport(links, rechts);

        // Gebruik D pinnen
        useDport(rechts);

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

# Technische tekening display
Hieronder zie je welke technische tekening ik gebruikt heb voor het opzoeken van de juiste pinnen per segment.
[![Technische tekening display](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_2/assets/img/matrix-technisch.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_2_2/assets/img/matrix-technisch.png?raw=true)

[Data Sheet]: http://www.datasheetarchive.com/A/d5621A/B*-datasheet.html?q=A/d5621A/B*&amp;amp;amp;amp;amp;p=11
[video]: https://youtu.be/suMXQRbO9Xg
[Youtube]: https://www.youtube.com/watch?v=yWwvUUZ4-Xs