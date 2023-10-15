/*
 * QEI.c
 *
 *  Created on: 19-Aug-2023
 *      Author: Sarvjit
 */

#include "QEI.h"

#ifndef UART_H_
#include"UART.h"
#endif

void QEI_0_INIT(void)
{
    SYSCTL_RCGC1_R |= SYSCTL_RCGC1_QEI0 ;

    SYSCTL_RCGCQEI_R |= SYSCTL_RCGCQEI_R0 ;

//    while((SYSCTL_PRQEI_R & SYSCTL_PRQEI_R0) == 0){}; // Wait for clock to stabilize

    SYSCTL_RCGC2_R |= 0x00000020 ;       /* Enable clock to GPIO_F_ at clock gating control register */

    SYSCTL_RCGCGPIO_R |= 0x00000020 ;    /* Enable and provide a clock to GPIO Port_F_ in Run mode */

//    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5) == 0){}; // Wait for clock to stabilize

    GPIO_PORTF_LOCK_R = 0x4C4F434B;     /* unlock commit register */

    GPIO_PORTF_DIR_R |= 0x00000000 ;    /*  GPIO Direction | 0 -> INPUT | 1 -> OUTPUT */

    GPIO_PORTF_DIR_R &= ~ 0x00000013 ;

    GPIO_PORTF_CR_R |= 0xFFFFFFFF ;     /* 1 -> The corresponding GPIOAFSEL, GPIOPUR, GPIOPDR, or GPIODEN bits can be written */

    GPIO_PORTF_AFSEL_R &= ~ 0xFFFFFFFF ;  /* Disable alternate function on PORT */

    GPIO_PORTF_AFSEL_R |= 0x00000013 ;

    GPIO_PORTF_AMSEL_R &= ~ 0xFFFFFFFF ;  /* Disable analog function on PORT */

    GPIO_PORTF_PCTL_R &= ~ 0xFFFFFFFF ; /* Regular digital function */

    GPIO_PORTF_PCTL_R |= 0x00060066 ;

    GPIO_PORTF_DEN_R |= 0xFF;       /* enable the GPIO pins for digital function */

    QEI0_CTL_R |= 0x00000038 ;

    QEI0_MAXPOS_R = 0x00001FFF ;

    QEI0_LOAD_R = 160000 - 1 ;

    QEI0_CTL_R |= 0x00000001 ;

    /* Interrupt */

    EnableInterrupts() ;             /* Enable global Interrupt flag (I) */

    NVIC_PRI3_R |= (NVIC_PRI3_R & 0xFFFF1FFF) | 0x0000C000 ; /*  priority 6 */

    NVIC_EN0_R |= 0x00002000 ;        /*  Enable interrupt 13 in NVIC */

    QEI0_INTEN_R |= 0x00000005 ;

}

char Q_str[100] ;

long rpm = 0;

void QEI_0_Handler(void)
{
    if( QEI0_RIS_R & 0x00000004 )
    {
        QEI0_ISC_R |= 0x00000004 ;

//        uart0_send_str("DIR\n");
//        DIR
    }

    if( QEI0_RIS_R & 0x00000001 )
    {
        QEI0_ISC_R |= 0x00000001 ;

//        rpm = (10000 * ( (QEI0_SPEED_R & 0xFFFF0000) >> 16 ) * 60);
//
//        uart0_send_str("I\n");
//        sprintf(Q_str,"RPM = %ld\n", rpm);
//        uart0_send_str(Q_str);
//        index
    }
}



