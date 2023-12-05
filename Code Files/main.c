#include "configurationBits.c"
#include "uart.h"
#include "bt832.h"
#include "dht11.h"
#include <xc.h>
#include <stdbool.h>
#define _XTAL_FREQ 4000000

#define ledPin LATA2
void ledBlink(void){
    ledPin = 1;              
    __delay_ms(400);
    ledPin = 0;              
}

void main(void) {
    /*Register configuration*/
    OSCCON = 0b11101011;    //Sets the internal oscillator at 4MHz.
    WDTCON = 0b00011000;    //Sets Watchdog interval for 1 second.
    ANSELA = 0;             //Makes all pins digital I/O.
    RXDTSEL = 1;            //RX Function is on RA5.
    TXCKSEL = 1;            //TX Function is on RA4.
    
    TRISA0 = 1;             //Sets Pin 0 as a digital input (sensor).
    TRISA1 = 0;             //Sets Pin 1 as a digital output (bt832 UART wakeup).
    TRISA2 = 0;             //Sets Pin 2 as a digital output (led).
    LATA1 = 0;              //Pulls the bt832's GPIO26 Pin low to wake up the UART.
    LATA1 = 1;              //Pulls the bt832's GPIO26 Pin high.
    
    /*Initialization*/
    ledBlink();
    uart_start(9600);
    bt832_command("AT");            //Cleans bt832 receiver buffer.
    CLRWDT();
    bt832_setName("Temp&Hum");
    bt832_advertisingInterval("0100");
    bt832_save();

    while(1){
        dht11_read();
        bt832_send(temperatureInteger,temperatureDecimal,humidityInteger,humidityDecimal);
        bt832_advertisingStart();
        __delay_ms(200);
        bt832_sleep(AllOff);
        SLEEP();
        bt832_wakeUp();                 //Reactivates the bt832's uart.
    }
    return;
}