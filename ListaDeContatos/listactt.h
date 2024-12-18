typedef struct cliente{
    int codigo;
    char nome[50];
    char empresa[40];
    char departamento[25];
    char telefone[14];
    char celular[15];
    char email[40];
} CLIENTE;

typedef struct elemento* Lista;

void abortaPrograma();

Lista *criaLista();

int tamanhoLista(Lista *li);

void liberaLista(Lista *li);

void apresentaMenu();

void exibeCliente(CLIENTE cli);

int consultaCodigo(Lista *li, int cod, CLIENTE *cli);

int consultaNome(Lista *li, char *nome);

int consultaGeral(Lista *li);

int insereCliente(Lista *li, CLIENTE cli);

int coletaDados(Lista *li, CLIENTE *novoCliente);

void leituraLista(Lista *li, FILE *arq);

void gravaLista(Lista *li, FILE *arq);
