#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>
#include "AVL.h"
#include "LLRB.h"

// Função auxiliar para testar e medir operações em uma instância de AVL
void testar_avl(const std::string& cenario, int N, const std::vector<int>& dados, std::ofstream& arq) {
    ArvoreAVL avl;

    // 1. Inserção
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int x : dados) avl.inserir(x);
    auto t2 = std::chrono::high_resolution_clock::now();
    double t_ins = std::chrono::duration<double, std::milli>(t2 - t1).count();

    // 2. Busca (existentes e inexistentes)
    auto t3 = std::chrono::high_resolution_clock::now();
    for (int x : dados) avl.buscar(x);      // existentes
    avl.buscar(-1);                          // inexistente
    auto t4 = std::chrono::high_resolution_clock::now();
    double t_busca = std::chrono::duration<double, std::milli>(t4 - t3).count();

    // Guardar altura e rotações acumuladas até aqui
    int alt = avl.get_altura();
    int rot = avl.get_rotacoes();

    // 3. Remoção
    auto t5 = std::chrono::high_resolution_clock::now();
    for (int x : dados) avl.remover(x);
    auto t6 = std::chrono::high_resolution_clock::now();
    double t_rem = std::chrono::duration<double, std::milli>(t6 - t5).count();

    // Salva no CSV (TrocasCor para AVL é 0)
    arq << "AVL," << cenario << "," << N << "," << alt << "," 
        << rot << ",0," << t_ins << "," << t_busca << "," << t_rem << "\n";
    
    arq.flush();
}

// Função auxiliar para testar e medir operações em uma instância de LLRB
void testar_llrb(const std::string& cenario, int N, const std::vector<int>& dados, std::ofstream& arq) {
    ArvoreLLRB rb;

    // 1. Inserção
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int x : dados) rb.inserir(x);
    auto t2 = std::chrono::high_resolution_clock::now();
    double t_ins = std::chrono::duration<double, std::milli>(t2 - t1).count();

    // 2. Busca
    auto t3 = std::chrono::high_resolution_clock::now();
    for (int x : dados) rb.buscar(x);
    rb.buscar(-1);
    auto t4 = std::chrono::high_resolution_clock::now();
    double t_busca = std::chrono::duration<double, std::milli>(t4 - t3).count();

    int alt = rb.get_altura();
    int rot = rb.get_rotacoes();
    int trocas = rb.get_trocas_cor();

    // 3. Remoção
    auto t5 = std::chrono::high_resolution_clock::now();
    for (int x : dados) rb.remover(x);
    auto t6 = std::chrono::high_resolution_clock::now();
    double t_rem = std::chrono::duration<double, std::milli>(t6 - t5).count();

    arq << "LLRB," << cenario << "," << N << "," << alt << "," 
        << rot << "," << trocas << "," << t_ins << "," << t_busca << "," << t_rem << "\n";

    arq.flush();
}

void executar_benchmark() {
    std::ofstream arq("dados_testes.csv");
    arq << "Estrutura,Cenario,N,Altura,Rotacoes,TrocasCor,TempoInsercaoMS,TempoBuscaMS,TempoRemocaoMS\n";

    std::vector<int> tamanhos = {1000, 5000, 10000, 50000};
    std::mt19937 g(1337); // Semente fixa para reprodutibilidade nos testes

    for (int N : tamanhos) {
        // Gerar vetores de entrada
        std::vector<int> crescente(N);
        std::iota(crescente.begin(), crescente.end(), 1);

        std::vector<int> decrescente = crescente;
        std::reverse(decrescente.begin(), decrescente.end());

        std::vector<int> aleatorio = crescente;
        std::shuffle(aleatorio.begin(), aleatorio.end(), g);

        // Executar os testes para cada cenário
        testar_avl("Crescente", N, crescente, arq);
        testar_llrb("Crescente", N, crescente, arq);

        testar_avl("Decrescente", N, decrescente, arq);
        testar_llrb("Decrescente", N, decrescente, arq);

        testar_avl("Aleatorio", N, aleatorio, arq);
        testar_llrb("Aleatorio", N, aleatorio, arq);
    }

    arq.close();
    std::cout << "Testes concluídos com sucesso! Arquivo dados_testes.csv gerado." << std::endl;
}

int main() {
    executar_benchmark();
    return 0;
}