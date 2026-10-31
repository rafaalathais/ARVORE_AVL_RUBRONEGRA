# Árvore AVL e Árvore Rubro-Negra (LLRB)
Este projeto consiste em um protótipo de sistema logístico desenvolvido para gerenciar, buscar e remover identificadores de encomendas com alta eficiência durante o pico de acessos da Black Friday. O sistema foi implementado utilizando duas estruturas de árvores balanceadas para garantir operações em tempo O(log N): **Árvore AVL** e **Árvore Rubro-Negra caída para a esquerda (LLRB)**.

## Tecnologias
* C++ - implementação das árvores e testes
* Python 3 - gráficos

## Funcionalidades do Sistema
1. **Inserção:** Insere um novo ID na árvore e impede o cadastro de códigos de encomendas duplicados.
2. **Remoção:** Remove um ID da árvore, bloqueia a exclusão de IDs inexistentes e rebalanceia a estrutura em tempo de execução.
3. **Busca:** Localiza encomendas instantaneamente indicando se o código reside ou não na base de dados.
4. **Visualização da estrutura:** 
   - A árvore AVL exibe o fator de balanceamento (FB) ao lado de cada ID.
   - A árvore Rubro-Negra destaca visualmente os nós **vermelhos** e **pretos**.
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
Após selecionar a estrutura, você poderá executar as operações de cadastro, remoção, busca, visualização e exibição ordenada (crescente):
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
- `main.cpp`: menu interativo do usuário.
- `AVL.h` / `AVL.cpp`: definição e implementação da árvore AVL.
- `LLRB.h` / `LLRB.cpp`: definição e implementação da árvore LLRB.
- `testes.cpp` / `graficos.py`: implementação de testes para diferentes cenários do conjunto de dados e geração dos gráficos com matploltlib a fim de realizar análises comparativas dos dois tipos de árvores.
- `programa.exe`: arquivo executável do programa principal
- `dados_testes.csv`: csv com dados gravados por testes.cpp
- `testes.exe`: arquivo executável dos testes

## Como compilar e executar
Pré-requisitos:
* Compilador GCC/C++

### Windows
Na pasta raiz do projeto execute:
```bash
g++ -Iinclude src/main.cpp src/AVL.cpp src/LLRB.cpp -o programa.exe
./programa.exe 
```
### Linux / macOS
Na pasta raiz do projeto execute:
```bash
g++ -Iinclude src/main.cpp src/AVL.cpp src/LLRB.cpp -o programa
./programa 
```

## Decisões de Implementação
* **Mapeamento de cores:** atributo booleano (`cor = true` para vermelho, `false` para preto), os nós nulos (`nullptr`) são tratados como pretos por definição.
* **Interface CLI:** exibição da estrutura com fatores de balanceamento na AVL e marcadores de cor na LLRB via terminal.
* **Retorno da função buscar:** retorno booleano, pois agiliza a verificação.
* **Passagem por referência:** evita o custo de cópia de variáveis globais e locais.

## Testes e Análise
Para avaliar o comportamento das estruturas sob diferentes escalas de volume e distribuições, foram realizados testes em quatro escalas de tamanho (N) em que as duas estruuras se submeteram a inserção, busca e remoção em massa. As métricas coletadas foram: tempo de execução, altura e número de rotações.

## Como rodar os testes
Pré-requisitos:
* Compilador GCC/C++
* Python

Na pasta raiz do projeto execute:
```bash
g++ -Iinclude test/testes.cpp src/AVL.cpp src/LLRB.cpp -o testes.exe
./testes.exe 
```

Depois, para gerar os gráficos de análise, na pasta raiz do projeto execute:
```bash
py test/graficos.py
```
## Autor
* Rafaela Thais de Abreu Lúcio Maia

## Referências 
Este projeto contou com o auxílio pontual da inteligência artificial generativa Google Gemini para suporte na estruturação dos scripts de visualização de dados e auxílio na implementação do código em C++. A lógica das árvores balanceadas foi desenvolvida pelo autor, utilizando como referência:
* https://www.facom.ufu.br/~backes/gsi011/Aula10-Arvores.pdf
* https://www.facom.ufu.br/~backes/gsi011/Aula11-ArvoreAVL.pdf
* https://www.facom.ufu.br/~backes/gsi011/Aula12-ArvoreRB.pdf