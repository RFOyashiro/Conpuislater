#include <stdio.h>
#include <stdlib.h>

#include "AnalyseurSynth.h"
#include "analyseur_lexical.h"
#include "symboles.h"

char yytext[100];
FILE *yyin;

int main(int argc, char **argv) {  
  yyin = fopen(argv[1], "r");
  if(yyin == NULL){
    fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[1]);
    exit(1);
  }
  analyse();
  return 0;
}
