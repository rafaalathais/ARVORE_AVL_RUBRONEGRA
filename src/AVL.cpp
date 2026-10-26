#include "AVL.h"
#include <cstdlib>

//calcula a altura de um no
int altura_no(struct NoAVL* no){
    if(no == NULL){
        return -1;
    }else{
        return no->altura;
    }
}

//calcula o fator de balanceamento de um no
int fator_balanceamento_no(struct NoAVL* no){
    return labs(altura_no(no->esquerda)-altura_no(no->direita));
}

NoAVL *busca(ArvAVL arvore, int chave){
    if(chave == NULL || arvore->chave == chave){
        return arvore;
    }
    if(arvore->chave > chave){
        return busca(arvore->esquerda, chave);
    }else{
        return busca(arvore->direita, chave);
    }
}

ArvAVL* criar_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*)malloc(sizeof(ArvAVL));
    if(raiz !=NULL){
        *raiz = NULL;
    }
    return raiz;
}

void libera_no(struct NoAVL* no){
    //percorre a arvore e libera os nós
    if(no == NULL){return;}
    libera_no(no->esquerda);
    libera_no(no->direita);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    //trata a raiz
    if(raiz == NULL){return;}
    libera_no(*raiz);
    free(raiz);
}