/**
 * IMTHE1 - Zowie van Geest - 1097398 - INF3C
 * Eindopdracht
 * Datum: 31-03-2018
 */

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <USART.h>

// DHT11 pinnen
#define DHT11_PIN 6
// Pinnen waar data overheen gaat shift register
#define DS_PORT PORTC
#define DS_PIN 0
// ST CP port en pin van shiftregister
#define ST_CP_PORT PORTC
#define ST_CP_PIN 1
// SH CP port en pin van shiftregister
#define SH_CP_PORT PORTC
#define SH_CP_PIN 2

// Delay van de ledjes
#define DELAY_LED 160
#define DELAY_LED_K 110

// Pin laag zetten
#define DS_low() DS_PORT &= ~_BV(DS_PIN)
// Pin hoog zetten
#define DS_high() DS_PORT |= _BV(DS_PIN)
// ST CP pin laag
#define ST_CP_low() ST_CP_PORT &= ~_BV(ST_CP_PIN)
// ST CP pin hoog
#define ST_CP_high() ST_CP_PORT |= _BV(ST_CP_PIN)
//SH CP pin laag
#define SH_CP_low() SH_CP_PORT &= ~_BV(SH_CP_PIN)
// SH CP pin hoog
#define SH_CP_high() SH_CP_PORT |= _BV(SH_CP_PIN)

// variable voor Integraal Luchtvochtigheid, Decimaal Luchtvochtigheid, Integraal Temperatuur, Decimaal temperatuur en als laatste de checksum.
uint8_t c = 0, I_RH, D_RH, I_Temp, D_Temp, CheckSum;
// Variable voor het optellen
int count;

// Functie voor het starten van pull-up-pull-down request
void request()
{
    DDRD |= _BV(DHT11_PIN);
    // Zet de pin op low
    PORTD &= ~_BV(DHT11_PIN);
    // Wachten voor 20ms
    _delay_ms(20);
    // Zet de pin op high
    PORTD |= _BV(DHT11_PIN);
}

// Functie voor het ontvangen van de response van de DHT11 sensor
void response()
{
    // Response van DHT11 nu actief
    DDRD &= ~_BV(DHT11_PIN);
    // Loop tot de pin clear is
    while (PIND & _BV(DHT11_PIN))
        ;
    // Loop tot die een waarde krijgt
    while ((PIND & _BV(DHT11_PIN)) == 0)
        ;
    // Loop tot de pin weer clear is
    while (PIND & _BV(DHT11_PIN))
        ;
}

// Functie voor het ontvangen van data van de DHT11 sensor
uint8_t receive_data() /* receive data */
{
    // for loop voor elk stuk data (8bit) voor het uitlezen dient dit 8x gedaan te worden.
    for (int a = 0; a < 8; a++)
    {
        // Loop voor het kijken of er een 0 of 1 terug gegeven wordt
        while ((PIND & _BV(DHT11_PIN)) == 0)
            ;
        // Delay van 30us
        _delay_us(30);
        // Check of de high pin groter is dan 30ms
        if (PIND & _BV(DHT11_PIN))
            // Dan is de pin high
            c = (c << 1) | (0x01); /* then its logic HIGH */
        else
            // Ander is de pin low
            c = (c << 1);
        // Loop tot pin clear is
        while (PIND & _BV(DHT11_PIN))
            ;
    }
    // teruggeven c
    return c;
}

void dht11_measure()
{
    // begin met het request
    request();
    // Wacht op response
    response();
    // Integraal voor luchtvochtigheid
    I_RH = receive_data();
    // Decimaal voor luchtvochtigheid
    D_RH = receive_data();
    // Integraal voor Temperatuur
    I_Temp = receive_data();
    // Decimaal voor Temperatuur
    D_Temp = receive_data();
    // Checksum voor alle 4 de bits van 8
    CheckSum = receive_data();
}

