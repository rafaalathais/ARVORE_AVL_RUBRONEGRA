#include "AVL.h"
#include <cstdlib>
#include <algorithm>

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
    return labs(altura_arvore(no->esquerda)-altura_arvore(no->direita));
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
    NoAVL *no = raiz->esquerda;
    raiz->esquerda = no->direita;
    no->direita = raiz;

    raiz->altura = std::max(altura_arvore(raiz->esquerda), altura_arvore(raiz->direita)) + 1;
    no->altura = std::max(altura_arvore(no->esquerda),raiz->altura) +1;

    raiz = no;

}

void ArvoreAVL::rotacaoRR(NoAVL* &raiz){
    NoAVL *no = raiz->direita;
    raiz->direita = no->esquerda;
    no->esquerda = raiz;

    raiz->altura = std::max(altura_arvore(raiz->esquerda), altura_arvore(raiz->direita)) + 1;
    no->altura = std::max(altura_arvore(no->direita),raiz->altura) +1;

    raiz = no;

}

void ArvoreAVL::rotacaoRL(NoAVL* &raiz){
    rotacaoRR(raiz->esquerda);
    rotacaoLL(raiz);
}

void ArvoreAVL::rotacaoLR(NoAVL* &raiz){
   rotacaoRR(raiz->esquerda);
   rotacaoLL(raiz);
}

int ArvoreAVL::inserir(NoAVL* &no, int chave){
    int res;
    // se achou posicao vazia insere
    if(no == nullptr){
        no = new NoAVL(chave);
        if(no == nullptr){
            return 0;
        }
        return 1;
    }else{
        if(chave > no->chave){
            if((res=inserir(no->direita, chave))==1){
                // se a arvore desbalanceou para a direita
                if(fator_balanceamento_no(no)>=2){

                    //compara com a chave do filho da direita
                    if(no->direita->chave < chave){
                        rotacaoRR(no);
                    }else{
                        rotacaoRL(no);
                    }
                }
            }
        }else{
            //chave já existe (duplicado)
            return 0;
        }
        no->altura = std::max(altura_arvore(no->esquerda), altura_arvore(no->direita)) + 1;

        return res;
    }
}
    

int ArvoreAVL::remover(NoAVL* &no, int chave){
    if(no == nullptr) {
        //chave não existe na árvore
        return 0; 
    }

    int res;
    // chave está na subárvore Esquerda
    if(chave < no->chave) {
        if ((res = remover(no->esquerda,chave)) == 1) {
            if (fator_balanceamento_no(no) >= 2) {
                if (altura_arvore(no->direita->esquerda) <= altura_arvore(no->direita->direita))
                    rotacaoRR(no);
                else
                    rotacaoRL(no);
            }
        }
        return res;
    }

    // chave está na subárvore direita
    if(no->chave < chave) {
        if ((res = remover(no->direita,chave)) == 1) {
            if (fator_balanceamento_no(no) >= 2) {
                if (altura_arvore(no->esquerda->direita) <=altura_arvore(no->esquerda->esquerda))
                    rotacaoLL(no);
                else
                    rotacaoLR(no);
            }
        }
        return res;
    }

    // encontramos o nó a ser removido
    if(no->chave ==chave) {

        // tem 1 filho ou nenhum
        if(no->esquerda == nullptr || no->direita == nullptr){
            NoAVL* velhoNode = no;
            if(no->esquerda != nullptr)
                no = no->esquerda; // O filho esquerdo assume o lugar do pai
            else
                no = no->direita;  // O filho direito assume o lugar do pai (ou vira nullptr)
            
            delete velhoNode; // libera a memória em C++
            return 1;
        } 
        // O nó possui 2 filhos
        else {
            NoAVL* temp = procuraMenor(no->direita);
            no->chave = temp->chave; // Copia ochave do substituto
            remover(no->direita, no->chave); // Remove o substituto original na direita
            
            // Rebalanceamento após a remoção no nó de 2 filhos
            if(fator_balanceamento_no(no) >= 2) {
                if (altura_arvore(no->esquerda->direita) <= altura_arvore(no->esquerda->esquerda))
                    rotacaoLL(no);
                else{
                    rotacaoLR(no);
            }
            return 1;
        }
    }

    // Atualiza a altura do nó atual se ele ainda existir
    if (no != nullptr) {
        no->altura = std::max(altura_arvore(no->esquerda),altura_arvore(no->direita)) + 1;
    }

    return res;

}
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
    
    // Se o ponteiro retornado for diferente de nulo, significa que encontrou!
    if (resultado != nullptr) {
        return true;
    }
    
    return false; // Se for nulo, o valor não existe na árvore
}

void ArvoreAVL::inserir(int chave) {
    // Ela pega o atributo privado 'raiz' da classe e joga na função interna 
    // que faz todo o trabalho de ponteiros, recursão e rotações.
    inserir(raiz, chave);
}


