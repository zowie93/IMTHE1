# Opdracht 5.2 - ET Phone HOME!

Zoek naar een library op internet om het HD44780 display te kunnen besturen en maak een programma dat jouw naam en studentnummer op het display laat zien.

# Samenvatting

x

# Afbeelding Setup

Hieronder zie je afbeelding van de setup die ik gemaakt heb.
[![Opdracht 5.2 - Setup](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_5_2/assets/img/opdracht5_2_setup.JPG?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_5_2/assets/img/opdracht5_2_setup.JPG?raw=true)

# Afbeelding Fritzing

Hieronder zie je de afbeelding van de fritzing tekening die ik gemaakt heb.
[![Opdracht 5.2 - Fritzing](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_5_2/assets/img/opdracht5_2_fritzing_bb.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_5_2/assets/img/opdracht5_2_fritzing_bb.png?raw=true)

# Video URL

De [video][video] is te vinden op de onderstaande url:
[![Opdracht 5_2](https://img.youtube.com/vi/gxTNZPafquQ/maxresdefault.jpg)](https://youtu.be/gxTNZPafquQ)

# Code gebruikt voor de opdracht

```c
/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 5.2 - ET Phone HOME
 */

#include "hd44780.h"


void main(void) {

    // LCD initialiseren
    lcd_init();

    // Leeg beginnen scherm
    lcd_clrscr();

    // Naam op scherm schrijven
    lcd_puts("Zowie van Geest");

    // Hard enter
    lcd_goto(64);

    // Studentnummer op scherm schrijven
    lcd_puts("1097398");
}

```

[video]: https://youtu.be/gxTNZPafquQ
[Display Librabry]: https://community.atmel.com/projects/hd44780-library