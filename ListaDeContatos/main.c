#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listactt.h"

int main(){
    int codigo=0, x=0, y=0;
    Lista *li = NULL;
    char r, buscaNome[50];
    CLIENTE cli_consulta;
    FILE *f;
    printf("Hello branch joaorvs!\n");

    if((li = criaLista()) == NULL){
        abortaPrograma();
    }

    f = fopen("contatos.txt", "rb");
    if(f != NULL) {
        leituraLista(li,f);
    }
    fclose(f);

    while(r != '7') {
        system("cls");
        apresentaMenu();
        fflush(stdin);
        r = getchar();
        switch(r) {
            case '1' :
                system("cls");
                CLIENTE novoCliente;
                x = coletaDados(li, &novoCliente);
                if(x) {
                    x = insereCliente(li, novoCliente);
                    if(x) {
                        printf("\n\nCliente %d inserido com sucesso na lista de contatos!\n\n", x);
                    }
                    else {
                        printf("\n\nNao foi possivel inserir o cliente na lista de contatos.\n\n");
                    }
                }
                else {
                    printf("\n\nInsercao encerrada.\n\n");
                }

                system("pause");
                break;

            case '2' :
                system("cls");
                x = consultaGeral(li);
                if(!x) {
                    printf("\n\nNao existem registros na lista de contatos.\n\n");
                }
                system("pause");
                break;

            case '3' :
                 system("cls");
                 printf("Digite o codigo do cliente: ");
                 scanf("%d", &codigo);
                 x = consultaCodigo(li, codigo, &cli_consulta);
                 if(x) {
                    exibeCliente(cli_consulta);
                 }
                 else{
                    printf("\n\nNao foi possivel encontrar este codigo na lista de contatos.\n\n");
                 }
                 system("pause");
                break;

            case '4' :
                    system("cls");
                    printf("Digite o nome que deseja buscar: ");
                    fflush(stdin);
                    fgets(buscaNome, 49, stdin);
                    x = consultaNome(li, buscaNome);
                    if(!x) {
                        printf("\n\nNao foi possivel encontrar este nome na lista de contatos.\n\n");
                    }
                    system("pause");
                    break;

            case '5' :
                system("cls");
                printf("Digite o codigo do cliente para edicao: ");
                scanf("%d", &y);
                printf("\n");
                x = editaCliente(li, y);
                if(x){
                    printf("\n\nO cliente %d foi editado com sucesso!\n\n", y);
                } else {
                    printf("\n\nEdicao abortada.\n\n");
                }
                system("pause");
                break;

            case '6' :
                system("cls");
                printf("Digite o codigo do cliente para remocao: ");
                scanf("%d", &y);
                x = removeCliente(li, y);
                if(x){
                    printf("\n\nO cliente %d foi removido com sucesso!\n\n", y);
                } else {
                    printf("\n\nNao foi possivel remover este cliente da lista.\n\n");
                }
                system("pause");
                break;

            case '7' :
                break;

            default :
                printf("\n\nOpcao invalida, tente novamente!\n\n");
                system("pause");
        }
    }

    f = fopen("contatos.txt", "wb");
    if(f == NULL) {
        printf("Erro na abertura do arquivo. Dados não serão salvos.\n\n");
        system("pause");
        exit(1);
    }

    gravaLista(li, f);
    liberaLista(li);
    fclose(f);
    return 0;
}
