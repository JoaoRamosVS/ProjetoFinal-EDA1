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

CLIENTE coletaDados() {
    CLIENTE cli;
    printf("Digite o codigo do cliente: ");
    scanf("%d", &cli.codigo);
    printf("Digite o nome do cliente: ");
    fflush(stdin);
    fgets(cli.nome, 49, stdin);
    printf("Digite a empresa do cliente: ");
    fgets(cli.empresa, 39, stdin);
    printf("Digite o departamento do cliente: ");
    fgets(cli.departamento, 24, stdin);
    printf("Digite o telefone do cliente: ");
    fgets(cli.telefone, 13, stdin);
    printf("Digite o celular do cliente: ");
    fgets(cli.celular, 14, stdin);
    printf("Digite o email do cliente: ");
    fgets(cli.email, 39, stdin);
    return cli;
}

// Cria a lista dinâmica através do primeiro elemento e seu nó
Lista *criaLista() {
    Lista *li;
    li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL){
        *li = NULL;
    }
    return li;
}

// Verifica se a lista está sem elementos
int listaVazia(Lista *li) {
    if(li == NULL) {
        abortaPrograma();
    }
    if(*li == NULL) {
        return 1;
    }
    return 0;
}

// Retorna o número de elementos na lista através de váriavel contadora
int tamanhoLista(Lista *li) {
    if(li == NULL) {
        abortaPrograma();
    }
    int acum=0;
    ELEM *no = *li;
    while(no != NULL) {
        acum++;
        no = no->prox;
    }
    return acum;
}

// Libera a lista da memória, liberando a memória alocada por cada nó da lista
void liberaLista(Lista *li){
    if(li != NULL) {
        ELEM *no;
        while((*li) != NULL) {
            no = *li;
            *li =(*li)->prox;
            free(no);
        }
        free(li);
    }
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


/*
 * Insere cliente já preenchido de maneira ordenada na lista de contatos
 * É feita uma verificação de duplicidade nos códigos dos clientes antes da inserção
 *
 * Recebe como parâmetros a lista dinâmica e a struct cliente preenchida.
*/
int insereCliente(Lista *li, CLIENTE cli) {
    if(li == NULL){
        abortaPrograma();
    }
    ELEM *no = (ELEM*) malloc(sizeof(ELEM));
    if(no == NULL) {
        return 0;
    }

    CLIENTE cli_consulta;
    int p = consultaCodigo(li, cli.codigo, &cli_consulta); // Aqui é feita a consulta na lista para verificação de duplicidade por código
    if(!p) { // Se não encontrar o código informado
        no->dados = cli;
        if(listaVazia(li)) {
            no->prox = (*li);
            *li = no;
            return cli.codigo;
        }
        else {
            ELEM *ant, *atual = *li;
            while(atual != NULL && atual->dados.codigo < cli.codigo) {
                ant = atual;
                atual = atual->prox;
            }
            if(atual == *li) {
                no->prox = (*li);
                *li = no;
            }
            else {
                no->prox = ant->prox;
                ant->prox = no;
            }
            return cli.codigo;
        }
    }
    else { // Se encontrar o código informado, interrompe a inserção e retorna falso
        printf("\nEste codigo ja esta cadastrado. Tente novamente com outro codigo.");
        return 0;
    }
}


void leituraLista(Lista *li, FILE *arq){
    CLIENTE clienteLido;
    while(!feof(arq)) {
        fread(&clienteLido, sizeof(CLIENTE),1,arq);
        insereCliente(li, clienteLido);
    }
}

void gravaLista(Lista *li, FILE *arq) {
    ELEM *no = *li;
    while(no != NULL){
        fwrite(&no->dados, sizeof(CLIENTE), 1, arq);
        no = no->prox;
    }
    free(no);
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
