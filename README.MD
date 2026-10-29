# Árvore AVL e Árvore Rubro-Negra
Este projeto consiste em um protótipo de sistema logístico desenvolvido para gerenciar, buscar e remover identificadores de encomendas com alta eficiência durante o pico de acessos da Black Friday. 

O sistema foi implementado utilizando duas estruturas de árvores balanceadas para garantir operações em tempo O(log N): **Árvore AVL** e **Árvore Rubro-Negra Caída para a Esquerda (LLRB)**.
## Autor
* Rafaela Thais de Abreu Lúcio Maia

## Tecnologias
* C++ - implementação das árvores
* Python 3 - testes e gráficos

## Como compilar e executar
Pré-requisitos:
* Compilador GCC/C++

### Windows
Na pasta raiz do projeto execute:
```bash
g++ -Iinclude src/main.cpp src/AVL.cpp src/LLRB.cpp -o programa.exe
```
e depois:
```bash
./programa.exe 
```
### Linux / macOS
Na pasta raiz do projeto execute:
```bash
g++ -Iinclude src/main.cpp src/AVL.cpp src/LLRB.cpp -o programa
```
e depois:
```bash
./programa 
```
## Funcionalidades do Sistema
1. **Inserção com Tratamento:** Impede o cadastro de códigos de encomendas duplicados.
2. **Remoção Segura:** Bloqueia a exclusão de IDs inexistentes e rebalanceia a estrutura em tempo de execução.
3. **Busca Eficiente:** Localiza encomendas instantaneamente indicando se o código reside ou não na base de dados.
4. **Visualização da estrutura:** 
   - A árvore AVL exibe o Fator de Balanceamento (FB) ao lado de cada ID.
   - A árvore Rubro-Negra destaca visualmente os nós **Vermelhos** e **Pretos** utilizando cores ANSI direto no console.
5. **Percurso em ordem:** Impressão utilizando percurso em ordem, apresentado os elemnetos em ordem crescente.

## Exmplos de uso
Ao iniciar o programa, escolha qual árvore deseja utilizar para gerenciar os identificadores das encomendas:

```text
======= AMAZON ENGINEERING =======
1. Gerenciar sistema usando Arvore AVL
2. Gerenciar sistema usando Arvore Rubro-Negra (LLRB)
0. Sair do programa
Escolha uma opcao: 1
```
Após selecionar a estrutura, você poderá executar as operações de cadastro, remoção, busca, visualização e ordenação:
```text
--- ARVORE AVL ---
1. Inserir encomenda (ID)
2. Remover encomenda (ID)
3. Buscar encomenda (ID)
4. Visualizar estrutura da arvore
5. Exibir elementos em ordem crescente
0. Voltar ao menu principal
Escolha uma opcao: 1

--- ARVORE AVL ---
1. Inserir encomenda (ID)
2. Remover encomenda (ID)
3. Buscar encomenda (ID)
4. Visualizar estrutura da arvore
5. Exibir elementos em ordem crescente
0. Voltar ao menu principal
Escolha uma opcao: 1
Digite o ID numerico para insercao: 20
Sucesso!

--- ARVORE AVL ---
1. Inserir encomenda (ID)
2. Remover encomenda (ID)
3. Buscar encomenda (ID)
4. Visualizar estrutura da arvore
5. Exibir elementos em ordem crescente
0. Voltar ao menu principal
Escolha uma opcao: 4

===== ESTRUTURA DA ARVORE AVL =====
/-- 20 (FB:0)
================================
```

## Estrutura do Repositório
- `main.cpp`: Menu interativo do usuário e rotinas de testes automatizados.
- `AVL.h` / `AVL.cpp`: Definição e implementação da Árvore AVL.
- `LLRB.h` / `LLRB.cpp`: Definição e implementação da Árvore Rubro-Negra (LLRB).
- `testes.cpp` / `graficos.py`: Implementação de testes para diferentes cenários do conjunto de dados e geração dos gráficos com matploltlib a fim de realizar análises comparativas dos dois tipos de árvores.

## Testes e análise
Para avaliar o comportamento das estruturas sob diferentes escalas de volume e distribuições, foram realizados testes em quatro escalas de tamanho (N) em que as duas estruuras se submeteram a inserção, busca e remoção em massa. A métricas coletadas foram: tempo de execução, altura, número de rotações.

## Como rodar os testes
Pré-requisitos:
* Python

Na pasta raiz do projeto execute:
```bash
g++ -Iinclude test/testes.cpp src/AVL.cpp src/LLRB.cpp -o testes.exe
```
em seguida :
```bash
./testes.exe 
```

Depois, para gerar os gráficos de análise, na pasta raiz do projeto execute:
```bash
py test/graficos.py
```