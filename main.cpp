/// firmware for SPI force sensor breakout board
/// Written by Andrew SaLoutos, loosely based on motor control code from benkatz
/// Written for the STM32F446, but could be ported to other STM MCU's without much effort

#define REST_MODE           0
#define PRINT_NN_MODE       1
#define PRINT_RAW_MODE      2

#define VERSION_NUM "0.02"

#include "mbed.h"
#include "math_ops.h"  
#include "ForceSensor.h"
#include "bmp3_funcs.h"
#include "bmp3.h"
#include "neural_nets.h"


// new limits for force sensors
#define FT_MIN -20.0f
#define FT_MAX 20.0f 
#define FN_MIN -30.0f
#define FN_MAX 30.0f
#define ANG_MIN -45.0f
#define ANG_MAX 45.0f

Serial pc(PA_2, PA_3);
DigitalOut led(PC_5);

// Initialize SPI hardware
SPI spi1(PA_7, PA_6, PA_5); // MOSI, MISO, SCK
DigitalOut dec1(PA_4);
DigitalOut bit01(PC_6);
DigitalOut bit11(PC_7);
DigitalOut bit21(PC_8);

SPI spi2(PB_15, PB_14, PB_13);
DigitalOut dec2(PB_12);
DigitalOut bit02(PA_8);
DigitalOut bit12(PA_9);
DigitalOut bit22(PA_10);

SPI spi3(PC_12, PC_11, PB_3);
DigitalOut dec3(PA_15);
DigitalOut bit03(PC_13);
DigitalOut bit13(PC_14);
DigitalOut bit23(PC_15);

// initialize neural net structs
extern NeuralNet sensor28;
extern NeuralNet sensor31;

// initialize force sensors on each channel with corresponding neural net model
ForceSensor channel1(1, &sensor28); 
ForceSensor channel2(2, &sensor31); 

// setup for state machine and sensor interrupts
volatile int state = REST_MODE;
volatile int send_data_flag = 0;
Ticker send_data;
void send_new_data(){
    send_data_flag = 1;
} 

void enter_menu_state(void){
    
    // TODO: make more useful menu
    printf("\n\r\n\r\n\r");
    printf(" Commands:\n\r");
    wait_us(10);
    printf(" n - Print Force Outputs\n\r");
    wait_us(10);
    printf(" r - Print Raw Sensor Values\n\r");
    wait_us(10);
    printf(" esc - Exit to Menu\n\r");
    wait_us(10);
    }
    
    
/// Manage state machine with commands from serial terminal or configurator gui ///
/// Called when data received over serial ///
void serial_interrupt(void){
    while(pc.readable()){
        char c = pc.getc();
        if(c == 27){
            state = REST_MODE;
            led = 0;
            enter_menu_state();
        }
        if(state == REST_MODE){
            switch (c){
                case 'n':
                    state = PRINT_NN_MODE;
                    pc.printf("Printing NN outputs.\n\r");
                    break;
                case 'r':
                    state = PRINT_RAW_MODE;
                    pc.printf("Printing raw outputs.\n\r");
                    break;
                }
        }  
    }
}

       
int main() {

    
    
    pc.baud(115200);                                                            // set serial baud rate
    wait(.01);
        
    // initialize SPI channels
    channel1.Initialize();
    channel2.Initialize();
    // calibrate sensor offsets
    channel1.Calibrate();
    channel2.Calibrate();
    
    pc.attach(&serial_interrupt);        // attach serial interrupt
    enter_menu_state();
    
    // attach main interrupt here
    send_data.attach_us(&send_new_data,10000); // 5000us = 5ms => 200Hz (10000 = 10 ms = 100 Hz)
    
    while(1) {

        if(send_data_flag==1){
            led = 1;
            // sample force sensors
            // sampling all 3 sensors taks 0.002774 seconds
            channel1.Sample(); 
            channel2.Sample();
            // evaluating all 3 nets takes 0.001120 seconds
            channel1.Evaluate();
            channel2.Evaluate();    
            // for printing, reduce sampling frequency to 100Hz!   
            if (state==PRINT_RAW_MODE){
                // printing raw data from all 3 sensors takes 0.001722 seconds
                pc.printf("%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d \n\r", channel1.raw_data[0],channel1.raw_data[1],channel1.raw_data[2],
                    channel1.raw_data[3],channel1.raw_data[4],channel1.raw_data[5],channel1.raw_data[6],channel1.raw_data[7]);   
                pc.printf("%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d \n\r", channel2.raw_data[0],channel2.raw_data[1],channel2.raw_data[2],
                    channel2.raw_data[3],channel2.raw_data[4],channel2.raw_data[5],channel2.raw_data[6],channel2.raw_data[7]);   
                pc.printf("\n\r\n\r");
            }
            if (state==PRINT_NN_MODE){
                // printing output data from all 3 sensors takes 0.001415 seconds                      
                // print a single line for each sample
//                pc.printf("%2.4f,%2.4f,%2.4f,%2.4f,%2.4f,%2.4f,%2.4f,%2.4f,%2.4f,%2.4f,%2.4f,%2.4f,%2.4f,%2.4f,%2.4f\n\r",
                // print over three lines
                pc.printf("%2.4f,%2.4f,%2.4f,%2.4f,%2.4f\n\r%2.4f,%2.4f,%2.4f,%2.4f,%2.4f\n\r\n\r\n\r",
                    channel1.output_data[0],channel1.output_data[1],
                    channel1.output_data[2],channel1.output_data[3],channel1.output_data[4],
                    channel2.output_data[0],channel2.output_data[1],channel2.output_data[2],
                    channel2.output_data[3],channel2.output_data[4]); 
                
            }
            
            // clear flag
            send_data_flag = 0;
            led = 0;
  
         }

    }
}
