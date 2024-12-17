#include <stdio.h>
#include <stdlib.h>
#include "listactt.h"

int main()
{
    int codigo=0, x=0;
    char r;
    FILE *f;
    printf("Hello branch joaorvs!\n");

    f = fopen("contatos.txt", "rb");
    /*if(f != NULL) {

    }*/
    fclose(f);
    while(r != '7') {
        system("cls");
        apresentaMenu();
        r = getchar();
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
    return 0;
}
