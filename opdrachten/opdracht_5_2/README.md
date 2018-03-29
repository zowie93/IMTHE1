# Opdracht 5.2 - ET Phone HOME!

Zoek naar een library op internet om het HD44780 display te kunnen besturen en maak een programma dat jouw naam en studentnummer op het display laat zien.

# Samenvatting

Voor deze opdracht heb ik een library gezocht op het internet voor de aansturing hiervan. Er zijn een aantal library's gemaakt voor het display en dit maakte de keuze erg lastig. Ik ben gegaan voor de makkelijkste weg en ging voor een combinatie van twee tutorials. Ik heb een [Display Library] gevonden met een settings bestand waarin je aanvoudig de aansluitingen voor elke arduino kon veranderen naar eigen wens. Omdat ik niet precies wist op welke pinnen het aangesloten moest worden ben ik ook opzoek gegaan naar een schema hoe ze het precies aansluiten. Al snel kwam ik erachter dat iedereen een pot meter gebruikte voor regelen van de backlight van de display.

De library heb ik gebruikt van:
https://community.atmel.com/projects/hd44780-library

In deze library zit een settings bestand die ik als volgt heb aangepast:
```c
#ifndef HD44780_SETTINGS_H
#define HD44780_SETTINGS_H

#define F_CPU                    16000000     // Set Clock Frequency

#define USE_ADELAY_LIBRARY       0           // Set to 1 to use my ADELAY library, 0 to use internal delay functions
#define LCD_BITS                 4           // 4 for 4 Bit I/O Mode, 8 for 8 Bit I/O Mode
#define RW_LINE_IMPLEMENTED      0           // 0 for no RW line (RW on LCD tied to ground), 1 for RW line present
#define WAIT_MODE                0           // 0=Use Delay Method (Faster if running <10Mhz)
                                             // 1=Use Check Busy Flag (Faster if running >10Mhz) ***Requires RW Line***
#define DELAY_RESET              15          // in mS

#define LCD_DB4_PORT             PORTC       // If using 4 bit omde, yo umust configure DB4-DB7
#define LCD_DB4_PIN              0
#define LCD_DB5_PORT             PORTC
#define LCD_DB5_PIN              1
#define LCD_DB6_PORT             PORTC
#define LCD_DB6_PIN              2
#define LCD_DB7_PORT             PORTC
#define LCD_DB7_PIN              3

#define LCD_RS_PORT              PORTC       // Port for RS line
#define LCD_RS_PIN               4           // Pin for RS line

#define LCD_DISPLAYS             1           // Up to 4 LCD displays can be used at one time
                                             // All pins are shared between displays except for the E
                                             // pin which each display will have its own

                                             // Display 1 Settings - if you only have 1 display, YOU MUST SET THESE
#define LCD_DISPLAY_LINES        2           // Number of Lines, Only Used for Set I/O Mode Command
#define LCD_E_PORT               PORTC       // Port for E line
#define LCD_E_PIN                5           // Pin for E line

#endif
```



Voor de aansluiting van alle pinnen heb ik een tutorial gevolgt:
http://www.learningaboutelectronics.com/Articles/Arduino-HD44780-circuit.php

Hierin staat een afbeelding met de exacte pinnen waarop je alles kan aansluiten en die heb ik ingevuld in de bovenstaande settings.
[![Lcd pin layout](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_5_2/assets/img/lcd_pinlayout.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_5_2/assets/img/lcd_pinlayout.png?raw=true)



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
 * Datum: 28-03-2018
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
[Display Library]: https://community.atmel.com/projects/hd44780-library