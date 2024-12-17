#include <stdlib.h>
#include <stdio.h>
#include "listactt.h"

struct elemento {
    CLIENTE dados;
    struct elemento *prox;
};

typedef struct elemento ELEM;

void abortaPrograma() {
    printf("ERRO! Lista nao foi alocada, programa sera encerrado...\n\n\n");
    system("pause");
    exit(1);
}

/*
 * Consulta se existe um cliente com o código informado
 * Se sim, atribui o cliente ao endereço informado e retorna verdadeiro
 * Se não, retorna falso
 *
 * Recebe como parâmetros a lista dinâmica, o código e o ponteiro da váriavel cliente de consulta
*/
int consultaCodigo(Lista *li, int cod, CLIENTE *cli) {
    if(li == NULL){
        abortaPrograma();
    }
    ELEM *no = *li;
    while(no != NULL && no->dados.codigo != cod) {
        no = no->prox;
    }
    if(no == NULL) {
        return 0;
    }
    else {
        *cli = no->dados;
        return 1;
    }
}

void apresentaMenu() {
    printf("\t===== MENU - LISTA DE CONTATOS =====\n\n");
    printf("\tINSERIR CLIENTE - Digite 1\n\n");
    printf("\tLISTA COMPLETA - Digite 2\n\n");
    printf("\tBUSCAR CLIENTE POR CODIGO - Digite 3\n\n");
    printf("\tBUSCAR CLIENTE POR NOME - Digite 4\n\n");
    printf("\tEDITAR CLIENTE - Digite 5\n\n");
    printf("\tREMOVER CLIENTE - Digite 6\n\n");
    printf("\tSAIR DO PROGRAMA - Digite 7\n\n");
    printf("\t-------------------------------------\n->: ");
}
