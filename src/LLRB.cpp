#include "LLRB.h"
#include <algorithm>
#include <iostream>

ArvoreLLRB::ArvoreLLRB() {
    raiz = nullptr;
}

ArvoreLLRB::~ArvoreLLRB() {
    libera_no(raiz);
}

Cor ArvoreLLRB::obter_cor(NoLLRB* no) {
    if (no == nullptr) return Cor::Preto; // os nós folhas são pretos
    return no->cor;
}

int ArvoreLLRB::calcula_altura(NoLLRB* no) {
    if (no == nullptr) return -1; // Ou 0 se considerar folha nula como 0
    int alt_esq = calcula_altura(no->esquerda);
    int alt_dir = calcula_altura(no->direita);
    return 1 + std::max(alt_esq, alt_dir);
}

int ArvoreLLRB::get_altura() {
    return calcula_altura(raiz);
}

void ArvoreLLRB::trocar_cores(NoLLRB* no) {
    if (no != nullptr) {
        trocas_cor++;
        no->cor = (no->cor == Cor::Vermelho) ? Cor::Preto : Cor::Vermelho;
        if (no->esquerda != nullptr) 
            no->esquerda->cor = (no->esquerda->cor == Cor::Vermelho) ? Cor::Preto : Cor::Vermelho;
        if (no->direita != nullptr) 
            no->direita->cor = (no->direita->cor == Cor::Vermelho) ? Cor::Preto : Cor::Vermelho;
    }
}

void ArvoreLLRB::rotacionar_esquerda(NoLLRB* &A) {
    rotacoes++;
    NoLLRB* B = A->direita;
    A->direita = B->esquerda;
    B->esquerda = A;
    B->cor = A->cor;
    A->cor = Cor::Vermelho;
    A = B;
}

void ArvoreLLRB::rotacionar_direita(NoLLRB* &A) {
    rotacoes++;
    NoLLRB* B = A->esquerda;
    A->esquerda = B->direita;
    B->direita = A;
    B->cor = A->cor;
    A->cor = Cor::Vermelho;
    A = B; 
}

void ArvoreLLRB::balancear(NoLLRB* &H) {
    // nó da direita é vermelho e esquerda é preto
    if (obter_cor(H->direita) == Cor::Vermelho && obter_cor(H->esquerda) == Cor::Preto) {
        rotacionar_esquerda(H);
    }
    // filho e neto da esquerda são vermelhos
    if (obter_cor(H->esquerda) == Cor::Vermelho && obter_cor(H->esquerda->esquerda) == Cor::Vermelho) {
        rotacionar_direita(H);
    }
    // ambos os filhos são vermelhos
    if (obter_cor(H->esquerda) == Cor::Vermelho && obter_cor(H->direita) == Cor::Vermelho) {
        trocar_cores(H);
    }
}

void ArvoreLLRB::mover_vermelho_esquerda(NoLLRB* &H) {
    trocar_cores(H);
    if (obter_cor(H->direita->esquerda) == Cor::Vermelho) {
        rotacionar_direita(H->direita);
        rotacionar_esquerda(H);
        trocar_cores(H);
    }
}

void ArvoreLLRB::mover_vermelho_direita(NoLLRB* &H) {
    trocar_cores(H);
    if (obter_cor(H->esquerda->esquerda) == Cor::Vermelho) {
        rotacionar_direita(H);
        trocar_cores(H);
    }
}

ArvoreLLRB::NoLLRB* ArvoreLLRB::procura_menor(NoLLRB* atual) {
    NoLLRB* no1 = atual;
    NoLLRB* no2 = atual->esquerda;
    while (no2 != nullptr) {
        no1 = no2;
        no2 = no2->esquerda;
    }
    return no1;
}


int ArvoreLLRB::inserir(int valor) {
    int resp = insere_no(raiz, valor);
    if (raiz != nullptr) {
        raiz->cor = Cor::Preto; // raiz sempre é preta
    }
    return resp;
}

int ArvoreLLRB::insere_no(NoLLRB* &H, int valor) {
    if (H == nullptr) {
        H = new NoLLRB(valor);
        if (H == nullptr) return 0;
        return 1;
    }

    if (valor == H->chave) return 0; // não aceita valor duplicado

    int resp;
    if (valor < H->chave) {
        resp = insere_no(H->esquerda, valor);
    } else {
        resp = insere_no(H->direita, valor);
    }

    // na volta da recursão corrige as propriedades violadas
    balancear(H);
    return resp;
}

