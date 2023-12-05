#ifndef DHT11_H
#define	DHT11_H

#include <stdbool.h>

#define _XTAL_FREQ 4000000

/*Required Definitions*/
#define DHT11_DataDirection TRISA0
#define DHT11_DataPin       RA0

/*Global Variables*/
char humidityInteger    =   0;
char humidityDecimal    =   0;
char temperatureInteger =   0;
char temperatureDecimal =   0;
char checksum           =   0;

/*Function's prototypes*/
void dht11_Start(void);
void dht11_Response(void);
char dht11_ReadPackage(void);
void dht11_read(void);

#endif	/* DHT11_H */

