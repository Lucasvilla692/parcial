// Proyecto lucas y valeria
#include "mcc_generated_files/mcc.h"
#include  <xc.h>

struct trama {
    uint16_t header;
    char state;
    float voltaje1;
    float voltaje2;
    float voltaje3;
    uint8_t otros;
    uint8_t cheksum;
};


// funcion para crear el cheksum

uint8_t checksum(void* data, unsigned char size_trama) {
    uint8_t contador = 0;
    unsigned char* puntero = data;
    unsigned char i;
    contador = puntero[0];
    for (i = 0; i < size_trama - 1; i++) {
        contador = contador^puntero[i + 1];
    }
    return (contador);
}
// funcion para enviar la trama
void enviar_trama(void* data, unsigned char size_trama) {
    unsigned char* puntero = data;
    unsigned char i;
    for (i = 0; i < size_trama; i++) {
        printf("%02X", puntero[i]);

    }
}

struct trama trama2;
unsigned char entrada;
void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    while (1) {
        ADC_Initialize();
        trama2.header = 0XFEEF;
        trama2.state = 0X41;
        trama2.voltaje1 = (ADC_GetConversion(channel_AN0)/ 1023.0)*5000.0;
        __delay_ms(10);
        trama2.voltaje2 = (ADC_GetConversion(channel_AN1)/ 1023.0)*5.0;
        __delay_ms(10);
        trama2.voltaje3 = (ADC_GetConversion(channel_AN2)/ 1023.0)*5.0;
        __delay_ms(10);
        trama2.otros = 0.0;
        trama2.cheksum = checksum(&trama2.state, sizeof (trama2) - 3);
        enviar_trama(&trama2, sizeof (trama2));
        __delay_ms(100);
        
        

    }
}