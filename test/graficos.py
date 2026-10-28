import pandas as pd
import matplotlib.pyplot as plt

# 1. Carregar os dados
df = pd.read_csv('dados_testes.csv')
cenarios = ['Crescente', 'Decrescente', 'Aleatorio']

plt.style.use('seaborn-v0_8-whitegrid')

def gerar_grafico(coluna_y, titulo, nome_arquivo, label_y):
    fig, axes = plt.subplots(1, 3, figsize=(16, 4.8), sharey=False)
    
    for i, cenario in enumerate(cenarios):
        dados_c = df[df['Cenario'] == cenario]
        avl = dados_c[dados_c['Estrutura'] == 'AVL']
        rb = dados_c[dados_c['Estrutura'] == 'LLRB']
        
        # Plota primeiro a LLRB (vermelho, linha contínua)
        axes[i].plot(rb['N'], rb[coluna_y], label='Rubro-Negra (LLRB)', 
                    color='red', marker='s', linewidth=2.5, zorder=1)
        
        # Plota a AVL (azul, linha pontilhada e zorder alto para NÃO ser coberta quando os valores forem iguais)
        axes[i].plot(avl['N'], avl[coluna_y], label='AVL', 
                    color='blue', marker='o', linestyle='--', linewidth=2, zorder=2)
        
        axes[i].set_title(f'Cenário: {cenario}', fontweight='bold')
        axes[i].set_xlabel('Número de Elementos (N)')
        axes[i].set_ylabel(label_y)
        axes[i].legend()
        axes[i].grid(True, linestyle='--', alpha=0.7)
        
    plt.suptitle(titulo, fontsize=14, fontweight='bold')
    plt.tight_layout()
    plt.savefig(nome_arquivo, dpi=300)
    plt.show()

# ==============================================================================
# GERAR OS 5 GRÁFICOS
# ==============================================================================

# 1. Tempo de Inserção
gerar_grafico('TempoInsercaoMS', 'Comparação de Tempo de Inserção (ms)', 
              'grafico_tempo_insercao.png', 'Tempo (ms)')

# 2. Tempo de Busca
gerar_grafico('TempoBuscaMS', 'Comparação de Tempo de Busca (ms)', 
              'grafico_tempo_busca.png', 'Tempo (ms)')

# 3. Tempo de Remoção
gerar_grafico('TempoRemocaoMS', 'Comparação de Tempo de Remoção (ms)', 
              'grafico_tempo_remocao.png', 'Tempo (ms)')

# 4. Altura Final
gerar_grafico('Altura', 'Comparação de Altura Final da Árvore', 
              'grafico_altura.png', 'Altura Final')

# 5. Quantidade de Rotações
gerar_grafico('Rotacoes', 'Comparação da Quantidade de Rotações', 
              'grafico_rotacoes.png', 'Número de Rotações')

print("Todos os 5 gráficos foram gerados e salvos com sucesso!")