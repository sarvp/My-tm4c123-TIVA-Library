/*
 * PI.c
 *
 *  Created on: 12-Sep-2023
 *      Author: Sarvjit
 */


#include "PI.h"

#include<stdio.h>

#ifndef UART_H_
#include"UART.h"
#endif

void PIController_Init(PIController *pi) {

    /* Clear controller variables */
    pi->integrator = 0.0f;
    pi->prevError  = 0.0f;

    pi->differentiator  = 0.0f;
    pi->prevMeasurement = 0.0f;

    pi->out = 0.0f;

}

char d_str[100] ;
float PIController_Update(PIController *pi, float setpoint, float measurement) {

    /*
    * Error signal
    */
    float error = setpoint - measurement;


    /*
    * Proportional
    */
    float proportional = pi->Kp * error;


    /*
    * Integral
    */
    pi->integrator = pi->integrator + 0.5f * pi->Ki * pi->T * (error + pi->prevError);

    /* Anti-wind-up via integrator clamping */
    if (pi->integrator > pi->limMaxInt) {

        pi->integrator = pi->limMaxInt;

    } else if (pi->integrator < pi->limMinInt) {

        pi->integrator = pi->limMinInt;

    }


    /*
    * Derivative (band-limited differentiator)
    */

    pi->differentiator = -(2.0f * pi->Kd * (measurement - pi->prevMeasurement)   /* Note: derivative on measurement, therefore minus sign in front of equation! */
                        + (2.0f * pi->tau - pi->T) * pi->differentiator)
                        / (2.0f * pi->tau + pi->T);


    /*
    * Compute output and apply limits
    */
    pi->out = proportional + pi->integrator + pi->differentiator;

    if (pi->out > pi->limMax) {

        pi->out = pi->limMax;

    } else if (pi->out < pi->limMin) {

        pi->out = pi->limMin;

    }

    /* Store error and measurement for later use */
    pi->prevError       = error;
    pi->prevMeasurement = measurement;

    /* Return controller output */
//    sprintf(d_str,"proportional = %d\n", (int)(pi->out));
//    uart0_send_str(d_str);
    return pi->out;

}
