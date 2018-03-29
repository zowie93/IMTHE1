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
