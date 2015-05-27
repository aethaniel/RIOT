/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_sam4s-xpld
 * @{
 *
 * @file        board.c
 * @brief       Board specific implementations for the Atmel SAM4S Xplained board
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>

#include "board.h"
#include "cpu.h"


void led_init(void);


void board_init(void)
{
    /* initialize core clocks via CMSIS function provided by Atmel */
    SystemInit();

    /* initialize the CPU */
    cpu_init();

    /* initialize the boards LEDs */
    led_init();
}


/**
 * @brief Initialize the boards on-board LEDs (Amber LEDs "LED1" and "LED2")
 *
 * The LEDs initialization is hard-coded in this function. As the LEDs are soldered
 * onto the board it is fixed to their CPU pins.
 *
 * The LEDs are connected to the following pin:
 * - LED1: PC10
 * - LED2: PC17
 */
void led_init(void)
{
    /* enable PIO control of pins PC10 and PC17 */
    LED1_PORT->PIO_PER = LED1_PIN|LED2_PIN;
    /* set pin as output */
    LED1_PORT->PIO_OER = LED1_PIN|LED2_PIN;
    /* enable direct write access to the LEDs pins */
    LED1_PORT->PIO_OWER = LED1_PIN|LED2_PIN;
    /* disable pull-up */
    LED1_PORT->PIO_PUDR = LED1_PIN|LED2_PIN;
    /* clear pin */
    LED1_PORT->PIO_CODR = LED1_PIN|LED2_PIN;
}
