#ifndef LLRB_H
#define LLRB_H
#include <string>

enum class Cor { Vermelho, Preto };

class ArvoreLLRB {
private:
    struct NoLLRB {
        int chave;
        NoLLRB* esquerda;
        NoLLRB* direita;
        Cor cor;

        NoLLRB(int valor) {
            chave = valor;
            esquerda = nullptr;
            direita = nullptr;
            cor = Cor::Vermelho;
        }
    };

    NoLLRB* raiz;
    int rotacoes = 0;
    int trocas_cor = 0;

    Cor obter_cor(NoLLRB* no);
    void trocar_cores(NoLLRB* no);
    
    void rotacionar_esquerda(NoLLRB* &no);
    void rotacionar_direita(NoLLRB* &no);
    void balancear(NoLLRB* &no);
    
    void mover_vermelho_esquerda(NoLLRB* &no);
    void mover_vermelho_direita(NoLLRB* &no);
    NoLLRB* procura_menor(NoLLRB* atual);
    
    int insere_no(NoLLRB* &H, int valor);
    int remove_no(NoLLRB* &H, int valor);
    int remover_menor(NoLLRB* &H);
    int calcula_altura(NoLLRB* no);
    void em_ordem(NoLLRB* no);
    
    void libera_no(NoLLRB* no);
    NoLLRB* buscar_interno(NoLLRB* no, int chave);
     void imprimir_arvore(NoLLRB* no, std::string prefixo, bool eh_esquerdo);

public:
    ArvoreLLRB();
    ~ArvoreLLRB();

    int inserir(int valor);
    int remover(int valor);
    bool buscar(int chave);
    void imprimir_estrutura();
    int get_altura();
    void imprimir_em_ordem();
    int get_rotacoes() const;
    int get_trocas_cor() const;

};

#endif
