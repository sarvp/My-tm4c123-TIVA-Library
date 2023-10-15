/*
 * PI.h
 *
 *  Created on: 12-Sep-2023
 *      Author: Sarvjit
 */

#ifndef PI_H_
#define PI_H_


typedef struct {
    /* Controller gains */
    float Kp;
    float Ki;
    float Kd;
    /* Derivative low-pass filter time constant */
    float tau;
    /* Output limits */
    float limMin;
    float limMax;

    /* Integrator limits */
    float limMinInt;
    float limMaxInt;

    /* Sample time (in seconds) */
    float T;
    /* Controller "memory" */
    float integrator;
    float prevError;            /* Required for integrator */
    float differentiator;
    float prevMeasurement;      /* Required for differentiator */
    /* Controller output */
    float out;
} PIController;
void  PIController_Init(PIController *pi);
float PIController_Update(PIController *pi, float setpoint, float measurement);

#endif /* PI_H_ */
