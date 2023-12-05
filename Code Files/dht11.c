#include <stdbool.h>
#include <xc.h>
#include "dht11.h"

void dht11_Start(void){
    DHT11_DataDirection = 0;    // Set DHT11 data pin as output
    DHT11_DataPin = 0;          // Set data pin to low
    __delay_ms(20);             // Delay for 20ms
    DHT11_DataPin = 1;          // Set data pin to high
    __delay_us(30);             // Delay for 30us
    DHT11_DataDirection = 1;    // Set DHT11 data pin as input
}
char dht11_ReadPackage(void){
    char data = 0;
    for (char i = 0; i < 8; i++) {
        while (!DHT11_DataPin);         // Wait for data to go high
        __delay_us(35);                 
        if (DHT11_DataPin == 0) {       //If it was a short pulse (0)
            data = (data<<1);           //shifts byte to the left and adds a 0 to the right
        }
        else {                          //If it was a long pulse (1)
            data = ((data<<1) | 1);     //shifts byte to the left and adds a 1 to the right
        }
        while (DHT11_DataPin);          // Wait for data to go low
    }
    return data;
}
void dht11_read(void){
    dht11_Start();
    while (!DHT11_DataPin);                     //Wait for response.
    while (DHT11_DataPin);                      //Wait for response.
    humidityInteger     = dht11_ReadPackage();
    humidityDecimal     = dht11_ReadPackage();
    temperatureInteger  = dht11_ReadPackage();
    temperatureDecimal  = dht11_ReadPackage();
    checksum            = dht11_ReadPackage();
    //(checksum == (humidityInteger + humidityDecimal +  temperatureInteger + temperatureDecimal)){    //verifies checksum 
}

