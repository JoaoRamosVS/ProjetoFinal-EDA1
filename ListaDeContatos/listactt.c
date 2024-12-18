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
    printf("Digite o cod do cliente: ");
    scanf("%d", &cli.codigo);

    printf("Digite o nome do cliente atualizado: ");
    fflush(stdin);
    fgets(cli.nome, 49, stdin);
    printf("Digite a empresa do cliente atualizado: ");
    fgets(cli.empresa, 39, stdin);
    printf("Digite o departamento do cliente atualizado: ");
    fgets(cli.departamento, 24, stdin);
    printf("Digite o telefone do cliente atualizado: ");
    fgets(cli.telefone, 13, stdin);
    printf("Digite o celular do cliente atualizado: ");
    fgets(cli.celular, 14, stdin);
    printf("Digite o email do cliente atualizado: ");
    fgets(cli.email, 39, stdin);
    return cli;
}


// Cria a lista din�mica atrav�s do primeiro elemento e seu n�
Lista *criaLista() {
    Lista *li;
    li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL){
        *li = NULL;
    }
    return li;
}

// Verifica se a lista est� sem elementos
int listaVazia(Lista *li) {
    if(li == NULL) {
        abortaPrograma();
    }
    if(*li == NULL) {
        return 1;
    }
    return 0;
}

// Retorna o n�mero de elementos na lista atrav�s de v�riavel contadora
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

// Libera a lista da mem�ria, liberando a mem�ria alocada por cada n� da lista
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
 * Consulta se existe um cliente com o c�digo informado
 * Se sim, atribui o cliente ao endere�o informado e retorna verdadeiro
 * Se n�o, retorna falso
 *
 * Recebe como par�metros a lista din�mica, o c�digo e o ponteiro da v�riavel cliente de consulta
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
 * Insere cliente j� preenchido de maneira ordenada na lista de contatos
 * � feita uma verifica��o de duplicidade nos c�digos dos clientes antes da inser��o
 *
 * Recebe como par�metros a lista din�mica e a struct cliente preenchida.
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

    int p = consultaCodigo(li, cli.codigo, &cli_consulta); // Aqui � feita a consulta na lista para verifica��o de duplicidade por c�digo
    if(!p) { // Se n�o encontrar o c�digo informado
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
    else { // Se encontrar o c�digo informado, interrompe a inser��o e retorna falso
        printf("\nEste codigo ja esta cadastrado. Tente novamente com outro codigo.");
        return 0;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int removeOrdenado(Lista *li, int cod){
    int codigo;

    if(li == NULL){
        abortaPrograma();
    }

    ELEM *ant, *no = *li;

    while(no != NULL && no->dados.codigo != cod){
        ant = no;
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    }
    if(no == *li){
        *li = no->prox;
    } else {
    ant->prox = no->prox;
    }

    codigo = no->dados.codigo;

    free(no);

    return codigo;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CLIENTE editaDados() {
    CLIENTE cli;
    printf("Digite o nome do cliente atualizado: ");
    fflush(stdin);
    fgets(cli.nome, 49, stdin);
    printf("Digite a empresa do cliente atualizado: ");
    fgets(cli.empresa, 39, stdin);
    printf("Digite o departamento do cliente atualizado: ");
    fgets(cli.departamento, 24, stdin);
    printf("Digite o telefone do cliente atualizado: ");
    fgets(cli.telefone, 13, stdin);
    printf("Digite o celular do cliente atualizado: ");
    fgets(cli.celular, 14, stdin);
    printf("Digite o email do cliente atualizado: ");
    fgets(cli.email, 39, stdin);
    return cli;
}

int editaContato(Lista *li, int cod){
    char y;
    if(li == NULL){
        abortaPrograma();
    }
    //////////////////////////////////////////
    ELEM *ant, *no = *li;

    while(no != NULL && no->dados.codigo != cod){
        ant = no;
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    }
    ////////////////////////////////////////
    // fun��o consulta individual

    fflush(stdin);
    printf("Deseja editar esse registro? s/n");
    y = getchar();

    if(y == 's'){
        CLIENTE cli = editaDados();
        cli.codigo = cod;
        no->dados = cli;

        return 1;
    } else{
        return 0;
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
