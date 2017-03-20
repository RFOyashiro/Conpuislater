CC = gcc

LIBS = -lm 
CCFLAGS = -Wall -ggdb

OBJ = analyseur_lexical.o util.o suivants.o premiers.o analyseur_syntaxique.o syntabs.o affiche_arbre_abstrait.o tabsymboles.o analyseur_semantique.o

all: test_yylex

test_yylex: test_yylex.c $(OBJ)
	$(CC) $(CCFLAGS) -o test_yylex test_yylex.c $(OBJ)

.PHONY : clean

clean:
	- rm -f $(OBJ)
	- rm -f test_yylex
