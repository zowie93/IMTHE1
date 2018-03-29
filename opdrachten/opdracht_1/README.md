# Opdracht 1 - Blink once to accept

Maak	een	‘Blink	led’	programma,	waar	twee	leds	omen-om aan	 en	 uit	 gaan.	 Het	 knipperen	 van	 de	 leds moet	traag	verlopen,	zodat	het	knippereffect	zichtbaar is	met	het	blote	oog.

# Samenvatting

Voor de opdracht heb ik gebruik gemaakt van de [Native Blink PlatformIO] waarvan ik gebruik maak binnen in de editor visual studio code. Deze code laat de onboard led van de arduino nano blinken (eigenlijk hetzelfde principe als een normale led). Ik heb ook gebruik gemaakt van een [WordPress Blog] die precies uitlegd hoe het nou te werk gaat alleen maken ze hier gebruik van 1 led die op high en low gezet kan worden. 

# Afbeelding Setup

Hieronder zie je afbeelding van de setup die ik gemaakt heb.
[![Opdracht 1 - Setup](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_1/assets/img/opdracht1_setup.JPG?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_1/assets/img/opdracht1_setup.JPG?raw=true)


# Afbeelding Fritzing

Hieronder zie je de afbeelding van de fritzing tekening die ik gemaakt heb.
[![Opdracht 1 - Fritzing](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_1/assets/img/opdracht1_fritzing_bb.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_1/assets/img/opdracht1_fritzing_bb.png?raw=true)

# Video URL

De [video] is te vinden op de onderstaande url:
[![Opdracht 1](https://img.youtube.com/vi/ttEtQj9GnBg/maxresdefault.jpg)](https://www.youtube.com/watch?v=ttEtQj9GnBg)

# Code gebruikt voor de opdracht
```c
/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 1 - Blink once to accept
 * Datum: 15-02-2018
 */

#include <avr/io.h>
#include <util/delay.h>

// Define voor blink delay tijd in ms (1200)
#define DELAY_BLINK_MS 1200

int main(void)
{
    // Pin D5 & D6 zijn de output pins voor de leds
    DDRD = 0b01100000;

    // While loop
    while (1)
    {
        // Zet led aan op D5 en D6 uit indien die aan was
        PORTD ^= 1 << 5;

        // Wacht 1.2 seconden
        _delay_ms(DELAY_BLINK_MS);

        // Zet led uit op D5 en zet led aan op D6
        PORTD ^= 1 << 6;
    }

    return 0;
}
```

[WordPress Blog]: <https://balau82.wordpress.com/2011/03/29/programming-arduino-uno-in-pure-c/>
[Native Blink PlatformIO]: <https://github.com/platformio/platform-atmelavr/tree/develop/examples/native-blink>
[video]: <https://youtu.be/ttEtQj9GnBg>
