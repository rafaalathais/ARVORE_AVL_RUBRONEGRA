#ifndef AVL_H
#define AVL_H
#include <string>

class ArvoreAVL{

private:
    struct NoAVL {
    int chave;
    int altura;
    NoAVL* esquerda;
    NoAVL* direita;

    NoAVL(int valor){
        chave = valor;
        altura =0;
        esquerda = nullptr;
        direita = nullptr;
    };

    };

    NoAVL* raiz;
    int rotacoes =0;

    int altura_arvore(NoAVL* no);
    int fator_balanceamento_no(struct NoAVL* no);

    NoAVL* buscar(NoAVL* no, int chave);
    int inserir(NoAVL* &no, int chave);
    int remover(NoAVL* &no, int chave);
    NoAVL* procuraMenor(NoAVL* atual);

    void libera_no(struct NoAVL* no);
    void em_ordem(NoAVL* no);

    void rotacaoLL(NoAVL* &raiz);
    void rotacaoRR(NoAVL* &raiz);
    void rotacaoRL(NoAVL* &raiz);
    void rotacaoLR(NoAVL* &raiz);
    void imprimir_arvore(NoAVL* no, std::string prefixo, bool eh_esquerdo);

public:
    ArvoreAVL();
    ~ArvoreAVL();

    void inserir(int chave);
    void remover(int chave);
    bool buscar(int chave);
    void imprimir_estrutura();
    int get_altura();
    void imprimir_em_ordem();
    int get_rotacoes() const { return rotacoes; }
};


#endif