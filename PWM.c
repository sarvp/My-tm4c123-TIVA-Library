/*
 * PWM.c
 *
 *  Created on: 15-Apr-2023
 *      Author: Sarvjit
 */

#include <PWM.h>

#ifndef UART_H_
#include"UART.h"
#endif

void PWM_0_SYNC(void)
{
//    SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0 ;
//
//    while((SYSCTL_RCGCPWM_R & SYSCTL_RCGCPWM_R0)==0){};
//
//    PWM0_CTL_R |= 0x0000000F ;
//    PWM0_SYNC_R |= 0x0000000F ;
}
/* PWM PB4 M0PWM2 */

/*--------------------------------------------M0PWM2--------------------------------------------*/

void M0PWM2_init(int Ts)
{
    //GPIO_PORTE_LOCK_R = 0x4C4F434B;
    SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0 ;

    while((SYSCTL_RCGCPWM_R & SYSCTL_RCGCPWM_R0)==0){};

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1 ;

    while((SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R1)==0){};

    SYSCTL_RCC_R |= (SYSCTL_RCC_USEPWMDIV | SYSCTL_RCC_PWMDIV_4) ;

//    GPIO_PORTE_CR_R |= 0x10;
   // SYSCTL_RCGC0_R |= SYSCTL_RCGC0_PWM0 ;
   // SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
    GPIO_PORTB_AFSEL_R |= 0x10 ; // PB4
    GPIO_PORTB_AMSEL_R &= ~0x10 ;
//    GPIO_PORTB_PCTL_R &= ~ 0x000F0000 ;
    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB4_M0PWM2; //PB4 M0PWM4
    GPIO_PORTB_DEN_R |= 0x10 ;
    //GPIO_PORTB_DIR_R |= 0x10 ;

    PWM0_1_CTL_R &= ~ 0x00000001 ;
    PWM0_1_CTL_R |= 0x00000002 ;
    PWM0_1_INTEN_R |= ( PWM_1_INTEN_TRCNTLOAD | PWM_1_INTEN_INTCNTLOAD ) ;
    PWM0_1_GENA_R |= 0x000000B0 ;
    //PWM0_2_GENB_R = 0x0000008C ;


//    PWM0_1_LOAD_R = (125000/Ts)  ;
    PWM0_1_LOAD_R = (0.125000*Ts) ;

    float dutycycle_init = 0.5 ;

    PWM0_1_CMPA_R = ( 1-dutycycle_init )*(PWM0_1_LOAD_R)  ; // //

//    PWM0_ENUPD_R |= 0x00000030 ;

    /* Interrupt */

//    EnableInterrupts() ;             /* Enable global Interrupt flag (I) */
//
//    PWM0_INTEN_R |= PWM_INTEN_INTPWM2 ;
//
//    NVIC_PRI3_R |= (NVIC_PRI3_R & 0xFFFFFFF1) | 0x0000000A ; /*  priority 5 */
//
//    NVIC_EN0_R |= 0x00001000 ;        /*  Enable interrupt 12 in NVIC */
//
//    PWM0_1_ISC_R |= 0x00000002 ;
//    PWM0_ISC_R |= 0x00000002 ;

    /**/

//    PWM0_1_CTL_R |= 0x00000001 ;
    PWM0_ENABLE_R |= 0x04 ;

}

void M0PWM2_start(void)
{
    PWM0_ENABLE_R |= 0x04 ;
}

void M0PWM2_stop(void)
{
    PWM0_ENABLE_R &= ~0x04 ;
}

void M0PWM2_set_Ts(int Ts)
{
    PWM0_ENABLE_R &= ~ 0x40 ;

    PWM0_1_LOAD_R = (0.125000*Ts) ;

    float dutycycle_init = 0.5 ;

    PWM0_1_CMPA_R = ( 1-dutycycle_init )*(PWM0_1_LOAD_R)   ;

    PWM0_ENABLE_R |= 0x04 ;
}

void M0PWM2_set(float dutycycle)
{
    PWM0_1_CMPA_R = ( 1-dutycycle )*(PWM0_1_LOAD_R) ; // //
}

