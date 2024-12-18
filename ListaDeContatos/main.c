#include <stdio.h>
#include <stdlib.h>
#include "listactt.h"

int main(){
    int codigo=0, x=0, y=0;
    Lista *li = NULL;
    char r;
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
        r = getchar();
        switch(r) {
            case '1' :
                system("cls");
                CLIENTE novoCliente;
                x = coletaDados(li, &novoCliente);
                if(x) {
                    insereCliente(li, novoCliente);
                    if(x) {
                        printf("\n\nContato %d inserido com sucesso na lista de contatos!\n\n", x);
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

            case '5' :
                system("cls");
                printf("\n\nQual o codigo do cliente que deve ser editado?\n\n");
                scanf("%d", &y);
                x = editaContato(li, y);
                if(x){
                    printf("\n\nO contato nCOLOCAR AQUELA BOLINHA PEQUENA %d foi editado com sucesso!! \n\n", y);
                } else {
                    printf("\n\n %d %d >:( !! \n\n",x , y);
                }
                system("pause");
                break;

            case '6' :
                system("cls");
                printf("\n\nQual o codigo do cliente que deve ser removido?\n\n");
                scanf("%d", &y);
                x = removeOrdenado(li, y);
                if(x){
                    printf("\n\nO contato nCOLOCAR AQUELA BOLINHA PEQUENA%d foi removido com sucesso!! \n\n", y);
                } else {
                    printf("\n\n %d O contato nCOLOCAR AQUELA BOLINHA PEQUENA %d nao foi removido >:( !! \n\n",x , y);
                }

                system("pause");
                break;



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
