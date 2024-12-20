#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
 * Coleta dados para inser��o na lista, evitando duplicidade de c�digos
 *
 * Recebe a lista para verifica��o de duplicidade de clientes j� cadastrados e o ponteiro para armazenar os dados do novo cliente
*/
int coletaDados(Lista *li, CLIENTE *novoCliente) {
    CLIENTE cli, cli_consulta;
    int t=0, codigoExistente=0, tentarNovamente=1;
    do{
        t=0;
        if(t==0 && tentarNovamente==1) {
            printf("Digite o codigo do cliente: ");
            scanf("%d", &cli.codigo);
            t = consultaCodigo(li, cli.codigo, &cli_consulta); // Verifica duplicidade de codigos

            if (t==1){ // Se encontrar duplicidade, oferece a op��o para o usu�rio tentar novamente
                system("cls");
                printf("O codigo informado ja existe na lista.\n");
                printf("Digite 1 para inserir outro numero\nDigite 0 para abortar a insercao\n");
                printf("->: ");
                scanf("%d", &tentarNovamente);

                if (tentarNovamente==0) {
                    codigoExistente = 1;  // Essa vari�vel � para caso o usuario deseje abortar a inser�ao
                }
            }
            else{
                tentarNovamente=0;
            }
        }
    }while(t && tentarNovamente); // Enquanto a duplicidade se mostrar verdadeira e o usu�rio desejar tentar novamente

    if(codigoExistente){
        return 0; // Aborta insercao
    }

    printf("Digite o nome do cliente: ");
    fflush(stdin);
    fgets(cli.nome, 49, stdin);
    printf("Digite a empresa do cliente  ");
    fgets(cli.empresa, 39, stdin);
    printf("Digite o departamento do cliente: ");
    fgets(cli.departamento, 24, stdin);
    printf("Digite o telefone do cliente: ");
    fgets(cli.telefone, 13, stdin);
    printf("Digite o celular do cliente: ");
    fgets(cli.celular, 14, stdin);
    printf("Digite o email do cliente: ");
    fgets(cli.email, 39, stdin);
    *novoCliente = cli;
    return 1;
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
 * Realiza a busca dentro da lista por clientes que cont�m a string informada dentro do nome do cliente.
 *
 * Recebe a lista din�mica e o nome para busca como parametros.
 * Exibe caso encontre e retorna verdadeiro, e se nao encontra apenas retorna falso.
*/
int consultaNome(Lista *li, char* nome) {
    int z=0;
    char nomeCliente[50], nome2[50];
    apagarEnter(nome);
    strcpy(nome2, nome);
    strlwr(nome2);
    if(li == NULL){
        abortaPrograma();
    }
    ELEM *no = *li;
    while(no != NULL) {
        strcpy(nomeCliente, no->dados.nome);
        strlwr(nomeCliente);
        if(strstr(nomeCliente, nome2)){
            exibeCliente(no->dados);
            z=1;
        }
        no = no->prox;
    }
    return z;
}

/*
 * Exibe o relatorio de todos os contatos
 *
 * Recebe a lista din�mica como parametro.
 * Caso nao tenham elementos na lista, retorna falso
*/
int consultaGeral(Lista *li) {
    int z=0;
    if(li == NULL){
        abortaPrograma();
    }
    ELEM *no = *li;
    while(no != NULL) {
        exibeCliente(no->dados);
        no = no->prox;
        z=1;
    }
    return z;
}

/*
 * Insere cliente j� preenchido de maneira ordenada na lista de contatos
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

/*
 * Realiza leitura dos dados salvos no arquivo bin�rio, elemento por elemento
 * e adiciona na lista
 *
 * Recebe como par�metros a lista din�mica e o arquivo bin�rio j� aberto no programa principal.
*/
void leituraLista(Lista *li, FILE *arq) {
    CLIENTE clienteLido;
    while (fread(&clienteLido, sizeof(CLIENTE), 1, arq) == 1) {
        insereCliente(li, clienteLido);
    }
}

/*
 * Remove ordenadamente seguindo a l�gica da busca por c�digo, onde ap�s o tratamento de
 * erros com os if's, cada node � iterado at� encontrar o node especificado, e ao verificar que o seu
 * c�digo n�o � menor que os outros da lista, tem seu ponteiro "prox" repassado para o ponteiro
 * "prox" do seu node antecessor para manter a integridade referencial da lista e deletar o node�apontado.
 *
*/
int removeCliente(Lista *li, int cod){
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
    return codigo;
}
/*
 * M�todo coletaDados simplificado e sem a possibilidade de se digitar um novo c�digo,
 * utilizado para edi��o
*/
CLIENTE editaDados() {
    CLIENTE cli;
    printf("\nDigite o nome do cliente atualizado: ");
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
/*
 * Recebe a lista e c�digo como par�metros e usa o c�digo fornecido para buscar qual node editar
 *
 * Ap�s iterar por cada node e compara-los com o cod, chamamos a fun��o consultaCodigo para passar por refer�ncia a struct original para a vari�vel local "cli",
 * tamb�m chamamos a fun��o exibeCliente para visualiza��o do cliente que o usu�rio editar� e a confirma��o se d� por um if "s/n"
 * Ap�s confirmar a edi��o, a struct nova � copiada para cima da struct velha e o codigo � atribuido diretamente do par�metro para a nova struct.
*/

int editaCliente(Lista *li, int cod){
    CLIENTE cli;
    char y;
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

    consultaCodigo(li, cod, &cli);
    exibeCliente(cli);

    fflush(stdin);
    printf("\nDeseja editar esse registro? s/n\n");
    y = getchar();
    if(y == 's'){
        CLIENTE cli = editaDados();
        cli.codigo = cod;
        no->dados = cli;
        return 1;
    } else {
        return 0;
    }
}


/*
 * Obt�m dados salvos na lista elemento por elemento
 * e realiza a escrita no arquivo bin�rio
 *
 * Recebe como par�metros a lista din�mica e o arquivo bin�rio j� aberto no programa principal.
*/
void gravaLista(Lista *li, FILE *arq) {
    ELEM *no = *li;
    while(no != NULL){
        fwrite(&no->dados, sizeof(CLIENTE), 1, arq);
        no = no->prox;
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

// Exibe os dados do cliente de maneira formatada
void exibeCliente(CLIENTE cli) {
    printf("\t=================================\n");
    printf("\tCodigo: %d\n\n",cli.codigo);
    printf("\tNome: %s\n",cli.nome);
    printf("\tEmpresa: %s\n",cli.empresa);
    printf("\tDepartamento: %s\n",cli.departamento);
    printf("\tTelefone: %s\n",cli.telefone);
    printf("\tCelular: %s\n",cli.celular);
    printf("\tEmail: %s\n",cli.email);
    printf("\t=================================\n");
}

// M�todo utilizado para apagar o \n obtido pelo fgets
void apagarEnter(char *str) {
    int tam = strlen(str);
    if (tam > 0 && str[tam - 1] == '\n') {
        str[tam - 1] = '\0';
    }
}

