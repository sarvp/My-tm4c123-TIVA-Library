/*
 * L298N H Bridge Driver using PWM
 * Sarvjit Ajit Patil 20862
 * Date : 08/08/2023
 */



/*
 * main.c
 */
#include <stdio.h>

#include <stdint.h>

#include <string.h>

#include <stdlib.h>

#include "D:/ti/TivaWare_C_Series-2.2.0.295/TivaWare_C_Series-2.2.0.295/inc/tm4c123gh6pm.h"

#include"SysTick.h"

#include"PWM.h"

#ifndef ADC_H_
#include"ADC.h"
#endif

#include"GPIO.h"

#ifndef UART_H_
#include"UART.h"
#endif

#ifndef QEI_H_
#include "QEI.h"
#endif

// #include"LCD.h"

// #include"utils.h"

#ifndef TIMER_H_
#include"timer.h"
#endif

#ifndef STEPPER_H_
#include"stepper.h"
#endif

//#ifndef PI_H_
//#include"PI.h"
//#endif

//#define DEBUG

// #include"ultrasonic.h"

void delayMs(int n);

#define PWM_FRE 20000

extern char RX1_BUF[200], RX0_BUF[200], RX1_CMD[200] ;

extern int rx0_command_flag ;

extern unsigned long ms_counter, h_us_cnt ;

extern int dir, done_flag ;

volatile int ADC_Voltage, ADC_Current ;

extern int ADC_Sel_cnt ;

float pos = 0 ;
long cur_cnt = 0 ;
char str[100] ;

//const int half_step_seq[8] = {0x00000080, 0x000000C0, 0x00000040, 0x00000060, 0x00000020, 0x00000030, 0x00000010, 0x00000090} ;
const int half_step_seq[8] = {0x00000080, 0x000000A0, 0x00000020, 0x00000060, 0x00000040, 0x00000050, 0x00000010, 0x00000090} ;
const int full_step_seq[7] = {0xA0, 0x60, 0x50, 0x90} ;

extern unsigned long h_us_stepper_counter ;

extern void PWM_Start(void);

/* Set Phase currents (in Amps) */

#define SET_CURR_A 1.5

#define SET_CURR_B 1.5

/* Set RPM */

int RPM_O = 0, RPM_S = 35, RPM_M = 0 ;

int K_P = 10;
int K_I = 0;

float set_Curr_A_ADC = ((SET_CURR_A * 4095) / 3.3);

float set_Curr_B_ADC = ((SET_CURR_B * 4095) / 3.3);

int I_Set = 0 ;

volatile int sequence = 0;

float Voltage, Current, R_RPM, Position;

/* Set sampling time Ts for PI * 100 us */
#define del_T 250

#define MAX_RPM 150
#define MIN_RPM 15

#define MAX_L_VAL 160000
#define MIN_L_VAL 16000

///* Controller parameters */
//#define PID_KP  1.0f
//#define PID_KI  0.0
//#define PID_KD  0
//
//#define PID_TAU 0.02f
//
//#define PID_LIM_MIN -500.0f
//#define PID_LIM_MAX  500.0f
//
//#define PID_LIM_MIN_INT -500.0f
//#define PID_LIM_MAX_INT  500.0f
//
//#define SAMPLE_TIME_S 0.01f

float rpm_m;

int DIR = 1 ;

