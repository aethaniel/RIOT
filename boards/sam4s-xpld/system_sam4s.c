#include "sam4s16c.h"

#ifdef __cplusplus
extern "C" {
#endif

#define __SYSTEM_CLOCK_4MHZ  (4000000UL)
#define __SYSTEM_CLOCK_12MHZ (12000000UL)

/* Clock Settings (4MHz) using Internal Fast RC */
uint32_t SystemCoreClock = __SYSTEM_CLOCK_4MHZ ;

/**
 * \brief Setup the microcontroller system.
 *
 * Initialize the System and update the SystemFrequency variable.
 */
void SystemInit( void )
{
  /* Set 6 FWS for Embedded Flash Access */
  EFC0->EEFC_FMR = EEFC_FMR_FWS(5);
#if defined(ID_EFC1)
  EFC1->EEFC_FMR = EEFC_FMR_FWS(5);
#endif

  /* Initialize main oscillator */
  if ( !(PMC->CKGR_MOR & CKGR_MOR_MOSCSEL) )
  {
    PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTST(0x8) | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN;
    for ( ; !(PMC->PMC_SR & PMC_SR_MOSCXTS) ; ) ;
  }

  /* Switch to 3-20MHz Xtal oscillator */
  PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTST(0x8) | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCSEL;
  for ( ; !(PMC->PMC_SR & PMC_SR_MOSCSELS) ; ) ;

  PMC->PMC_MCKR = (PMC->PMC_MCKR & ~(uint32_t)PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK;
  for ( ; !(PMC->PMC_SR & PMC_SR_MCKRDY) ; ) ;

  /* Initialize PLLB */
  PMC->CKGR_PLLBR = (CKGR_PLLBR_MULB(29) | CKGR_PLLBR_PLLBCOUNT(0x1) | CKGR_PLLBR_DIVB(3)) ;
  for ( ; !(PMC->PMC_SR & PMC_SR_LOCKB) ; ) ;

  /* Switch to main clock */
  PMC->PMC_MCKR = PMC_MCKR_PRES_CLK_1 | PMC_MCKR_CSS_MAIN_CLK ;
  for ( ; !(PMC->PMC_SR & PMC_SR_MCKRDY) ; ) ;

  PMC->PMC_MCKR = PMC_MCKR_PRES_CLK_1 |  PMC_MCKR_CSS_PLLB_CLK ;
  for ( ; !(PMC->PMC_SR & PMC_SR_MCKRDY) ; ) ;

  SystemCoreClock=__SYSTEM_CLOCK_12MHZ ;
}

/**
 * \brief Get Core Clock Frequency.
 */
void SystemCoreClockUpdate( void )
{
}

#ifdef __cplusplus
}
#endif