void initTimerOverflowCapture()
{
    // Starten van timer met 64ms delay
    TIMSK0 |= (1 << TOIE0);
    // Starten van timer met 64ms delay
    TIMSK1 |= (1 << TOIE1);

    // Starten van de timer en prescaler op 64ms
    TCCR0B |= (1 << CS00) | (1 << CS02);

    // Starten van de timer en prescaler op 64ms
    TCCR1B |= (1 << CS10);

    // interrupts aan
    sei();
}

// Functie voor initialiseren matrix
void matrixInit()
{
    // Zet de pinnen aan op output
    DDRC = 0b00000111;
    PORTC = 0b00000000;
}

// Functie waarbij je 1 ledje aanzet met berekening van 1 rij en 1 column
void single_led(int row, int column)
{
    // Zet SH CP op low
    SH_CP_low();
    // Zet ST CP op low
    ST_CP_low();
    // For loop die het matrix indexeerd van 8 rijen
    for (int i = 0; i < 8; i++)
    {
        // Als i een getal is gaat de pin op high dus rij x column is ledje aan
        if (i == row)
        {
            // Zet pin hoog
            DS_high();
        }
        // Anders nog iets?
        else
        {
            // Zet pin laag
            DS_low();
        }
        // Pin hoog
        SH_CP_high();
        // Pin laag
        SH_CP_low();
    }

    // For loop die het matrix indexeerd van 8 columns
    for (int i = 0; i < 8; i++)
    {
        // Als i een getal is gaat de pin op high dus rij x column is ledje aan
        if (i == column)
        {
            // Zet pin laag
            DS_low();
        }

        else
        {   
            // Zet ping hoog
            DS_high();
        }
        // Pin hoog
        SH_CP_high();
        // Pin laag
        SH_CP_low();
    }
    // Pin hoog eindigen 
    ST_CP_high();
}

// Functie voor het tekenen van een K
void drawKoorts()
{
    single_led(0, 0);
    _delay_us(DELAY_LED_K);
    single_led(0, 1);
    _delay_us(DELAY_LED_K);
    single_led(0, 5);
    _delay_us(DELAY_LED_K);
    single_led(0, 6);
    _delay_us(DELAY_LED_K);
    single_led(1, 0);
    _delay_us(DELAY_LED_K);
    single_led(1, 1);
    _delay_us(DELAY_LED_K);
    single_led(1, 4);
    _delay_us(DELAY_LED_K);
    single_led(1, 5);
    _delay_us(DELAY_LED_K);
    single_led(2, 0);
    _delay_us(DELAY_LED_K);
    single_led(2, 1);
    _delay_us(DELAY_LED_K);
    single_led(2, 3);
    _delay_us(DELAY_LED_K);
    single_led(2, 4);
    _delay_us(DELAY_LED_K);
    single_led(3, 0);
    _delay_us(DELAY_LED_K);
    single_led(3, 1);
    _delay_us(DELAY_LED_K);
    single_led(3, 2);
    _delay_us(DELAY_LED_K);
    single_led(3, 3);
    _delay_us(DELAY_LED_K);
    single_led(4, 0);
    _delay_us(DELAY_LED_K);
    single_led(4, 1);
    _delay_us(DELAY_LED_K);
    single_led(4, 2);
    _delay_us(DELAY_LED_K);
    single_led(4, 3);
    _delay_us(DELAY_LED_K);
    single_led(5, 0);
    _delay_us(DELAY_LED_K);
    single_led(5, 1);
    _delay_us(DELAY_LED_K);
    single_led(5, 3);
    _delay_us(DELAY_LED_K);
    single_led(5, 4);
    _delay_us(DELAY_LED_K);
    single_led(6, 0);
    _delay_us(DELAY_LED_K);
    single_led(6, 1);
    _delay_us(DELAY_LED_K);
    single_led(6, 4);
    _delay_us(DELAY_LED_K);
    single_led(6, 5);
    _delay_us(DELAY_LED_K);
    single_led(7, 0);
    _delay_us(DELAY_LED_K);
    single_led(7, 1);
    _delay_us(DELAY_LED_K);
    single_led(7, 5);
    _delay_us(DELAY_LED_K);
    single_led(7, 6);
    _delay_us(DELAY_LED_K);
}