void M0PWM2_update(int COMPA)
{
//    PWM0_1_CTL_R &= ~ 0x00000001 ;
//    PWM0_ENABLE_R &= ~ 0x10 ;
    PWM0_1_CMPA_R = COMPA ;
//    PWM0_1_CTL_R |= 0x00000001 ;
//    PWM0_ENABLE_R |= 0x04 ;
}

/* PWM PB5 M0PWM3 */

/*--------------------------------------------M0PWM3--------------------------------------------*/

void M0PWM3_init(int Ts)
{
    //GPIO_PORTE_LOCK_R = 0x4C4F434B;
    SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0 ;
    while((SYSCTL_RCGCPWM_R & SYSCTL_RCGCPWM_R0)==0){};

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1 ;

    while((SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R1)==0){};

    SYSCTL_RCC_R |= (SYSCTL_RCC_USEPWMDIV | SYSCTL_RCC_PWMDIV_4) ;

//    GPIO_PORTE_CR_R |= 0x10;
   // SYSCTL_RCGC0_R |= SYSCTL_RCGC0_PWM0 ;
   // SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
    GPIO_PORTB_AFSEL_R |= 0x20 ; // PB5
    GPIO_PORTB_AMSEL_R &= ~0x20 ;
//    GPIO_PORTB_PCTL_R &= ~ 0x000F0000 ;
    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB5_M0PWM3; //PB5 M0PWM3
    GPIO_PORTB_DEN_R |= 0x20 ;
    //GPIO_PORTB_DIR_R |= 0x20 ;

    PWM0_1_CTL_R &= ~ 0x00000001 ;
    PWM0_1_CTL_R |= 0x00000002 ;
    PWM0_1_INTEN_R |= ( PWM_1_INTEN_TRCNTLOAD | PWM_1_INTEN_INTCNTLOAD ) ;
//    PWM0_1_GENA_R |= 0x000000B0 ;
    PWM0_1_GENB_R = 0x00000B00 ;


    PWM0_1_LOAD_R = (0.125000*Ts) ;

    float dutycycle_init = 0.5 ;

    PWM0_1_CMPB_R = ( 1-dutycycle_init )*(PWM0_1_LOAD_R)  ; // //

//    PWM0_ENUPD_R |= 0x000000C0 ;

    /* Interrupt */

//    EnableInterrupts() ;             /* Enable global Interrupt flag (I) */
//
//    PWM0_INTEN_R |= PWM_INTEN_INTPWM2 ;
//
//    NVIC_PRI3_R |= (NVIC_PRI3_R & 0xFFFFFFF1) | 0x0000000A ; /*  priority 5 */
//
//    NVIC_EN0_R |= 0x00001000 ;        /*  Enable interrupt 12 in NVIC */
//
//    PWM0_1_ISC_R |= 0x00000002 ;
//    PWM0_ISC_R |= 0x00000002 ;

    /**/

//    PWM0_1_CTL_R |= 0x00000001 ;
    PWM0_ENABLE_R |= 0x08 ;
//    PWM0_INVERT_R |= 0x08 ;

}

void M0PWM3_start(void)
{
    PWM0_ENABLE_R |= 0x08 ;
}

void M0PWM3_stop(void)
{
    PWM0_ENABLE_R &= ~0x08 ;
}

void M0PWM3_set_Ts(int Ts)
{
    PWM0_ENABLE_R &= ~ 0x08 ;

    PWM0_1_LOAD_R = (0.125000*Ts) ;

    float dutycycle_init = 0.5 ;

    PWM0_1_CMPA_R = ( 1-dutycycle_init )*(PWM0_1_LOAD_R)  ;

    PWM0_ENABLE_R |= 0x08 ;
}

void M0PWM3_set(float dutycycle)
{
    PWM0_1_CMPA_R = ( 1-dutycycle )*(PWM0_1_LOAD_R)  ; // //
}

void M0PWM3_update(int COMPA)
{
//    PWM_Stop();
    PWM0_1_CMPB_R = COMPA ;
//    PWM_Start();
}

/* PWM PE4 M0PWM4 */

/*--------------------------------------------M0PWM4--------------------------------------------*/

