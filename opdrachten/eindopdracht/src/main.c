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

#define DHT11_PIN 6
#define DS_PORT PORTC
#define DS_PIN 0
#define ST_CP_PORT PORTC
#define ST_CP_PIN 1
#define SH_CP_PORT PORTC
#define SH_CP_PIN 2

#define DS_low() DS_PORT &= ~_BV(DS_PIN)
#define DS_high() DS_PORT |= _BV(DS_PIN)
#define ST_CP_low() ST_CP_PORT &= ~_BV(ST_CP_PIN)
#define ST_CP_high() ST_CP_PORT |= _BV(ST_CP_PIN)
#define SH_CP_low() SH_CP_PORT &= ~_BV(SH_CP_PIN)
#define SH_CP_high() SH_CP_PORT |= _BV(SH_CP_PIN)

uint8_t c = 0, I_RH, D_RH, I_Temp, D_Temp, CheckSum;

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

void matrixInit()
{
    // Output pinnen aanzetten
    DDRC = 0b00000111;
    PORTC = 0b00000000;
}

void maxtrix_output(unsigned int __led_state)
{
    SH_CP_low();
    ST_CP_low();
    for (int i = 0; i < 16; i++)
    {
        if ((_BV(i) & __led_state) == _BV(i))
            DS_high();
        else
            DS_low();

        SH_CP_high();
        SH_CP_low();
    }
    ST_CP_high();
}

void initTimerOverflowCapture()
{
    // Starten van timer met 64ms delay 
    TIMSK0 |= _BV(TOIE0);

    // Starten van timer met 64ms delay 
    TIMSK1 |= _BV(TOIE1);

    // Starten van de timer en prescaler op 64ms
    TCCR0B |= _BV(CS02) | _BV(CS00);

    // Starten van de timer en prescaler op 64ms
    TCCR1B |= _BV(CS10);

    // interrupts aan
    sei();
}

ISR(TIMER0_OVF_vect) {

    printString("Error");

    // char data[5];

    // dht11_measure();

    //     if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
    //     {
    //         printString("Error");
    //     }

    //     else
    //     {
    //         itoa(I_RH, data, 10);
    //         printString(data);
    //         printString(".");

    //         itoa(D_RH, data, 10);
    //         printString(data);
    //         printString("%");

    //         itoa(I_Temp, data, 10);
    //         printString(data);
    //         printString(".");

    //         itoa(D_Temp, data, 10);
    //         printString(data);
    //         printString("°C ");

    //         itoa(CheckSum, data, 10);
    //         printString(data);
    //         printString(" \n\n");
    //     }

    //     _delay_ms(1000);
}


int main(void)
{

    initUSART();

    _delay_ms(1000);

    matrixInit();

    initTimerOverflowCapture();


    while (1)
    {
        
    }
}
