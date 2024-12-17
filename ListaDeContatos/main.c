#include <stdio.h>
#include <stdlib.h>
#include "listactt.h"

int main()
{
    int codigo=0, x=0;
    Lista *li = NULL;
    char r;
    FILE *f;
    printf("Hello branch joaorvs!\n");

    if((li = criaLista()) == NULL){
        abortaPrograma();
    }

    f = fopen("contatos.txt", "rb");
    /*if(f != NULL) {

    }*/
    fclose(f);
    while(r != '7') {
        system("cls");
        apresentaMenu();
        r = getchar();
        switch(r) {
            case '1' :
                system("cls");
                CLIENTE novoCliente = coletaDados();
                x = insereCliente(li, novoCliente);
                if(x) {
                    printf("\n\nContato %d inserido com sucesso na lista de contatos!\n\n", x);
                }
                else {
                    printf("\n\nNao foi possivel inserir o cliente na lista de contatos.\n\n");
                }
                system("pause");
                break;
        }
    }
    /*case '3' :
     system("cls");
     printf("Digite o codigo do cliente: ");
     scanf("%d", &codigo);
     if(x) {
        ...
     }
    break;
    */
    liberaLista(li);
    return 0;
}
