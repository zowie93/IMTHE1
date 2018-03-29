# Opdracht 4.3 - Led there be Light!

Verander deelopdracht 2 zodat binnenkomende data afgehandeld wordt in een interrupt (USART_RX_vect) zodat je programma (zoals in het voorbeeld van hoofdstuk 5) niet ‘eeuwig’ op input wacht. Toon aan dat het werkt door via seriële communicatie een ‘r’, ‘g’ of ‘b’ door te geven aan de AVR en dat dan de corresponderende kleur gaat pulseren (PWM op 1 kleur).

# Samenvatting

Bij deze opdracht heb ik alles precies hetzelfde aangesloten als opdracht 4.1 waar we een color changing led gemaakt hebben met behulp van ISR. Dat is bij deze opdracht niet anders alleen moeten we hier gebruik maken van interrupt. Dit werkte eerste instantie niet in het standaard USART bestand hierdoor moest de functie aangepast worden zodat je enkele characters kon sturen via deze manier. Eerst kwam ik er niet uit hoe ik deze characters kon sturen maar na veel Googlen kwam ik op een [forum] waarbij de ze in de initUSART functie op de variable UCSR0B de RXCIE0 aanzetten om te zorgen dat dit wel kan. Hiervoor moest je ook een tweede methode voor ISR aanmaken om te kijken of er geschreven wordt via de seriele verbinding. 

# Afbeelding Setup

Hieronder zie je afbeelding van de setup die ik gemaakt heb.
[![Opdracht 4.3 - Setup](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_3/assets/img/opdracht4_3_setup.jpg?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_3/assets/img/opdracht4_3_setup.jpg?raw=true)

# Afbeelding Fritzing

Hieronder zie je de afbeelding van de fritzing tekening die ik gemaakt heb.
[![Opdracht 4.3 - Fritzing](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_3/assets/img/opdracht4_3_fritzing_bb.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_4_3/assets/img/opdracht4_3_fritzing_bb.png?raw=true)

# Video URL

De [video][video] is te vinden op de onderstaande url:
[![Opdracht 4_2](https://img.youtube.com/vi/MGRdxS2QpH4/maxresdefault.jpg)](https://youtu.be/MGRdxS2QpH4)

# Code gebruikt voor de opdracht

```c
/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Opdracht 4.3 - Led there be light
 * Datum: 23-03-2018
 */

// Baud rate.
#define BAUD 9600

// Includes.
#include <avr/io.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>

// character begint op R rood.
char kleurChar = 'r';

// int voor teller.
int teller = 0;

// Gekopieerd uit bestand USART snap niet waarom dit moet als we het nu juist over code kwaliteit hebben en object georienteerd programmeren? 
void initUSART(void)
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    #if USE_2X
        UCSR0A |= (1 << U2X0);
    #else
        UCSR0A &= ~(1 << U2X0);
    #endif

    // RXCIE0 aanzetten voor character ontvangst
    // https://www.avrfreaks.net/forum/usart-interrupts-atmega328p-solved
    UCSR0B = (1 << TXEN0) | (1 << RXCIE0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Gekopieerd uit bestand USART snap niet waarom dit moet als we het nu juist over code kwaliteit hebben en object georienteerd programmeren? 
void printString(const char myString[])
{
    uint8_t i = 0;
    while (myString[i])
    {
        transmitByte(myString[i]);
        i++;
    }
}

// Gekopieerd uit bestand USART snap niet waarom dit moet als we het nu juist over code kwaliteit hebben en object georienteerd programmeren? 
uint8_t receiveByte(void)
{
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

// Gekopieerd uit bestand USART snap niet waarom dit moet als we het nu juist over code kwaliteit hebben en object georienteerd programmeren? 
void transmitByte(uint8_t data)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

void initTimerOverflowCapture()
{
    // Starten van timer met 64ms delay 
    TIMSK0 |= (1 << TOIE0);

    // Starten van de timer en prescaler op 64ms
    TCCR0B |= (1 << CS02) | (1 << CS00);
}

void initPWMTimerForTheLED()
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

// Als er geschreven wordt naar de seriele verbinding.
ISR (USART_RX_vect)
{
    if(UDR0 == 'r') {
        // Print de kleur
        printString("kleur veranderd naar rood\n");
        // Teller op 0 zetten
        teller = 0;
        // Opslaan in de kleurChar
        kleurChar = 'r';
    } else if(UDR0 == 'g') {
        // Print de kleur
        printString("kleur veranderd naar groen\n");
        // Teller op 0 zetten
        teller = 0;
        // Opslaan in de kleurChar
        kleurChar = 'g';
    } else if(UDR0 == 'b') {
        // Print de kleur
        printString("kleur veranderd naar blauw\n");
        // Teller op 0 zetten
        teller = 0;
        // Opslaan in de kleurChar
        kleurChar = 'b';
    } else {
        // Print wat voor input er gegeven moet worden.
        printString("Vul een R in voor Rood een G voor Groen en een B voor Blauw\n");
    }
}

// Timer overflow interrupt.
ISR (TIMER0_OVF_vect)
{
    // Tel de count op, voor de brightness.
    teller++;
    // Switch om te kijken om welke kleur het gaat.

    if(kleurChar == 'r') {
      // Rode led aan met teller
      OCR1A = ~teller;
      // Groene led uit
      OCR1B = ~0;
      // Blauwe led uit
      OCR2A = ~0;
    } else if(kleurChar == 'g') {
      // Rode led aan met teller
      OCR1A = ~0;
      // Groene led uit
      OCR1B = ~teller;
      // Blauwe led uit
      OCR2A = ~0;
    } else if(kleurChar == 'b') {
      // Rode led aan met teller
      OCR1A = ~0;
      // Groene led uit
      OCR1B = ~0;
      // Blauwe led uit
      OCR2A = ~teller;
    }
}


// Main methode.
int main(void)
{
    // RGB pinnen initialiseren
    DDRB = (1 << PB1) | (1 << PB2) | (1 << PB3);
    // USART initialiseren
    initUSART();
    // Functie van de overflow capture timer
    initTimerOverflowCapture();
    // Functie van de led timer
    initPWMTimerForTheLED();
    // Interrupts aan
    sei();

    while (1) {
    }

    return 0;
}
```

[video]: https://youtu.be/MGRdxS2QpH4

[forum]: https://www.avrfreaks.net/forum/usart-interrupts-atmega328p-solved