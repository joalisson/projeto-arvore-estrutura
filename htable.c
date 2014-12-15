#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrut.h"
#include "htable.h"


int hash_func (char *chave) {
        
        int hash_value = 0,
            i;

        for (i = 0; chave[i] != '\0'; ++i) {
                hash_value += chave[i];
        }

        return hash_value % HASHTABLE_SIZE;
}

htable **init_table (void) {

        htable **new_table = malloc(sizeof(htable *) * HASHTABLE_SIZE);

        int i;
        for (i = 0; i < HASHTABLE_SIZE; ++i)
                new_table[i] = NULL;

        return new_table;
}


struct dados *consulta_tabela (htable **ht, char *nome) {
        
        int hash = hash_func(nome),
            i;

        if (ht[hash] == NULL)
                return NULL;

        // verifica se nome está na posicao hash
        if (strcmp(ht[hash]->chave, nome) == 0)
                return ht[hash]->dados;

        // procura proxima posicao nao vazia onde a chave pode ter sido inserida
        for (i = hash + 1; i != hash && ht[i] != NULL; ++i) {
                if (strcmp(ht[i]->chave, nome) == 0)
                        return ht[i]->dados;
                if (i >= HASHTABLE_SIZE - 1)
                        i = 0;
        }

        return NULL;
}

struct dados *insere_tabela (htable **ht, char *nome, struct dados data) {

        int hash = hash_func(nome),
            i;

        htable *new_elem = malloc(sizeof(htable));

        new_elem->dados = malloc(sizeof(struct dados));
        *new_elem->dados = data;
        new_elem->chave = malloc(sizeof(char) * (strlen(nome) + 1));
        strcpy (new_elem->chave, nome);

        // se posicao hash esta vazia insere dados nela
        if (ht[hash] == NULL) {
                ht[hash] = new_elem;
                return ht[hash]->dados;
        }

        // se posicao hash nao estiver vazia, insere na proxima vazia
        for (i = hash + 1; i != hash && ht[i] != NULL; ++i) {
                if (ht[i] == NULL) {
                        ht[i] = new_elem;
                        return ht[hash]->dados;
                }
                if (i >= HASHTABLE_SIZE - 1)
                        i = 0;
        }
        return NULL;
}


        







