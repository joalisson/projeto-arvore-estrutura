#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrut.h"
#include "htable.h"
#include "entrada.h"

void insere_nascimento (htable **ht, char *nome, char *sexo) {
        
        struct dados dados;

        //nome já está na tabela
        if (consulta_tabela(ht, nome) != NULL)
                return;

        //copia argumentos para dados
        strcpy(dados.nome, nome);
        strcpy(dados.sexo, sexo);

        //inicializa
        dados.pais[0] = NULL;
        dados.pais[1] = NULL;
        dados.filho = NULL;
        dados.irmao_prox = NULL;
        dados.conj = NULL;

        insere_tabela(ht, nome, dados);
}

void insere_nascimento_pai (htable **ht, char *nome, char *sexo, char *nome_pai) {

        struct dados *dados_pai,
                     *dados;

        dados = consulta_tabela(ht, nome);
        dados_pai = consulta_tabela(ht, nome_pai);
        
        //caso pai nao seja casado
        if (dados_pai->conj == NULL) {
                return;
        }

        if (dados == NULL) {
                dados = malloc(sizeof(struct dados));

                dados->pais[0] = dados_pai;
                dados->pais[1] = NULL;
                dados->filho = NULL;
                dados->irmao_prox = NULL;
                dados->conj = NULL;
                insere_tabela(ht, nome, *dados);

        } else {

                //adiciona ponteiro para o pai
                if (dados->pais[0] == NULL)
                        dados->pais[0] = dados_pai;
                else if (dados->pais[1] == NULL) {

                        //caso os pais nao sejam casados entre si
                        if (dados->pais[0]->conj != dados_pai)
                                return;

                        dados->pais[1] = dados_pai;
                }
                //caso os dois pais ja estejam registrados
                else {
                        return;
                }

                //adiciona ponteiro para o proximo irmao
                dados->irmao_prox = dados_pai->filho;
                //atualiza ponteiro para o filho com a pessoa inserida
                dados_pai->filho = insere_tabela(ht, nome, *dados);

        }
}

void insere_casamento (htable **ht, char *nome_conj1, char *nome_conj2) {

        //consulta registro dos conjuges
        struct dados *conjug[2];

        conjug[0] = consulta_tabela(ht, nome_conj1);
        conjug[1] = consulta_tabela(ht, nome_conj2);

        //pessoas do mesmo sexo nao podem casar
        if (strcmp(conjug[0]->sexo, conjug[1]->sexo) == 0)
                return;

        //nenhum dos conjuges ja podem ser casados
        if (conjug[0]->conj != NULL || conjug[1]->conj != NULL) 
                return;

        //atualiza ponteiros do casal
        conjug[0]->conj = conjug[1];
        conjug[1]->conj = conjug[0];
}
