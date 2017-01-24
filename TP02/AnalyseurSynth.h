#ifndef __ANA_SYNTH__
#define __ANA_SYNTH__

#include "stdio.h"

// See AnalyseurSynth.c for detailed comments.

/**
 * Main function to use the synthaxic analyser.
 */
void analyse(void);
/************************************************************************************************
 * ARITHMETIC EXPRESSION PARSING                                                                                             *
 * Use E0() to analyse next serie of token as an arithmetic expression(like $a + 10 * (4 + $b).          *
 * TODO : add variables, tables values ($a[3]), and function call.                                                       *
 ************************************************************************************************/
void E0(void);
void E0a(void);
void E1(void);
void E1a(void);
void E2(void);
void E2a(void);
void E3(void);
void E3a(void);
void E4(void);
void E4a(void);
void E5(void);
void E6(void);
void E6a(void);
void E7(void);
/************************************************************************************************
 * /ARITHMETIC EXPRESSION PARSING                                                                                           *
 * Use E0() to analyse next serie of token as an arithmetic expression(like $a + 10 * (4 + $b).          *
 * TODO : add variables, tables values ($a[3]), and function call.                                                       *
 ************************************************************************************************/
#endif
