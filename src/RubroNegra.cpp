#include "RubroNegra.h"
#include <algorithm>

ArvoreLLRB::ArvoreLLRB() {
    raiz = nullptr;
}

ArvoreLLRB::~ArvoreLLRB() {
    libera_no(raiz);
}

Cor ArvoreLLRB::obter_cor(NoRBN* no) {
    if (no == nullptr) return Cor::Preto; // os nós folhas são pretos
    return no->cor;
}

void ArvoreLLRB::trocar_cores(NoRBN* no) {
    if (no != nullptr) {
        no->cor = (no->cor == Cor::Vermelho) ? Cor::Preto : Cor::Vermelho;
        if (no->esquerda != nullptr) 
            no->esquerda->cor = (no->esquerda->cor == Cor::Vermelho) ? Cor::Preto : Cor::Vermelho;
        if (no->direita != nullptr) 
            no->direita->cor = (no->direita->cor == Cor::Vermelho) ? Cor::Preto : Cor::Vermelho;
    }
}

void ArvoreLLRB::rotacionar_esquerda(NoRBN* &A) {
    NoRBN* B = A->direita;
    A->direita = B->esquerda;
    B->esquerda = A;
    B->cor = A->cor;
    A->cor = Cor::Vermelho;
    A = B;
}

void ArvoreLLRB::rotacionar_direita(NoRBN* &A) {
    NoRBN* B = A->esquerda;
    A->esquerda = B->direita;
    B->direita = A;
    B->cor = A->cor;
    A->cor = Cor::Vermelho;
    A = B; 
}

void ArvoreLLRB::balancear(NoRBN* &H) {
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

void ArvoreLLRB::mover_vermelho_esquerda(NoRBN* &H) {
    trocar_cores(H);
    if (obter_cor(H->direita->esquerda) == Cor::Vermelho) {
        rotacionar_direita(H->direita);
        rotacionar_esquerda(H);
        trocar_cores(H);
    }
}

void ArvoreLLRB::mover_vermelho_direita(NoRBN* &H) {
    trocar_cores(H);
    if (obter_cor(H->esquerda->esquerda) == Cor::Vermelho) {
        rotacionar_direita(H);
        trocar_cores(H);
    }
}

ArvoreLLRB::NoRBN* ArvoreLLRB::procura_menor(NoRBN* atual) {
    NoRBN* no1 = atual;
    NoRBN* no2 = atual->esquerda;
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

int ArvoreLLRB::insere_no(NoRBN* &H, int valor) {
    if (H == nullptr) {
        H = new NoRBN(valor);
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

int ArvoreLLRB::remover_menor(NoRBN* &H) {
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

int ArvoreLLRB::remove_no(NoRBN* &H, int valor) {
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
            NoRBN* x = procura_menor(H->direita);
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

ArvoreLLRB::NoRBN* ArvoreLLRB::buscar_interno(NoRBN* no, int chave) {
    if (no == nullptr || no->chave == chave) return no;
    if (no->chave > chave) return buscar_interno(no->esquerda, chave);
    return buscar_interno(no->direita, chave);
}

void ArvoreLLRB::libera_no(NoRBN* no) {
    if (no == nullptr) return;
    libera_no(no->esquerda);
    libera_no(no->direita);
    delete no;
}