int ArvoreLLRB::remover_menor(NoLLRB* &H) {
    if (H->esquerda == nullptr) {
        delete H;
        H = nullptr;
        return 1;
    }
    if (obter_cor(H->esquerda) == Cor::Preto && obter_cor(H->esquerda->esquerda) == Cor::Preto) {
        mover_vermelho_esquerda(H);
    }
    remover_menor(H->esquerda);
    balancear(H);
    return 1;
}

int ArvoreLLRB::remover(int valor) {
    // só removemos se o nó existir
    if (!buscar(valor)) return 0; 

    int resp = remove_no(raiz, valor);
    if (raiz != nullptr) {
        raiz->cor = Cor::Preto;
    }
    return resp;
}

int ArvoreLLRB::remove_no(NoLLRB* &H, int valor) {
    if (valor < H->chave) {
        if (obter_cor(H->esquerda) == Cor::Preto && obter_cor(H->esquerda->esquerda) == Cor::Preto) {
            mover_vermelho_esquerda(H);
        }
        remove_no(H->esquerda, valor);
    } else {
        if (obter_cor(H->esquerda) == Cor::Vermelho) {
            rotacionar_direita(H);
        }
        if (valor == H->chave && H->direita == nullptr) {
            delete H;
            H = nullptr;
            return 1;
        }
        if (obter_cor(H->direita) == Cor::Preto && obter_cor(H->direita->esquerda) == Cor::Preto) {
            mover_vermelho_direita(H);
        }
        if (valor == H->chave) {
            NoLLRB* x = procura_menor(H->direita);
            H->chave = x->chave;
            remover_menor(H->direita);
        } else {
            remove_no(H->direita, valor);
        }
    }
    balancear(H);
    return 1;
}

bool ArvoreLLRB::buscar(int chave) {
    return buscar_interno(raiz, chave) != nullptr;
}

ArvoreLLRB::NoLLRB* ArvoreLLRB::buscar_interno(NoLLRB* no, int chave) {
    if (no == nullptr || no->chave == chave) return no;
    if (no->chave > chave) return buscar_interno(no->esquerda, chave);
    return buscar_interno(no->direita, chave);
}

void ArvoreLLRB::libera_no(NoLLRB* no) {
    if (no == nullptr) return;
    libera_no(no->esquerda);
    libera_no(no->direita);
    delete no;
}

void ArvoreLLRB::imprimir_estrutura() {
    std::cout <<"\n===== ESTRUTURA DA ARVORE LLRB =====\n"; 
    
    if (raiz == nullptr) {
        std::cout << "A arvore esta vazia!" << std::endl;
    } else {
        imprimir_arvore(raiz, "", false);
    }
    
    std::cout << "==============================================\n";
}

void ArvoreLLRB::imprimir_arvore(NoLLRB* no, std::string prefixo, bool eh_esquerdo) {
    if (no == nullptr) return;

    imprimir_arvore(no->direita, prefixo + (eh_esquerdo ? "   " : "|    "), false);

    std::cout << prefixo;
    std::cout << (eh_esquerdo ? "\\-- " : "/-- ");
 
    if (no->cor == Cor::Vermelho) {
        std::cout << "\033[1;31m[" << no->chave << " (V)]\033[0m" << std::endl;
    } else {
        std::cout << "[" << no->chave << " (P)]" << std::endl;
    }

    imprimir_arvore(no->esquerda, prefixo + (eh_esquerdo ? "|   " : "    "), true);
}

void ArvoreLLRB::em_ordem(NoLLRB* no) {
    if (no == nullptr) return;
    em_ordem(no->esquerda);
    std::cout << no->chave << " ";
    em_ordem(no->direita);
}

void ArvoreLLRB::imprimir_em_ordem() {
    std::cout << "Elementos em ordem: ";
    em_ordem(raiz);
    std::cout << std::endl;
}
int ArvoreLLRB::get_rotacoes() const{
    return rotacoes;
}

int ArvoreLLRB::get_trocas_cor() const { return trocas_cor; }