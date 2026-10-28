#include "AVL.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>

//Construtor
ArvoreAVL::ArvoreAVL() {
    raiz = nullptr;
}

ArvoreAVL::~ArvoreAVL() {
    libera_no(raiz);
}

//calcula a altura de um no
int ArvoreAVL::altura_arvore(NoAVL* no){
    if(no == NULL){
        return -1;
    }else{
        return no->altura;
    }
}

//calcula o fator de balanceamento de um no
int ArvoreAVL::fator_balanceamento_no(NoAVL* no){
    if (no==nullptr) return 0;
    return altura_arvore(no->esquerda)-altura_arvore(no->direita);
}

int ArvoreAVL::get_altura(){
    return altura_arvore(raiz);
}

ArvoreAVL::NoAVL* ArvoreAVL::buscar(NoAVL* no, int chave){
    if(no == nullptr || no->chave == chave){
        return no;
    }
    if(no->chave > chave){
        return buscar(no->esquerda, chave);
    }else{
        return buscar(no->direita, chave);
    }
}

void ArvoreAVL::libera_no(NoAVL* no){
    //percorre a arvore e libera os nós
    if(no == nullptr){return;}
    libera_no(no->esquerda);
    libera_no(no->direita);
    delete no;
    no = nullptr;
}

void ArvoreAVL::rotacaoLL(NoAVL* &raiz){
    rotacoes++;
    NoAVL *no = raiz->esquerda;
    raiz->esquerda = no->direita;
    no->direita = raiz;

    raiz->altura = std::max(altura_arvore(raiz->esquerda), altura_arvore(raiz->direita)) + 1;
    no->altura = std::max(altura_arvore(no->esquerda),raiz->altura) +1;

    raiz = no;

}

void ArvoreAVL::rotacaoRR(NoAVL* &raiz){
    rotacoes++;
    NoAVL *no = raiz->direita;
    raiz->direita = no->esquerda;
    no->esquerda = raiz;

    raiz->altura = std::max(altura_arvore(raiz->esquerda), altura_arvore(raiz->direita)) + 1;
    no->altura = std::max(altura_arvore(no->direita),raiz->altura) +1;

    raiz = no;

}

void ArvoreAVL::rotacaoRL(NoAVL* &raiz){
    rotacaoLL(raiz->direita);
    rotacaoRR(raiz);
}

void ArvoreAVL::rotacaoLR(NoAVL* &raiz){
   rotacaoRR(raiz->esquerda);
   rotacaoLL(raiz);
}

int ArvoreAVL::inserir(NoAVL* &no, int chave){
    int res;
    if (no == nullptr){
        no = new NoAVL(chave);
        if (no == nullptr) return 0;
        return 1;
    } else {
        if (chave > no->chave){
            if ((res = inserir(no->direita, chave)) == 1){
                if (fator_balanceamento_no(no) <= -2){
                    if (chave > no->direita->chave){
                        rotacaoRR(no);
                    } else {
                        rotacaoRL(no);
                    }
                }
            }
        } else if (chave < no->chave){
            if ((res = inserir(no->esquerda, chave)) == 1){
                if (fator_balanceamento_no(no) >= 2){
                    if (chave < no->esquerda->chave){
                        rotacaoLL(no);
                    } else {
                        rotacaoLR(no);
                    }
                }
            }
        } else {
            return 0; // chave duplicada
        }

        no->altura = std::max(altura_arvore(no->esquerda), altura_arvore(no->direita)) + 1;
        return res;
    }
}
    

int ArvoreAVL::remover(NoAVL* &no, int chave) {
    if (no == nullptr) {
        return 0; // Chave não encontrada
    }

    int res;
    if (chave < no->chave) {
        res = remover(no->esquerda, chave);
    } else if (chave > no->chave) {
        res = remover(no->direita, chave);
    } else {
        // Encontrou o nó a remover
        if (no->esquerda == nullptr || no->direita == nullptr) {
            NoAVL* velhoNode = no;
            if (no->esquerda != nullptr)
                no = no->esquerda;
            else
                no = no->direita;
            delete velhoNode;
            return 1;
        } else {
            NoAVL* temp = procuraMenor(no->direita);
            no->chave = temp->chave;
            remover(no->direita, no->chave);
            res = 1;
        }
    }

    if (no == nullptr) return res;

    // 1. Atualiza a altura do nó atual
    no->altura = std::max(altura_arvore(no->esquerda), altura_arvore(no->direita)) + 1;

    // 2. Verifica e aplica o rebalanceamento pós-remoção
    int fb = fator_balanceamento_no(no);

    // Desbalanceado para a ESQUERDA
    if (fb >= 2) {
        if (fator_balanceamento_no(no->esquerda) >= 0)
            rotacaoLL(no);
        else
            rotacaoLR(no);
    } 
    // Desbalanceado para a DIREITA
    else if (fb <= -2) {
        if (fator_balanceamento_no(no->direita) <= 0)
            rotacaoRR(no);
        else
            rotacaoRL(no);
    }

    return res;
}

ArvoreAVL::NoAVL* ArvoreAVL::procuraMenor(NoAVL* atual) {
    NoAVL* no1 = atual;
    NoAVL* no2 = atual->esquerda;
    while (no2 != nullptr) {
        no1 = no2;
        no2 = no2->esquerda;
    }
    return no1;
}

void ArvoreAVL::remover(int chave) {
    remover(raiz, chave);
}
bool ArvoreAVL::buscar(int chave) {
    NoAVL* resultado = buscar(raiz, chave);
    // se o ponteiro retornado for diferente de nulosignifica que encontrou
    if (resultado != nullptr) {
        return true;
    }
    
    return false; //se for nulo, o valor não existe na árvore
}

void ArvoreAVL::inserir(int chave) {
    inserir(raiz, chave);
}

void ArvoreAVL::imprimir_estrutura() {
    std::cout << "\n===== ESTRUTURA DA ARVORE AVL =====\n";
    if (raiz == nullptr) {
        std::cout << "A arvore esta vazia!" << std::endl;
    } else {
        imprimir_arvore(raiz, "", false);
    }
    std::cout << "================================\n";
}

void ArvoreAVL::imprimir_arvore(NoAVL* no, std::string prefixo, bool eh_esquerdo) {
    if (no == nullptr) return;

   
    imprimir_arvore(no->direita, prefixo + (eh_esquerdo ? "|   " : "    "), false);

    std::cout << prefixo;
    std::cout << (eh_esquerdo ? "\\-- " : "/-- ");
    std::cout << no->chave << " (FB:" << fator_balanceamento_no(no) << ")\n";
    imprimir_arvore(no->esquerda, prefixo + (eh_esquerdo ? "    " : "|   "), true);
}

void ArvoreAVL::em_ordem(NoAVL* no) {
    if (no == nullptr) return;
    em_ordem(no->esquerda);
    std::cout << no->chave << " ";
    em_ordem(no->direita);
}

void ArvoreAVL::imprimir_em_ordem() {
    std::cout << "Elementos em ordem: ";
    em_ordem(raiz);
    std::cout << std::endl;
}