int main(void)
{
    EnableInterrupts() ;

    Systick_init();
//    GPIOA_INIT();
    GPIOB_INIT();
//    GPIOC_INIT();
//    GPIOD_INIT();
//    GPIOE_INIT();
    GPIOF_INIT();

//    TIMER0_INIT();

    uart0_init();
//    uart1_init();

    uart0_send_str("Welcome to UART0\n");
    uart0_send_str("This is for debugging.\n");

    QEI_0_INIT();

    /* Init PWM for micro-stepping */

    //    float set_duty = 0.5 ;
//    PWM_0_SYNC() ;

//    M0PWM2_init(Ts);
//    M0PWM3_init(Ts);       /* PWM is used as it triggers the ADC */
    M0PWM4_init(100*del_T);
//    M0PWM5_init(Ts);
//
//    PWM_Start();

//    M0PWM5_init(PWM_FRE);
//    M0PWM4_set(set_duty);
//    M0PWM2_set(set_duty);
//    PWM_0_SYNC();

//    M0PWM5_set(set_duty);

//    ADC_0_SS_3_INIT() ;

//    ADC_0_SS_0_INIT();

//    ADC_0_SS_1_INIT();

//    ADC_1_SS_1_INIT();


    /* Initialise PID controller */
//       PIController pid = { PID_KP, PID_KI, -PID_KD,
//                             PID_TAU,
//                             PID_LIM_MIN, PID_LIM_MAX,
//                             PID_LIM_MIN_INT, PID_LIM_MAX_INT,
//                             SAMPLE_TIME_S };
//
//    PIController_Init(&pid);

    TIMER0_INIT();

    set_TIMER0_L(15000/160);

    start_TIMER0_A();

//    TIMER0_TAILR_R = 79999;

    RPM_O = RPM_S;

    int Out = 0;

    float rpm_m ;

    float rpm_error ;

    float P_O ;

    float I_O ;

    float PI_O ;

    while(1)
    {
//        if ( rx0_command_flag )
//        {
//            I_Set = atoi(RX0_BUF);
//
////            update_PWM(I_Set, 2) ;
////            RPM_S = I_Set ;
//
////            sprintf(str,"Set RPM = %d.%d\n", RPM_M, 0);
////            uart0_send_str(str);
//
////            delayMs(20) ;
////
////            sprintf(str,"Set Position = %d.%d\n", I_Set, 0);
////            uart0_send_str(str);
////            Position = ( QEI0_POS_R * 360 ) / ( 8192 ) ;
////            Position = Position * 1000 ;
////
////            int P_i = (int)(Position) / 1000;
////            int P_f = (int) (Position) % 1000 ;
////            sprintf(str,"Read Position = %d.%d\n", P_i * 200, P_f);
////            uart0_send_str(str);
////
////            float rpm = (6400 * ( (QEI0_SPEED_R) ) * 60) / (2048 * 4);
////            rpm = rpm * 1000 ;
////
////            int R_i = (int)(rpm) / 1000;
////            int R_f = (int) (rpm) % 1000 ;
////            sprintf(str,"RPM = %d.%d\n", R_i, R_f);
////            uart0_send_str(str);
//
//
//            rx0_command_flag = 0 ;
//
//        }

//        rpm_m = (6400 * ( (QEI0_SPEED_R) ) * 60) / (2048 * 4);
//
//        RPM_O = 0 ;
////        RPM_O = PIController_Update(&pid, RPM_S, rpm_m);
////        sprintf(str,"RPM_O = %d\n", (int)RPM_O);
////        uart0_send_str(str);

        /* Half Step/ Full Step */
//
//        if ( h_us_stepper_counter > (15000/(120)) )
//        {
//            h_us_stepper_counter = 0 ;
//
//            sequence = sequence + DIR;
//            if( sequence > 7 )
//            {
//                sequence = 0 ;
//            }
//            else if( sequence < 0 )
//            {
//                sequence = 7 ;
//            }
//
//        }
//
//        GPIO_PORTB_DATA_R = half_step_seq[sequence] ;
//
        /*PI*/
        if(h_us_stepper_counter > del_T)
        {
            h_us_stepper_counter = 0;

            rpm_m = (100 * ( (QEI0_SPEED_R) ) * 60) / (2048 * 4);

            rpm_error = RPM_S - rpm_m;

            P_O = rpm_error ;

            I_O = K_I ;

            PI_O = P_O + I_O ;

            Out = (int)PI_O;

//            if(Out > MAX_RPM)
//            {
//                Out = MAX_RPM ;
//            }
//            else if( Out < -MAX_RPM )
//            {
//                Out = -MAX_RPM;
//            }

            int P_Out = 4000 * Out ;

//            stop_TIMER0_A();
//
            TIMER0_TAILR_R = 160000 - P_Out - 1;

//            TIMER0_TAILR_R = 160000 - 80000 - 1;
//
//            start_TIMER0_A();

//            stop_TIMER0_A();
//            set_TIMER0_L(15000/(RPM_S));
//            start_TIMER0_A();
        }
        /* Display Parameters */
        if(h_us_cnt > 100000)
        {
            h_us_cnt = 0 ;
            float rpm = (100 * ( (QEI0_SPEED_R) ) * 60) / (2048 * 4);
//            rpm = (6400 * ( (QEI0_SPEED_R) ) * 60) / (2048 * 4);

//            rpm = rpm * 1000 ;
//
//            int R_i = (int)(rpm) / 1000;
//            int R_f = (int) (rpm) % 1000 ;
//            sprintf(str,"RPM = %d.%d\n", R_i, R_f);
//            uart0_send_str(str);

//            sprintf(str,"RPM_O = %d\n", (RPM_S + RPM_O));
//            uart0_send_str(str);
//
            sprintf(str,"Out = %d\n", (int)rpm_error);
            uart0_send_str(str);

            sprintf(str,"RPM_M = %d\n", (int)rpm);
            uart0_send_str(str);

        }

//        WaitForInterrupt();

    }
}

void delayMs( int n )
{
    int i, j ;

    for(i = 0; i < n ; i ++)
    {
        for(j = 0; j < 2000; j++);
    }
}
