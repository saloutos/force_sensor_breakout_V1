#ifndef BMP3_FUNCS_H
#define BMP3_FUNCS_H

#include "mbed.h"


// hardware prototypes
extern DigitalOut dec1;
extern DigitalOut bit01;
extern DigitalOut bit11;
extern DigitalOut bit21;
extern SPI spi1;
extern DigitalOut dec2;
extern DigitalOut bit02;
extern DigitalOut bit12;
extern DigitalOut bit22;
extern SPI spi2;
extern DigitalOut dec3;
extern DigitalOut bit03;
extern DigitalOut bit13;
extern DigitalOut bit23;
extern SPI spi3;

// function prototypes
void writeLow1(uint8_t pin);
void writeHigh1();
void writeLow2(uint8_t pin);
void writeHigh2();
void writeLow3(uint8_t pin);
void writeHigh3();

int8_t bmp_spi1_read(uint8_t cspin, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t bmp_spi1_write(uint8_t cspin, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

int8_t bmp_spi2_read(uint8_t cspin, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t bmp_spi2_write(uint8_t cspin, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

int8_t bmp_spi3_read(uint8_t cspin, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t bmp_spi3_write(uint8_t cspin, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

void bmp_delay_ms(uint32_t msec);

#endif
