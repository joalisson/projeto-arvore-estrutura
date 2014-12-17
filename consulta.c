#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrut.h"
#include "htable.h"

struct dados *busca_conj (htable **ht, char *nome) {
        
        struct dados *dados = consulta_tabela(ht, nome);

        return dados->conj;
}

struct dados *busca_pai (htable **ht, char *nome) {

        struct dados *dados = consulta_tabela(ht, nome);

        if (dados->pais[0] != NULL)
                return dados->pais[0];

        return dados->pais[1];
}

struct dados *busca_irmaos (htable **ht, char *nome) {
        
        struct dados *dados = consulta_tabela(ht, nome);

        //lista encadeada de irmaos
        return dados->irmao_prox;
}

struct dados *busca_filhos (htable **ht, char *nome) {
        
        struct dados *dados = consulta_tabela(ht, nome);

        //lista encadeada de filhos
        return dados->filho;
}

int eh_homem (struct dados *dados) {
        
        if (strcmp(dados->sexo, "masculino") == 0)
                return 1;
        return 0;
}

int eh_mulher (struct dados *dados) {
        
        if (strcmp(dados->sexo, "feminino") == 0)
                return 1;
        return 0;
}
