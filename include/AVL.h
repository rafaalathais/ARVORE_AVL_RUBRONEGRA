
typedef struct NoAVL* ArvAVL;

struct NoAVL {
    int chave; //atributo de identificacao
    int conteudo;//informacao armazenada no nó 
    NoAVL* esquerda;
    NoAVL* direita;
};

int altura_no(struct NoAVL* no);
int altura_arvore(NoAVL* no);
int fator_balanceamento_no(struct NoAVL* no);
NoAVL *buscar(ArvAVL arvore, int chave);
NoAVL *inserir(ArvAVL arvore, int chave);
NoAVL *remover(ArvAVL arvore, int chave);
ArvAVL* criar_ArvAVL();
void libera_no(struct NoAVL* no);
void libera_ArvAVL(ArvAVL* raiz);
