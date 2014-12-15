#ifndef ESTRUT_H
#define ESTRUT_H

struct dados {
        char nome[100], sexo[100];
        struct dados *pais[2], *filho, *irmao_prox, *conj;
};

#endif



