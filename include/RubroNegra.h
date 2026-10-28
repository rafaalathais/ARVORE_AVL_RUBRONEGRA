#ifndef RUBRONEGRA_H
#define RUBRONEGRA_H

enum class Cor { Vermelho, Preto };

class ArvoreLLRB {
private:
    struct NoRBN {
        int chave;
        NoRBN* esquerda;
        NoRBN* direita;
        Cor cor;

        NoRBN(int valor) {
            chave = valor;
            esquerda = nullptr;
            direita = nullptr;
            cor = Cor::Vermelho;
        }
    };

    NoRBN* raiz;

    Cor obter_cor(NoRBN* no);
    void trocar_cores(NoRBN* no);
    
    void rotacionar_esquerda(NoRBN* &A);
    void rotacionar_direita(NoRBN* &A);
    void balancear(NoRBN* &H);
    
    void mover_vermelho_esquerda(NoRBN* &H);
    void mover_vermelho_direita(NoRBN* &H);
    NoRBN* procura_menor(NoRBN* atual);
    
    int insere_no(NoRBN* &H, int valor);
    int remove_no(NoRBN* &H, int valor);
    int remover_menor(NoRBN* &H);
    
    void libera_no(NoRBN* no);
    NoRBN* buscar_interno(NoRBN* no, int chave);

public:
    ArvoreLLRB();
    ~ArvoreLLRB();

    int inserir(int valor);
    int remover(int valor);
    bool buscar(int chave);
};

#endif
