#ifndef __ANA_SYNT__
#define __ANA_SYNT__

#include "symboles.h"
#include "analyseur_lexical.h"
#include "premiers.h"
#include "suivants.h"
#include "syntabs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// See AnalyseurSynth.c for detailed comments.

/**
 * Main function to use the synthaxic analyser.
 */
n_prog *analyse(void);

n_prog *pg(void);
n_l_dec *odv(void);
n_l_dec *ldv(void);
n_l_dec *ldvb(void);
n_dec *dv(void);
int ott(void);
n_l_dec *ldf(void);
n_dec *df(void);
n_l_dec *lp(void);
n_l_dec *oldv(void);
n_instr *i(void);
n_instr *iaff(void);
n_instr *ib(void);
n_l_instr *li(void);
n_instr *isi(void);
n_instr *osinon(void);
n_instr *itq(void);
n_instr *iapp(void);
n_instr *iret(void);
n_instr *iecr(void);
n_instr *ivide(void);
n_instr *ift(void);
n_exp *exp(void);
n_exp *expb(n_exp* herit);
n_exp *conj(void);
n_exp *conjb(n_exp* herit);
n_exp *comp(void);
n_exp *compb(n_exp* herit);
n_exp *e(void);
n_exp *eb(n_exp* herit);
n_exp *t(void);
n_exp *tb(n_exp* herit);
n_exp *neg(void);
n_exp *f(void);
n_var *var(void);
n_exp *oind(void);
n_appel *appf(void);
n_l_exp *lexp(void);
n_l_exp *lexpb(void);

#endif