void M0PWM4_init(int Ts)
{
    //GPIO_PORTE_LOCK_R = 0x4C4F434B;
    SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0 ;
    while((SYSCTL_RCGCPWM_R & SYSCTL_RCGCPWM_R0)==0){};

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4 ;

    while((SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R4)==0){};

    SYSCTL_RCC_R |= (SYSCTL_RCC_USEPWMDIV | SYSCTL_RCC_PWMDIV_4) ;

//    GPIO_PORTE_CR_R |= 0x10;
   // SYSCTL_RCGC0_R |= SYSCTL_RCGC0_PWM0 ;
   // SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
    GPIO_PORTE_AFSEL_R |= 0x10 ; // E
    GPIO_PORTE_AMSEL_R &= ~0x10 ;
//    GPIO_PORTE_PCTL_R &= ~ 0x000F0000 ;
    GPIO_PORTE_PCTL_R |= GPIO_PCTL_PE4_M0PWM4; //PE4 M0PWM4
    GPIO_PORTE_DEN_R |= 0x10 ;
    //GPIO_PORTE_DIR_R |= 0x10 ;

    PWM0_2_CTL_R &= ~ 0x00000001 ;
    PWM0_2_CTL_R |= 0x00000002 ;
    PWM0_2_INTEN_R |= ( PWM_0_INTEN_TRCNTLOAD | PWM_0_INTEN_INTCNTLOAD ) ;
    PWM0_2_GENA_R |= 0x000000B0 ;
    //PWM0_2_GENB_R = 0x0000008C ;


    PWM0_2_LOAD_R = (0.125000*Ts) ;

    float dutycycle_init = 0.5 ;

    PWM0_2_CMPA_R = ( 1-dutycycle_init )*(PWM0_2_LOAD_R)  ; // //

//    PWM0_ENUPD_R |= 0x00000300 ;

    /* Interrupt */

//    EnableInterrupts() ;             /* Enable global Interrupt flag (I) */
//
//    PWM0_INTEN_R |= PWM_INTEN_INTPWM2 ;
//
//    NVIC_PRI3_R |= (NVIC_PRI3_R & 0xFFFFFFF1) | 0x0000000A ; /*  priority 5 */
//
//    NVIC_EN0_R |= 0x00001000 ;        /*  Enable interrupt 12 in NVIC */
//
//    PWM0_2_ISC_R |= 0x00000002 ;
//    PWM0_ISC_R |= 0x00000002 ;

    /**/

    PWM0_2_CTL_R |= 0x00000001 ;
    PWM0_ENABLE_R |= 0x10 ;

}

void M0PWM4_start(void)
{
    PWM0_ENABLE_R |= 0x10 ;
}

void M0PWM4_stop(void)
{
    PWM0_ENABLE_R &= ~0x10 ;
}

void M0PWM4_set_Ts(int Ts)
{
    PWM0_ENABLE_R &= ~ 0x10 ;

    PWM0_2_LOAD_R = (0.125000*Ts) ;

    float dutycycle_init = 0.5 ;

    PWM0_2_CMPA_R = ( 1-dutycycle_init )*(PWM0_2_LOAD_R) ;

    PWM0_ENABLE_R |= 0x10 ;
}

void M0PWM4_set(float dutycycle)
{
//    if( dutycycle == 0 )
//    {
//        PWM0_2_CMPA_R = ( 1-dutycycle )*(PWM0_2_LOAD_R)  ; // //
//
//    }
//    else if( dutycycle == 1 )
//    {
//        PWM0_2_CMPA_R = ( 1-dutycycle )*(PWM0_2_LOAD_R) + 1 ; // //
//    }
//    else
    {
        PWM0_2_CMPA_R = ( 1-dutycycle )*(PWM0_2_LOAD_R) ; // //
    }
}



/* PWM PE5 M0PWM5 */

/*--------------------------------------------M0PWM5--------------------------------------------*/

