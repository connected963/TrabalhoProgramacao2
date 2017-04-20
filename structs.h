typedef struct FILME Filme;
typedef struct ATOR Ator;
typedef struct DIRETOR Diretor;
typedef struct PERSONAGEM Personagem;
typedef struct POINTER_FILME pointerFilme;
typedef struct POINTER_ATOR pointerAtor;
typedef struct POINTER_DIRETOR pointerDiretor;
typedef struct POINTER_PERSONAGEM pointerPersonagem;

struct FILME{
  char nome[150];
  int ano;
  int cont;
  pointerAtor *atores;
  pointerDiretor *diretores;
  Filme *prox;
  Filme *ant;
};

struct ATOR{
  char nome[150];
  pointerFilme *filmes;
  Ator *prox;
  Ator *ant;
};

struct DIRETOR{
  char nome[150];
  pointerFilme *filmes;
  Diretor *prox;
  Diretor *ant;
};

struct PERSONAGEM{
  char nome[150];
  Personagem *prox;
};

struct POINTER_FILME{
  Filme *filme;
  Personagem *personagens;
  pointerFilme *prox;
};

struct POINTER_ATOR{
  Ator *ator;
  pointerAtor *prox;
};

struct POINTER_DIRETOR{
  Diretor *diretor;
  pointerDiretor *prox;
};
