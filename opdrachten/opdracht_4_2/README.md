# Opdracht 4.2 - Led there be light

Maak een programma waarin je via Serial communicatie een led aan of uit kan zetten. Dit mag door bijvoorbeeld het karakter ‘a’ of ‘u’ te sturen. Het programma geeft feedback over de seriële poort of het gelukt is ja of nee. Gebruik niet de gegeven usart.c en .h in je uitwerking, maar maak een oplossing in 1 source bestand.

# Samenvatting

In de les hebben we het gehad over USART.h/c die gebruikt wordt voor seriële communicatie. Hiervoor heb ik code meegetypt samen met de docent en verder uitgewerkt in deze opdracht. Als ik binnen de seriele monitor een 'u' of een 'a' stuur gaat de led aan of uit. De 'u' gebruik ik voor uit. De 'a' gebruik ik voor aan. Als dit gelukt is wordt er via de seriele monitor aangegeven of dit gelukt is of niet die gebeurd met een simpele if else constructie. Als het niet gelukt is of er is een verkeerde character gestuurd geeft de monitor ook een melding.

Voor de led heb ik dezelfde [Datasheet] gebruikt die ik eerder voor opdracht 1 heb gebruikt. In de [Datasheet] zie je dat de Anode (+) het langste pootje is en de Cathode(-) is het kortste pootje. Hierdoor weet je precies op welke pin je stroom moet zetten en op welke de ground. De layout van het ledje kan je hieronder vinden.

# Afbeelding Setup

Hieronder zie je afbeelding van de setup die ik gemaakt heb.
[![Opdracht 4.2 - Setup](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_2/assets/img/opdracht4_2_setup.JPG?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_2/assets/img/opdracht4_2_setup.JPG?raw=true)

# Afbeelding Fritzing

Hieronder zie je de afbeelding van de fritzing tekening die ik gemaakt heb.
[![Opdracht 4.2 - Fritzing](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_2/assets/img/opdracht4_2_fritzing_bb.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_2/assets/img/opdracht4_2_fritzing_bb.png?raw=true)

# Video URL

De [video][video] is te vinden op de onderstaande url:
[![Opdracht 4_2](https://img.youtube.com/vi/XsHXUzApZ7s/maxresdefault.jpg)](https://youtu.be/XsHXUzApZ7s)

# Code gebruikt voor de opdracht

```c
/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 4.2 - Led there be light
 * Datum: 22-03-2018
 */

#define BAUD 9600

#include <avr/io.h>
#include <util/setbaud.h>
#include <util/delay.h>

// Gekopieerd uit bestand USART snap niet waarom dit moet als we het nu juist over code kwaliteit hebben en object georienteerd programmeren? 
void initUSART(void) {
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= (1 << U2X0);
#else
  UCSR0A &= ~(1 << U2X0);
#endif
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Gekopieerd uit bestand USART snap niet waarom dit moet als we het nu juist over code kwaliteit hebben en object georienteerd programmeren? 
uint8_t receiveByte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}

// Gekopieerd uit bestand USART snap niet waarom dit moet als we het nu juist over code kwaliteit hebben en object georienteerd programmeren? 
void transmitByte(uint8_t data) {
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;
}

// Gekopieerd uit bestand USART snap niet waarom dit moet als we het nu juist over code kwaliteit hebben en object georienteerd programmeren? 
void printString(const char myString[]) {
  uint8_t i = 0;
  while (myString[i]) {
    transmitByte(myString[i]);
    i++;
  }
}

void geluktAan() {
     // Led aanzetten
    PORTB = (1 << PB5);

    // Printen string als het gelukt is en led aan
    printString("Het is gelukt. Status: LED Aan\n");
}

void geluktUit() {
    // Led uitzetten
    PORTB = (0 << PB5);

    // Printen string als het gelukt is om de led uit te zetten.
    printString("Het is gelukt. Status: LED Uit\n");
}

// Main functie.
int main (void)
{
  // Functie uti USART
  initUSART();

  // Gebruikte LED PIN PB5
  DDRB = (1 << PB5);

  // Loop voor altijd.
  while (1)
  {
    // Var om ontvangen byte / karakter te lezen
    uint8_t ontvangenKar = receiveByte();

    // Als het een A is
    if (ontvangenKar == 'a')
    {
        // Gelukt aan functie aanroepen
        geluktAan();
    }

    // Of als het een u is
    else if (ontvangenKar == 'u')
    {
        // Gelukt uit functie aanroepen
       geluktUit();
    }

    // Afvangen fout
    else
    {
        // Foutmelding printen
        printString("Het is niet gelukt. Controleer de verbinding of de character\n");
    }
  }
}

```

[video]: https://youtu.be/XsHXUzApZ7s
[Datasheet]: <http://www1.futureelectronics.com/doc/EVERLIGHT%C2%A0/334-15__T1C1-4WYA.pdf>	"Technical datasheet 5mm led"