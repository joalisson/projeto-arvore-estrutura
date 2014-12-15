#ifndef CONSULTA_H
#define CONSULTA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrut.h"
#include "htable.h"

struct dados *busca_conj (htable **ht, char *nome); 
        
struct dados *busca_pai (htable **ht, char *nome); 

struct dados *busca_irmaos (htable **ht, char *nome); 

struct dados *busca_filhos (htable **ht, char *nome); 

int eh_homem (struct dados *dados); 

int eh_mulher (struct dados *dados); 

#endif