// Functie voor het tekenen van het kruis
void drawGeenKoorts()
{
    _delay_us(DELAY_LED);
    single_led(1, 2);
    _delay_us(DELAY_LED);
    single_led(1, 3);
    _delay_us(DELAY_LED);
    single_led(1, 4);
    _delay_us(DELAY_LED);
    single_led(1, 5);
    _delay_us(DELAY_LED);
    single_led(2, 1);
    _delay_us(DELAY_LED);
    single_led(2, 2);
    _delay_us(DELAY_LED);
    single_led(2, 3);
    _delay_us(DELAY_LED);
    single_led(2, 4);
    _delay_us(DELAY_LED);
    single_led(2, 5);
    _delay_us(DELAY_LED);
    single_led(2, 6);
    _delay_us(DELAY_LED);
    single_led(3, 1);
    _delay_us(DELAY_LED);
    single_led(3, 2);
    _delay_us(DELAY_LED);
    single_led(3, 5);
    _delay_us(DELAY_LED);
    single_led(3, 6);
    _delay_us(DELAY_LED);
    single_led(5, 1);
    _delay_us(DELAY_LED);
    single_led(5, 2);
    _delay_us(DELAY_LED);
    single_led(5, 5);
    _delay_us(DELAY_LED);
    single_led(5, 6);
    _delay_us(DELAY_LED);
    single_led(6, 1);
    _delay_us(DELAY_LED);
    single_led(6, 2);
    _delay_us(DELAY_LED);
    single_led(6, 5);
    _delay_us(DELAY_LED);
    single_led(6, 6);
    _delay_us(DELAY_LED);
}

// Timer 1
ISR(TIMER0_OVF_vect)
{
    // Kijken wanneer de count groter is dan 300 dan voert die dit uit
    if (count > 300)
    {
        // Voor telkens opnieuw uitvoeren zet ik die count op 0 als die in de loop zit
        count = 0;

        // Data charset voor alle waardes uit de DHT11
        char data[5];

        // Starten van de meting
        dht11_measure();

        // Als de waardes niet overeen komen met de bijbehorende checksum print die een error.
        if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
        {
            // Print error.
            printString("Error");
        }
        // Anders nog iets?
        else
        {
            // Omzetten van de data
            itoa(I_RH, data, 10);
            // Printen data
            printString(data);
            // punt als tussenwaarde
            printString(".");

            // Omzetten van de data
            itoa(D_RH, data, 10);
            // Printen data
            printString(data);
            // Luchtvochtigheid is in percentage
            printString("%");

            // Omzetten van de data
            itoa(I_Temp, data, 10);
            // Printen data
            printString(data);
            // punt als tussen waarde
            printString(".");

            // Omzetten van de data
            itoa(D_Temp, data, 10);
            // Printen data
            printString(data);
            // Celsuis
            printString("C ");

            // Omzetten van de data
            itoa(CheckSum, data, 10);
            // Printen data
            printString(data);
            // New line
            printString("\n\n");
        }
    } else {
        // Count optellen
        count++;
    }
}

// Tweede timer die checkt of de waarde gelijk is als statement
ISR(TIMER1_OVF_vect)
{
    // Als de temperatuur hoger is van 37 graden celsius
    if (I_Temp > 37)
    {   
        // Teken koorts symbool
        drawKoorts();
    }
    else
    {
        // Teken smiley symbool
        drawGeenKoorts();
    }
}

int main(void)
{

    // USART initialiseren
    initUSART();

    // 1 Seconden delay
    _delay_ms(1000);

    // Matrix initialiseren
    matrixInit();

    // Timer overflow initialiseren
    initTimerOverflowCapture();

    while (1)
    {
    }
}