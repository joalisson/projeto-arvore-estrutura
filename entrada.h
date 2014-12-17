#ifndef ENTRADA_H
#define ENTRADA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrut.h"
#include "htable.h"

void insere_nascimento (htable **ht, char *nome, char *sexo);
        
void insere_nascimento_pai (htable **ht, char *nome, char *sexo, char *nome_pai); 

void insere_casamento (htable **ht, char *nome_conj1, char *nome_conj2); 

#endif
