#ifndef HTABLE_H
#define HTABLE_H

#define HASHTABLE_SIZE 128

typedef struct hash_table {
        char *chave;
        struct dados *dados; 
} htable;

int hash_func (char *chave);

htable **init_table (void);

struct dados *consulta_tabela (htable **ht, char *nome); 

struct dados *insere_tabela (htable **ht, char *nome, struct dados data); 

#endif
