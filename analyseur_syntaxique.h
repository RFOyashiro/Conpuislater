#ifndef __ANA_SYNT__
#define __ANA_SYNT__

#include "stdio.h"

// See AnalyseurSynth.c for detailed comments.

/**
 * Main function to use the synthaxic analyser.
 */
void analyse(void);

n_prog *pg (void);
n_l_dec *odv (void);
n_l_dec *ldv (void);
n_l_dec *ldvb (void);
n_dec *dv (void);
int ott (void);
n_l_dec *ldf (void);
n_dec *df (void);
n_l_dec *lp (void);
n_l_dec *oldv (void);
n_instr *i (void);
n_instr *iaff (void);
n_instr *ib (void);
n_l_instr *li (void);
n_instr *isi (void);
n_instr *osinon (void);
n_instr *itq (void);
n_instr *iapp (void);
n_instr *iret (void);
void iecr (void);
void ivide (void);
n_instr *ift (void);
n_exp *exp (void);
void expb (void);
void conj (void);
void conjb (void);
void comp (void);
void compb (void);
void e (void);
void eb (void);
void t (void);
void tb (void);
void neg (void);
void f (void);
n_var *var (void);
void oind (void);
n_appel *appf (void);
void lexp (void);
void lexpb (void);

#endif
