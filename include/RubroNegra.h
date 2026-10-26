enum class Cor{
    vermelho,
    preto
}

struct NoRubroNegra{
    int valor;
    Cor cor;
    NoRubroNegra* esquerda;
    NoRubroNegra* direita;
    NoRubroNegra* pai;
}