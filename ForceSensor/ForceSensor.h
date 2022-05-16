#ifndef FORCESENSOR_H
#define FORCESENSOR_H

#include "bmp3.h"
#include "bmp3_funcs.h"
#include "neural_nets.h"

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

class ForceSensor{
public:
    ForceSensor(int channel_number, NeuralNet *neural_net);
    void Sample();
    void Initialize();
    void Calibrate();
    void Evaluate();
    
    int _channel;
    int raw_data[8];
    int offsets[8];
    int offset_data[8];
    float input_data[8];
    float output_data[5];
    
    
private:
    void config_dev(struct bmp3_dev *dev, int channel);
    NeuralNet *_net;
    uint8_t sensor_comp;
    
    
    float l1[12]; // to be evaluated on-line
    float l2[64]; //[25];
    float l3[64]; //[5];
    float l4[5];
    // TODO: convert this into a struct array?
    struct bmp3_dev s1; // sets up dev as a 'bmp3_dev structure' w/ associated variables
    struct bmp3_dev s2;
    struct bmp3_dev s3;
    struct bmp3_dev s4;
    struct bmp3_dev s5;
    struct bmp3_dev s6;
    struct bmp3_dev s7;
    struct bmp3_dev s8;
    // TODO: convert this into a struct array?
    struct bmp3_data data1; // structs to store sensor data
    struct bmp3_data data2;
    struct bmp3_data data3;
    struct bmp3_data data4;
    struct bmp3_data data5;
    struct bmp3_data data6;
    struct bmp3_data data7;
    struct bmp3_data data8;
};

#endif
