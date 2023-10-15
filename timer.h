/*
 * timer.h
 *
 *  Created on: 15-Apr-2023
 *      Author: Sarvjit
 */

#ifndef TIMER_H_
#define TIMER_H_





#endif /* TIMER_H_ */

#include <stdint.h>

#include <string.h>

#include "D:/ti/TivaWare_C_Series-2.2.0.295/TivaWare_C_Series-2.2.0.295/inc/tm4c123gh6pm.h"

void WTIMER3_INIT(void);

void TIMER0_INIT(void);

void set_TIMER0_L(float cnt);

void start_TIMER0_A();

void stop_TIMER0_A();

void set_TIMER0_cnt(long cnt);

long read_TIMER0_cnt(void);

extern const int half_step_seq[8] ;

extern const int full_step_seq[7] ;

extern volatile int sequence ;

extern int DIR ;