void M0PWM5_init(int Ts)
{
    SYSCTL_RCGC0_R |= 0x00100000 ;
    //GPIO_PORTE_LOCK_R = 0x4C4F434B;
    SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0 ;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4 ;
    SYSCTL_RCC_R |= (SYSCTL_RCC_USEPWMDIV | SYSCTL_RCC_PWMDIV_4) ;

//    GPIO_PORTE_CR_R |= 0x10;
   // SYSCTL_RCGC0_R |= SYSCTL_RCGC0_PWM0 ;
   // SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
    GPIO_PORTE_AFSEL_R |= 0x20 ; // E
    //GPIO_PORTE_AMSEL_R = 0x00 ;
//    GPIO_PORTE_PCTL_R &= ~ 0x000F0000 ;
    GPIO_PORTE_PCTL_R |= GPIO_PCTL_PE5_M0PWM5; //PE5 M0PWM5
    GPIO_PORTE_DEN_R |= 0x20 ;
    //GPIO_PORTE_DIR_R |= 0x10 ;

    PWM0_2_CTL_R &= ~ 0x00000001 ;
    PWM0_2_CTL_R |= 0x00000002 ;
    PWM0_2_INTEN_R |= ( PWM_0_INTEN_TRCNTLOAD | PWM_0_INTEN_INTCNTLOAD ) ;
    PWM0_2_GENB_R |= 0x00000B00 ;
    //PWM0_2_GENB_R = 0x0000008C ;


    PWM0_2_LOAD_R = (0.125000*Ts) ;

    float dutycycle_init = 0.5 ;

    PWM0_2_CMPB_R = ( 1-dutycycle_init )*(PWM0_2_LOAD_R)  ; // //

//    PWM0_ENUPD_R |= 0x00000C00 ;

    /* Interrupt */

//    EnableInterrupts() ;             /* Enable global Interrupt flag (I) */
//
//    PWM0_INTEN_R |= PWM_INTEN_INTPWM2 ;
//
//    NVIC_PRI3_R |= (NVIC_PRI3_R & 0xFFFFFFF1) | 0x0000000A ; /*  priority 5 */
//
//    NVIC_EN0_R |= 0x00001000 ;        /*  Enable interrupt 12 in NVIC */
//
//    PWM0_2_ISC_R |= 0x00000002 ;
//    PWM0_ISC_R |= 0x00000002 ;

    /**/

//    PWM0_2_CTL_R |= 0x00000001 ;
    PWM0_ENABLE_R |= 0x20 ;
//    PWM0_INVERT_R |= 0x20 ;

}

void M0PWM5_start(void)
{
    PWM0_ENABLE_R |= 0x20 ;
}

void M0PWM5_stop(void)
{
    PWM0_ENABLE_R &= ~0x20 ;
}

void M0PWM5_set_Ts(int Ts)
{
    PWM0_ENABLE_R &= ~ 0x20 ;

    PWM0_2_LOAD_R = (0.125000*Ts)  ;

    float dutycycle_init = 0.5 ;

    PWM0_2_CMPA_R = ( 1-dutycycle_init )*(PWM0_2_LOAD_R)  ;

    PWM0_ENABLE_R |= 0x20 ;
}

void M0PWM5_set(float dutycycle)
{
//    if( dutycycle == 0 )
//    {
//        PWM0_2_CMPA_R = ( 1-dutycycle )*(PWM0_2_LOAD_R)  ; // //
//
//    }
//    else if( dutycycle == 1 )
//    {
//        PWM0_2_CMPA_R = ( 1-dutycycle )*(PWM0_2_LOAD_R) + 1 ; // //
//    }
//    else
    {
        PWM0_2_CMPA_R = ( 1-dutycycle )*(PWM0_2_LOAD_R)  ; // //
    }
}

void PWM_Start(void)
{
    PWM0_1_CTL_R |= 0x01 ;
    PWM0_2_CTL_R |= 0x01 ;
    PWM0_ENABLE_R |= 0x3C ;
}

void PWM_Stop(void)
{
    PWM0_1_CTL_R &= ~0x01 ;
    PWM0_2_CTL_R &= ~0x01 ;
    PWM0_ENABLE_R &= ~0x3C ;
}
/******************************PWM Interrupt handler********************************/

void PWM_0_G2_Handler(void)
{
//    uart0_send_str("P\n");
    PWM0_2_ISC_R |= 0x00000002 ;
}
