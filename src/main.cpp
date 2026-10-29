#include <iostream>
#include "AVL.h"
#include <fstream>
#include "LLRB.h"
using namespace std;

void menu_rubro_negra() {
    ArvoreLLRB rb;
    int opcao, valor;

    do {
        std::cout << "\n--- ARVORE RUBRO-NEGRA (LLRB) ---\n";
        std::cout << "1. Inserir encomenda (ID)\n";
        std::cout << "2. Remover encomenda (ID)\n";
        std::cout << "3. Buscar encomenda (ID)\n";
        std::cout << "4. Visualizar estrutura da arvore\n";
        std::cout << "5. Exibir elementos em ordem crescente\n";
        std::cout << "0. Voltar ao menu principal\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                std::cout << "Digite o ID numérico para insercao: ";
                std::cin >> valor;
                if (rb.inserir(valor) == 1) std::cout << "Sucesso!\n";
                else std::cout << "Erro: ID duplicado ou falha.\n";
                break;
            case 2:
                std::cout << "Digite o ID numérico para remocao: ";
                std::cin >> valor;
                if (rb.remover(valor) == 1) std::cout << "Removido com sucesso!\n";
                else std::cout << "Erro: ID nao encontrado.\n";
                break;
            case 3:
                std::cout << "Digite o ID numérico para busca: ";
                std::cin >> valor;
                if (rb.buscar(valor)) std::cout << "Encomenda localizada no sistema.\n";
                else std::cout << "Encomenda inexistente.\n";
                break;
            case 4:
                rb.imprimir_estrutura();
                break;
            case 5:
                rb.imprimir_em_ordem();
                break;
        }
    } while (opcao != 0);
}

void menu_avl() {
    ArvoreAVL avl;
    int opcao, valor;

    do {
        std::cout << "\n--- ARVORE AVL ---\n";
        std::cout << "1. Inserir encomenda (ID)\n";
        std::cout << "2. Remover encomenda (ID)\n";
        std::cout << "3. Buscar encomenda (ID)\n";
        std::cout << "4. Visualizar estrutura da arvore\n";
        std::cout << "5. Exibir elementos em ordem crescente\n";
        std::cout << "0. Voltar ao menu principal\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                std::cout << "Digite o ID numérico para insercao: ";
                std::cin >> valor;
                if (avl.buscar(valor)){
                    std::cout << "Erro: ID duplicado ou falha.\n";
                }else{
                   avl.inserir(valor);
                    std::cout << "Sucesso!\n";
                } 
                break;
            case 2:
                std::cout << "Digite o ID numérico para remocao: ";
                std::cin >> valor;
                if (!avl.buscar(valor)) {
                    std::cout << "Erro: ID nao encontrado no sistema logistico.\n";
                } else {
                    avl.remover(valor);
                    std::cout << "Removido com sucesso!\n";
                }
                break;
            case 3:
                std::cout << "Digite o ID numérico para busca: ";
                std::cin >> valor;
                if (avl.buscar(valor)) std::cout << "Encomenda localizada no sistema.\n";
                else std::cout << "Encomenda inexistente.\n";
                break;
            case 4:
                avl.imprimir_estrutura();
                break;
            case 5:
                avl.imprimir_em_ordem();
                break;
        }
    } while (opcao != 0);
}

int main(){
   
    int escolha;
    do {
        std::cout << "\n======= AMAZON ENGINEERING =======\n";
        std::cout << "1. Gerenciar sistema usando Arvore AVL\n";
        std::cout << "2. Gerenciar sistema usando Arvore Rubro-Negra (LLRB)\n";
        std::cout << "0. Sair do programa\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> escolha;

        if (escolha == 1) {
            menu_avl(); 
        } else if (escolha == 2) {
            menu_rubro_negra();
        }
    } while (escolha != 0);
}