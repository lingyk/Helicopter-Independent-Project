#ifndef _MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H

static int enc_ref[2] = {15,15};

static float kp = 10.0;
static float ki = 0.1;

static volatile int eint[2] = {0,0};

void init_motor();
void int_encoder();
void int_controller();
int read_encoder1();
int read_encoder2();
void reset_encoders();
float pi_control(int,int,int);

#endif
