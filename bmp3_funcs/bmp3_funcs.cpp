#include "bmp3_funcs.h"

// write cs pin on channel 1
void writeLow1(uint8_t pin){
    dec1.write(0);
    if (pin == 1){
        bit01.write(0);
        bit11.write(0);
        bit21.write(0);
    }
    else if (pin == 2){
        bit01.write(1);
        bit11.write(0);
        bit21.write(0);
    }
    else if (pin == 3){
        bit01.write(0);
        bit11.write(1);
        bit21.write(0);
    }
    else if (pin == 4){
        bit01.write(1);
        bit11.write(1);
        bit21.write(0);
    }
    else if (pin == 5){
        bit01.write(0);
        bit11.write(0);
        bit21.write(1);
    }
    else if (pin == 6){
        bit01.write(1);
        bit11.write(0);
        bit21.write(1);
    }
    else if (pin == 7){
        bit01.write(0);
        bit11.write(1);
        bit21.write(1);
    }
    else if (pin == 8){
        bit01.write(1);
        bit11.write(1);
        bit21.write(1);
    }
}

void writeHigh1(){
    dec1.write(1); // write all pins high by disabling the decoder
}

// write cs pin on channel 2
void writeLow2(uint8_t pin){
    dec2.write(0);
    if (pin == 1){
        bit02.write(0);
        bit12.write(0);
        bit22.write(0);
    }
    else if (pin == 2){
        bit02.write(1);
        bit12.write(0);
        bit22.write(0);
    }
    else if (pin == 3){
        bit02.write(0);
        bit12.write(1);
        bit22.write(0);
    }
    else if (pin == 4){
        bit02.write(1);
        bit12.write(1);
        bit22.write(0);
    }
    else if (pin == 5){
        bit02.write(0);
        bit12.write(0);
        bit22.write(1);
    }
    else if (pin == 6){
        bit02.write(1);
        bit12.write(0);
        bit22.write(1);
    }
    else if (pin == 7){
        bit02.write(0);
        bit12.write(1);
        bit22.write(1);
    }
    else if (pin == 8){
        bit02.write(1);
        bit12.write(1);
        bit22.write(1);
    }
}

void writeHigh2(){
    dec2.write(1); // write all pins high by disabling the decoder
}

// write cs pin on channel 3
void writeLow3(uint8_t pin){
    dec3.write(0);
    if (pin == 1){
        bit03.write(0);
        bit13.write(0);
        bit23.write(0);
    }
    else if (pin == 2){
        bit03.write(1);
        bit13.write(0);
        bit23.write(0);
    }
    else if (pin == 3){
        bit03.write(0);
        bit13.write(1);
        bit23.write(0);
    }
    else if (pin == 4){
        bit03.write(1);
        bit13.write(1);
        bit23.write(0);
    }
    else if (pin == 5){
        bit03.write(0);
        bit13.write(0);
        bit23.write(1);
    }
    else if (pin == 6){
        bit03.write(1);
        bit13.write(0);
        bit23.write(1);
    }
    else if (pin == 7){
        bit03.write(0);
        bit13.write(1);
        bit23.write(1);
    }
    else if (pin == 8){
        bit03.write(1);
        bit13.write(1);
        bit23.write(1);
    }
}

void writeHigh3(){
    dec3.write(1); // write all pins high by disabling the decoder
}

// General Read and Write functions for channel 1
// read function: |0x80 done in library, dummy byte taken care of in library
int8_t bmp_spi1_read(uint8_t cspin, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
    writeLow1(cspin);
    spi1.write(reg_addr); // send read command to chip_id register (reg 0x00)
    for(int i = 0; i < len; i++){
        *(reg_data+i) = spi1.write(0x00); // read in 2nd byte = chip_id
    }
    writeHigh1();
    return 0;
}

int8_t bmp_spi1_write(uint8_t cspin, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
    writeLow1(cspin);
    spi1.write(reg_addr);
    if (len>1) {
        for(int i = 0; i < len-1; i++){
            spi1.write(*(reg_data+i)); // send alternating register address and register bytes in multi write
        }
    }
    else{
        spi1.write(reg_data[0]);
    }    
    writeHigh1();
    return 0;
}

// General Read and Write functions for channel 2
// read function: |0x80 done in library, dummy byte taken care of in library
int8_t bmp_spi2_read(uint8_t cspin, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
    writeLow2(cspin);
    spi2.write(reg_addr); // send read command to chip_id register (reg 0x00)
    for(int i = 0; i < len; i++){
        *(reg_data+i) = spi2.write(0x00); // read in 2nd byte = chip_id
    }
    writeHigh2();
    return 0;
}

int8_t bmp_spi2_write(uint8_t cspin, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
    writeLow2(cspin);
    spi2.write(reg_addr);
    if (len>1) {
        for(int i = 0; i < len-1; i++){
            spi2.write(*(reg_data+i)); // send alternating register address and register bytes in multi write
        }
    }
    else{
        spi2.write(reg_data[0]);
    }    
    writeHigh2();
    return 0;
}

// General Read and Write functions for channel 3
// read function: |0x80 done in library, dummy byte taken care of in library
int8_t bmp_spi3_read(uint8_t cspin, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
    writeLow3(cspin);
    spi3.write(reg_addr); // send read command to chip_id register (reg 0x00)
    for(int i = 0; i < len; i++){
        *(reg_data+i) = spi3.write(0x00); // read in 2nd byte = chip_id
    }
    writeHigh3();
    return 0;
}

int8_t bmp_spi3_write(uint8_t cspin, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
    writeLow3(cspin);
    spi3.write(reg_addr);
    if (len>1) {
        for(int i = 0; i < len-1; i++){
            spi3.write(*(reg_data+i)); // send alternating register address and register bytes in multi write
        }
    }
    else{
        spi3.write(reg_data[0]);
    }    
    writeHigh3();
    return 0;
}

// Delay function
void bmp_delay_ms(uint32_t msec){ //delay in milliseconds
    wait_ms(msec); 
}   
    
