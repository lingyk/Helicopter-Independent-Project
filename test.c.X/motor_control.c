#include "motor_control.h"
#include <xc.h>

void init_motor(){
    RPA0Rbits.RPA0R = 0b0101;
    RPB13Rbits.RPB13R = 0b0101;
    
    T2CONbits.TCKPS = 0;
    PR2 = 2399;
    TMR2 = 0;
    
    OC1CONbits.OCM = 0b110;
    OC1RS = 0;
    OC1R = 0;
    
    OC4CONbits.OCM = 0b110;
    OC4RS = 0;
    OC4R = 0;
    
    T2CONbits.ON = 1;
    OC1CONbits.ON = 1;
    OC4CONbits.ON = 1;
}

void init_encoder(){
    T2CKRbits.T5CKR = 0b0100;
    T3CKRbits.T3CKR = 0b0100;
    
    T5CONbits.TCS = 1;
    PR5 = 0xFFFF;
    TMR5 = 0;
    T5CONbits.ON = 1;
    
    T3CONbits.TCS = 1;
    PR3 = 0xFFFF;
    TMR3 = 0;
    T3CONbits.ON = 1;
}

void init_controller(){
    T4CONbits.TCKPS = 0b101;
    PR4 = 29999;
    TMR4 = 0;
    T4CONbits.ON = 1;
    IPC4bits.T4IP = 4;
    IFS0bits.T4IF = 0;
    IEC0bits.T4IE = 1;
}

int read_encoder1(){
    return TMR5;
}

int read_encoder1(){
    return TMR3;
}

void reset_encoder(){
    TMR5 = 0;
    TMR3 = 0;
}

float pi_control(int reference, int actual, int motor_num){
    int err;
    float u;
    
    err = reference - actual;
    if(ki * (eint[motor_num - 1] + err) <= 1.0){
        eint[motor_num - 1] += err;
    }
    
    u = (float) (kp * err + ki * eint[motor_num -1]);
    
    if(u > 100.0){
        u = 100.0;
    }
    else if(u < 0.0){
        u = 0.0;
    }
    
    return u/100.0;
}