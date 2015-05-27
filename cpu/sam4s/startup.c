/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_sam4s16c
 * @{
 *
 * @file        startup.c
 * @brief       Startup code and interrupt vector definition
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <stdint.h>

#include "panic.h"

/**
 * memory markers as defined in the linker script
 */
extern uint32_t __etext ;
extern uint32_t __data_start__ ;
extern uint32_t __data_end__ ;
extern uint32_t __bss_start__ ;
extern uint32_t __bss_end__ ;
extern uint32_t __StackTop ;

/**
 * @brief functions for initializing the board, std-lib and kernel
 */
extern void board_init(void);
extern void kernel_init(void);
extern void __libc_init_array(void);

/**
 * @brief This function is the entry point after a system reset
 *
 * After a system reset, the following steps are necessary and carried out:
 * 1. load data section from flash to ram
 * 2. overwrite uninitialized data section (BSS) with zeros
 * 3. initialize the newlib
 * 4. initialize the board (sync clock, setup std-IO)
 * 5. initialize and start RIOTs kernel
 */
void reset_handler(void)
{
    uint32_t *dst = &__data_start__;
    uint32_t *src = &__etext;

    /* load data section from flash to ram */
    if ( (&__data_start__ != &__data_end__) && (src != dst) ) {
      for ( ; dst < &__data_end__ ; dst++, src++ ) {
        *dst = *src ;
      }
    }

    /* default bss section to zero */
    if ( &__bss_start__ != &__bss_end__ ) {
      for ( dst = &__bss_start__ ; dst < &__bss_end__ ; dst++ ) {
        *dst = 0ul ;
      }
    }

    /* initialize the board and startup the kernel */
    board_init();
    /* initialize std-c library (this should be done after board_init) */
    __libc_init_array();
    /* startup the kernel */
    kernel_init();
}

/**
 * @brief Default handler is called in case no interrupt handler was defined
 */
void dummy_handler(void)
{
    core_panic(DUMMY_HANDLER, "DUMMY HANDLER");
}

void isr_nmi(void)
{
    while (1) {asm ("nop");}
}

void isr_mem_manage(void)
{
    while (1) {asm ("nop");}
}

void isr_debug_mon(void)
{
    while (1) {asm ("nop");}
}

void isr_hard_fault(void)
{
    core_panic(HARD_FAULT, "HARD FAULT");
}

void isr_bus_fault(void)
{
    core_panic(BUS_FAULT, "BUS FAULT");
}

void isr_usage_fault(void)
{
    core_panic(USAGE_FAULT, "USAGE FAULT");
}

/* Cortex-M specific interrupt vectors */
void isr_svc(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_pendsv(void)               __attribute__ ((weak, alias("dummy_handler")));
void isr_systick(void)              __attribute__ ((weak, alias("dummy_handler")));

/* SAM4S16C specific interrupt vector */
void isr_supc(void)                 __attribute__ ((weak, alias("dummy_handler")));
void isr_rstc(void)                 __attribute__ ((weak, alias("dummy_handler")));
void isr_rtc(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_rtt(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_wdt(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_pmc(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_efc0(void)                 __attribute__ ((weak, alias("dummy_handler")));
#ifdef _SAM4S_EFC1_INSTANCE_
void isr_efc1(void)                 __attribute__ ((weak, alias("dummy_handler")));
#endif /* _SAM4S_EFC1_INSTANCE_ */
void isr_uart0(void)                __attribute__ ((weak, alias("dummy_handler")));
void isr_uart1(void)                __attribute__ ((weak, alias("dummy_handler")));
void isr_smc(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_pioa(void)                 __attribute__ ((weak, alias("dummy_handler")));
void isr_piob(void)                 __attribute__ ((weak, alias("dummy_handler")));
#ifdef _SAM4S_PIOC_INSTANCE_
void isr_pioc(void)                 __attribute__ ((weak, alias("dummy_handler")));
#endif /* _SAM4S_PIOC_INSTANCE_ */
void isr_usart0(void)               __attribute__ ((weak, alias("dummy_handler")));
#ifdef _SAM4S_USART1_INSTANCE_
void isr_usart1(void)               __attribute__ ((weak, alias("dummy_handler")));
#endif /* _SAM4S_USART1_INSTANCE_ */
#ifdef _SAM4S_HSMCI_INSTANCE_
void isr_hsmci(void)                __attribute__ ((weak, alias("dummy_handler")));
#endif /* _SAM4S_HSMCI_INSTANCE_ */
void isr_twi0(void)                 __attribute__ ((weak, alias("dummy_handler")));
void isr_twi1(void)                 __attribute__ ((weak, alias("dummy_handler")));
void isr_spi0(void)                 __attribute__ ((weak, alias("dummy_handler")));
void isr_ssc(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_tc0(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_tc1(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_tc2(void)                  __attribute__ ((weak, alias("dummy_handler")));
#ifdef _SAM4S_TC1_INSTANCE_
void isr_tc3(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_tc4(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_tc5(void)                  __attribute__ ((weak, alias("dummy_handler")));
#endif /* _SAM4S_TC1_INSTANCE_ */
void isr_adc(void)                  __attribute__ ((weak, alias("dummy_handler")));
#ifdef _SAM4S_DACC_INSTANCE_
void isr_dacc(void)                 __attribute__ ((weak, alias("dummy_handler")));
#endif /* _SAM4S_DACC_INSTANCE_ */
void isr_pwm(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_crccu(void)                __attribute__ ((weak, alias("dummy_handler")));
void isr_acc(void)                  __attribute__ ((weak, alias("dummy_handler")));
void isr_udp(void)                  __attribute__ ((weak, alias("dummy_handler")));

/* interrupt vector table */
__attribute__ ((section(".vectors")))
const void *interrupt_vector[] = {
    /* Stack pointer */
    (void*) (&__StackTop),          /* pointer to the top of the empty stack */
    /* Cortex-M handlers */
    (void*) reset_handler,          /* entry point of the program */
    (void*) isr_nmi,                /* non maskable interrupt handler */
    (void*) isr_hard_fault,         /* if you end up here its not good */
    (void*) isr_mem_manage,         /* memory controller interrupt */
    (void*) isr_bus_fault,          /* also not good to end up here */
    (void*) isr_usage_fault,        /* autsch */
    (void*) (0UL),                  /* Reserved */
    (void*) (0UL),                  /* Reserved */
    (void*) (0UL),                  /* Reserved */
    (void*) (0UL),                  /* Reserved */
    (void*) isr_svc,                /* system call interrupt */
    (void*) isr_debug_mon,          /* debug interrupt */
    (void*) (0UL),                  /* Reserved */
    (void*) isr_pendsv,             /* pendSV interrupt, used for task switching in RIOT */
    (void*) isr_systick,            /* SysTick interrupt, not used in RIOT */
    /* SAM4S16C specific peripheral handlers */
    (void*) isr_supc,               /*  0 supply controller */
    (void*) isr_rstc,               /*  1 reset controller */
    (void*) isr_rtc,                /*  2 real time clock */
    (void*) isr_rtt,                /*  3 real timer timer */
    (void*) isr_wdt,                /*  4 watchdog timer */
    (void*) isr_pmc,                /*  5 power management controller */
    (void*) isr_efc0,               /*  6 enhanced flash controller 0 */
#ifdef _SAM4S_EFC1_INSTANCE_
    (void*) isr_efc1,               /*  7 enhanced flash controller 1 */
#else
    (void*) (0UL),                  /*  7 Reserved */
#endif /* _SAM4S_EFC1_INSTANCE_ */
    (void*) isr_uart0,              /*  8 universal asynchronous receiver transceiver 0 */
    (void*) isr_uart1,              /*  9 universal asynchronous receiver transceiver 1 */
    (void*) isr_smc,                /* 10 static memory controller */
    (void*) isr_pioa,               /* 11 GPIO port A */
    (void*) isr_piob,               /* 12 GPIO port B */
#ifdef _SAM4S_PIOC_INSTANCE_
    (void*) isr_pioc,               /* 13 GPIO port C */
#else
    (void*) (0UL),                  /* 13 Reserved */
#endif /* _SAM4S_PIOC_INSTANCE_ */
    (void*) isr_usart0,             /* 14 USART0 */
#ifdef _SAM4S_USART1_INSTANCE_
    (void*) isr_usart1,             /* 15 USART1 */
#else
    (void*) (0UL),                  /* 15 Reserved */
#endif /* _SAM4S_USART1_INSTANCE_ */
    (void*) (0UL),                  /* 16 Reserved */
    (void*) (0UL),                  /* 17 Reserved */
#ifdef _SAM4S_HSMCI_INSTANCE_
    (void*) isr_hsmci,              /* 18 multimedia card interface */
#else
    (void*) (0UL),                  /* 18 Reserved */
#endif /* _SAM4S_HSMCI_INSTANCE_ */
    (void*) isr_twi0,               /* 19 two-wire interface 0 */
    (void*) isr_twi1,               /* 20 two-wire interface 1 */
    (void*) isr_spi0,               /* 21 serial peripheral interface */
    (void*) isr_ssc,                /* 22 synchronous serial controller */
    (void*) isr_tc0,                /* 23 timer counter 0 */
    (void*) isr_tc1,                /* 24 timer counter 1 */
    (void*) isr_tc2,                /* 25 timer counter 2 */
#ifdef _SAM4S_TC1_INSTANCE_
    (void*) isr_tc3,                /* 26 timer counter 3 */
#else
    (void*) (0UL),                  /* 26 Reserved */
#endif /* _SAM4S_TC1_INSTANCE_ */
#ifdef _SAM4S_TC1_INSTANCE_
    (void*) isr_tc4,                /* 27 timer counter 4 */
#else
    (void*) (0UL),                  /* 27 Reserved */
#endif /* _SAM4S_TC1_INSTANCE_ */
#ifdef _SAM4S_TC1_INSTANCE_
    (void*) isr_tc5,                /* 28 timer counter 5 */
#else
    (void*) (0UL),                  /* 28 Reserved */
#endif /* _SAM4S_TC1_INSTANCE_ */
    (void*) isr_adc,                /* 29 ADC controller */
#ifdef _SAM4S_DACC_INSTANCE_
    (void*) isr_dacc,               /* 30 DAC controller */
#else
    (void*) (0UL),                  /* 30 Reserved */
#endif /* _SAM4S_DACC_INSTANCE_ */
    (void*) isr_pwm,                /* 31 pulse width modulation controller */
    (void*) isr_crccu,              /* 32 CRC calculation unit */
    (void*) isr_acc,                /* 33 analog comparator */
    (void*) isr_udp                 /* 34 USB device port */
};
