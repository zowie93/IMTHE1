# Opdracht 4.1 - Led there be light

Creëer een ‘Color changing light’ met het RGB-led op basis van PWM. De PWM moet in een Interrupt Service Routine (ISR) worden afgehandeld.

# Samenvatting

Voor het aansluiten van de led heb ik eerste uitgezocht wat voor soort RGB- Led het is. Ik heb hem eerst aangesloten met alleen de 5 volt op de tweede pin en een ground op de eerste pin om te kijken of het een Common Cathode is of een Common Anode. Wij hebben de led gekregen die Common Anode is. In pricipe maakt dat voor de layout van de pinnen niet uit. 
Vervolgens heb ik de juiste [datasheet] erbij gezocht om te kijken welke pinnen bij welke kleur leds horen. 

In de les zelf hadden we een voorbeeld gemaakt om met de PWM OC2A de led te laten dimmen. Dit is bij een RGB led niet anders alleen heeft het meerdere pinnen. Hiervoor heb ik de PWM OC1A en de PWM OC1B. In het boek staat code die je kan gebruiken voor de RGB led.
In de code laat ik elke led van 0 tot en met 255 tellen met stappen van 5. Ik ben begonnen met de Rode led die begint op 0 en gaat naar 255 en vervolgens weer op 0. Dit doet die hetzelfde voor Groen en Blauw. Alle code die dit mogelijk maakt staat in de ISR wat volgens de opdracht vereist is. 

# Afbeelding Setup

Hieronder zie je afbeelding van de setup die ik gemaakt heb.
[![Opdracht 4.1 - Setup](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_1/assets/img/opdracht4_1_setup.jpg?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_1/assets/img/opdracht4_1_setup.jpg?raw=true)

# Afbeelding Fritzing

Hieronder zie je de afbeelding van de fritzing tekening die ik gemaakt heb.
[![Opdracht 4.1 - Fritzing](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_1/assets/img/opdracht4_1_fritzing_bb.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_1/assets/img/opdracht4_1_fritzing_bb.png?raw=true)

# Video URL

De [video][video] is te vinden op de onderstaande url:
[![Opdracht 4_1](https://img.youtube.com/vi/l-dhi2N9c1I/maxresdefault.jpg)](https://youtu.be/l-dhi2N9c1I)

# Code gebruikt voor de opdracht

```c
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

void initTimerOverflowCapture()
{
    // Starten van timer met 64ms delay 
    TIMSK0 |= (1 << TOIE0);

    // Starten van de timer en prescaler op 64ms
    TCCR0B |= (1 << CS02) | (1 << CS00);
    sei();
}

void intPWMTimerForTheLED()
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
    initTimerOverflowCapture();

    // Functie van de led timer
    intPWMTimerForTheLED();

    while (1) {
        
    }

    return 0;
}
```

# Technische data rgb-led

Hieronder zie je de afbeelding van de technische data van de rgb-led
[![technische data rgb-led](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_1/assets/img/rgb-datasheet.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_1/assets/img/rgb-datasheet.png?raw=true)

[video]: https://youtu.be/l-dhi2N9c1I
[datasheet]: https://www.sparkfun.com/datasheets/Components/YSL-R596CR3G4B5C-C10.pdf