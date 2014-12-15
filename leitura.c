#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrut.h"
#include "htable.h"


void parse_comandos(htable **ht, char *args[4]);

void comando (htable **ht) {
        
        char buffer[300],
             *args[4];

        //le uma linha da entrada padrao
        fgets(buffer, 300, stdin); 
        //separa argumentos
        args[0] = strtok(buffer, " ,\n");
        args[1] = strtok(NULL, " ,\n");
        args[2] = strtok(NULL, " ,\n");
        args[3] = strtok(NULL, " ,\n");

        //executa o comando lido
        parse_comandos(ht, args);
}

void parse_comandos(htable **ht, char *args[4]) {

        struct dados dados,
                     *dados_pai;

        if (strcmp(args[1], "nasceu") == 0) {

                char *nome = args[1],
                     *sexo = args[2],
                     *nome_pai = args[3];

                strcpy(dados.nome, nome);
                strcpy(dados.sexo, sexo);
                dados.pais[0] = NULL;
                dados.pais[1] = NULL;
                dados.filho = NULL;
                dados.irmao_prox = NULL;
                dados.conj = NULL;

                if (nome_pai != NULL) {
                        dados_pai = consulta_hash(ht, nome_pai);

                        //caso pai nao esteja na tabela
                        if (dados_pai == NULL)
                                return;
                        //caso pai nao seja casado
                        if (dados_pai->conj == NULL) {
                                return;
                        }

                        //adiciona ponteiro para o pai
                        if (dados.pais[0] == NULL)
                                dados.pais[0] = dados_pai;
                        else if (dados.pais[1] == NULL) {
                                
                                //caso os pais nao sejam casados
                                if (dados.pais[0]->conj != dados_pai)
                                        return;

                                dados.pais[1] = dados_pai;

                        //caso os dois pais ja estejam registrados
                        } else
                                return;

                        //adiciona ponteiro para o proximo irmao
                        dados.irmao_prox = dados_pai->filho;
                        //atualiza ponteiro para o filho com a pessoa inserida
                        dados_pai->filho = insere_tabela(ht, nome, dados);

                } else {
                        insere_tabela(ht,nome,dados);
                }

        } else if (strcmp(args[1], "casaram-se") == 0) {

                char *casal[2];
                casal[0] = args[1];
                casal[1] = args[2];

                //consulta registro dos conjuges
                struct dados *conjug[2];
                conjug[0] = consulta_hash(ht, casal[0]);
                conjug[1] = consulta_hash(ht, casal[1]);

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
}

