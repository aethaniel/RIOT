/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    boards_sam4s-xpld Atmel SAM4S Xplained
 * @ingroup     boards
 * @brief       Support for the Atmel SAM4S Xplained board.
 * @{
 *
 * @file
 * @brief       Board specific definitions for the Atmel SAM4S Xplained board.
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 */

#ifndef __BOARD_H
#define __BOARD_H

#include "cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Define the nominal CPU core clock in this board
 */
#define F_CPU               (120000000UL)

/**
 * Assign the hardware timer
 */
#define HW_TIMER            TIMER_0

/**
 * @name Define UART device and baudrate for stdio
 * @{
 */
#define STDIO               UART_0
#define STDIO_BAUDRATE      (115200U)
#define STDIO_RX_BUFSIZE    (64U)
/** @} */

/**
 * @name LED1 pin definitions
 * @{
 */
#define LED1_PORT           PIOC
#define LED1_PIN            PIO_PC10
/** @} */

/**
 * @name LED2 pin definitions
 * @{
 */
#define LED2_PORT           PIOC
#define LED2_PIN            PIO_PC17
/** @} */

/**
 * @name Macros for controlling the on-board LEDs.
 * @{
 */
#define LED1_ON             (LED1_PORT->PIO_ODSR |= LED1_PIN)
#define LED1_OFF            (LED1_PORT->PIO_ODSR &= ~LED1_PIN)
#define LED1_TOGGLE         (LED1_PORT->PIO_ODSR ^= LED1_PIN)

#define LED2_ON             (LED2_PORT->PIO_ODSR |= LED2_PIN)
#define LED2_OFF            (LED2_PORT->PIO_ODSR &= ~LED2_PIN)
#define LED2_TOGGLE         (LED2_PORT->PIO_ODSR ^= LED2_PIN)

/* for compatability to other boards */
#define LED_GREEN_ON        LED1_ON
#define LED_GREEN_OFF       LED1_OFF
#define LED_GREEN_TOGGLE    LED1_TOGGLE
#define LED_RED_ON          LED2_ON
#define LED_RED_OFF         LED2_OFF
#define LED_RED_TOGGLE      LED2_TOGGLE
/** @} */

/**
 * Define the type for the radio packet length for the transceiver
 */
typedef uint8_t radio_packet_length_t;

/**
 * @brief Initialize board specific hardware, including clock, LEDs and std-IO
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /** __BOARD_H */
/** @} */
