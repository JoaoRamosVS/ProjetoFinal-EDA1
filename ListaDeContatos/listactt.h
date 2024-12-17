typedef struct cliente{
    int codigo;
    char nome[50];
    char empresa[40];
    char departamento[25];
    char telefone[14];
    char celular[15];
    char email[40];
} CLIENTE;

CLIENTE coletaDados();

typedef struct elemento* Lista;

void abortaPrograma();

Lista *criaLista();

int tamanhoLista(Lista *li);

void liberaLista(Lista *li);

void apresentaMenu();

int consultaCodigo(Lista *li, int cod, CLIENTE *cli);

int insereCliente(Lista *li, CLIENTE cli);

void leituraLista(Lista *li, FILE *arq);

void gravaLista(Lista *li, FILE *arq);