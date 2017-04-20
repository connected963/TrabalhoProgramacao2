void removerPointersAtorPorFilme(Filme *filme, Ator **inicio, Ator **fim);
void removerPointersDiretorPorFilme(Filme *filme, Diretor **inicio, Diretor **fim);
void removerAtorDeFilme(Ator *ator);
void removerPointerAtor(pointerAtor **inicio, char ator[]);
void removerPointerDiretor(pointerDiretor **inicio, char diretor[]);
void removerDiretorDeFilme(Diretor *diretor);
void removerPersonagens(Personagem *personagem);
Personagem* containsPersonagem(Personagem *personagem, char nome[]);

/**
* Operações relacionadas a filme
*/

void inserirFilme(Filme **inicio, Filme **fim, Filme *novoFilme) {
  Filme *aux = *inicio;
  if(*fim == NULL) {
    *inicio = novoFilme;
    *fim = *inicio;
  }
  else if(novoFilme->ano <= (*inicio)->ano  && strcasecmp(novoFilme->nome, (*inicio)->nome) == 0 || strcasecmp(novoFilme->nome, (*inicio)->nome) <= 0) {
    novoFilme->prox = *inicio;

    (*inicio)->ant = novoFilme;
    *inicio = novoFilme;
  }
  else if(novoFilme->ano >= (*fim)->ano && strcasecmp(novoFilme->nome, (*fim)->nome) == 0 || strcasecmp(novoFilme->nome, (*fim)->nome) >= 0) {
    novoFilme->ant = *fim;

    (*fim)->prox = novoFilme;
    *fim = novoFilme;
  } else {
    while(aux->prox != NULL && (strcasecmp((aux->prox)->nome, novoFilme->nome) == 0 && (aux->prox)->ano < novoFilme->ano || strcasecmp((aux->prox)->nome, novoFilme->nome) < 0)) {
      aux = aux->prox;
    }

  if(aux->prox != NULL){
      (aux->prox)->ant = novoFilme;
    }

    novoFilme->prox = aux->prox;
    novoFilme->ant = aux;
    aux->prox = novoFilme;

  }
}

Filme* containsFilme(Filme *filme, char nome[], int ano){

  while(filme != NULL && strcasecmp(filme->nome, nome) <= 0) {
    if(strcasecmp(filme->nome, nome) == 0 && filme->ano == ano){
      return filme;
    }
    filme = filme->prox;
  }
  return NULL;
}

char* removerFilme(Filme **inicio, Filme **fim, char nome[], int ano, Ator **inicioAtor, Ator **fimAtor,
   Diretor **inicioDiretor, Diretor **fimDiretor){

  Filme *aux = *inicio;

  while(aux != NULL && strcasecmp(aux->nome, nome) < 0){
    aux = aux->prox;
  }

  if(aux != NULL && strcasecmp(aux->nome, nome) == 0){
    if(aux->ant == NULL){
      *inicio = aux->prox;
    }
    else if(aux->prox == NULL){
      *fim = aux->ant;
    } else {
      (aux->ant)->prox = aux->prox;
      (aux->prox)->ant = aux->ant;
    }

    removerPointersAtorPorFilme(aux, inicioAtor, fimAtor);
    removerPointersDiretorPorFilme(aux, inicioDiretor, fimDiretor);

    free(aux);
    aux = NULL;

     return "\nFilme e dependentes removidos com sucesso!\n";
  }
  return "\nERRO: Filme não encontrado!\n";

}

void removerAtorDoFilme(Filme *filme, char ator[]){
  removerPointerAtor(&(filme->atores), ator);
}

void removerDiretorDoFilme(Filme *filme, char diretor[]){
  removerPointerDiretor(&(filme->diretores), diretor);
}

void inserirPointerFilme(pointerFilme **pointer, Filme *filme){
  pointerFilme *novoPointer = (pointerFilme*)malloc(sizeof(pointerFilme));
  novoPointer->filme = filme;
  novoPointer->prox = *pointer;
  novoPointer->personagens = NULL;
  *pointer = novoPointer;
}

Filme* containsPointerFilme(pointerFilme *filme, char nome[], int ano){

  while(filme != NULL) {
    if(strcasecmp((filme->filme)->nome, nome) == 0 && (filme->filme)->ano == ano){
      return filme->filme;
    }
    filme = filme->prox;
  }
  return NULL;
}

pointerFilme* buscaPointerFilme(pointerFilme *filme, char nome[], int ano){

  while(filme != NULL) {
    if(strcasecmp((filme->filme)->nome, nome) == 0 && (filme->filme)->ano == ano){
      return filme;
    }
    filme = filme->prox;
  }
  return NULL;
}

void removerPointerFilme(pointerFilme **inicio, Filme *filme){
  pointerFilme *aux = *inicio, *auxRemo = NULL;

  if(*inicio != NULL){
    if(strcasecmp(((*inicio)->filme)->nome, filme->nome) == 0 && ((*inicio)->filme)->ano == filme->ano){
      *inicio = (*inicio)->prox;
      free(aux);
      aux = NULL;

    } else {
      while(aux->prox != NULL && strcasecmp(((aux->prox)->filme)->nome, filme->nome) != 0 && ((aux->prox)->filme)->ano != filme->ano){
        aux = aux->prox;
      }

      if(aux->prox != NULL){
        auxRemo = aux->prox;
        aux->prox = (aux->prox)->prox;
        free(auxRemo);
        auxRemo = NULL;
      }

    }

  }
}

void removeAllPointerFilme(pointerFilme **pointer){
  if(*pointer != NULL){
    removeAllPointerFilme(&((*pointer)->prox));
    free(*pointer);
    *pointer = NULL;
  }
}

void insereListaFilme(Filme **inicioFilme, Filme **fimFilme, Filme *filme){
  Filme *filmeLista = (Filme*)malloc(sizeof(Filme)), *aux = *inicioFilme;
  int len = strlen(filme->nome);
  memcpy(filmeLista->nome, filme->nome, len);
  filmeLista->nome[len] = '\0';

  filmeLista->ano = filme->ano;
  filmeLista->atores = filme->atores;
  filmeLista->diretores = filme->diretores;

  filmeLista->ant = NULL;
  filmeLista->prox = NULL;

  if(*fimFilme == NULL){
    *inicioFilme = filmeLista;
    *fimFilme = *inicioFilme;
  }
  else if(filmeLista->ano == 0){
    filmeLista->ant = *fimFilme;
    (*fimFilme)->prox = filmeLista;
    *fimFilme = filmeLista;
  }
  else if(filmeLista->ano < (*inicioFilme)->ano){
    filmeLista->prox = *inicioFilme;
    (*inicioFilme)->ant = filmeLista;
    *inicioFilme = filmeLista;
  } else {
    while(aux->prox != NULL && filmeLista->ano > (aux->prox)->ano && (aux->prox)->ano != 0){
      aux = aux->prox;
    }

    filmeLista->prox = aux->prox;
    filmeLista->ant = aux;
    aux->prox = filmeLista;

    if(aux->prox != NULL){
      (aux->prox)->ant = filmeLista;
    } else {
      *fimFilme = filmeLista;
    }

  }
}

Filme* filmesOrdemCronologica(pointerFilme *filmes){
  Filme *inicioFilme = NULL, *fimFilme = NULL;

  while(filmes != NULL){
    insereListaFilme(&inicioFilme, &fimFilme, filmes->filme);
    filmes = filmes->prox;
  }
  return inicioFilme;
}

void removeListaFilme(Filme **filme){
  if(*filme != NULL){
    removeListaFilme(&((*filme)->prox));
    free(*filme);
    *filme = NULL;
  }
}

pointerFilme* buscaFilmesPorPersonagemDeAtor(char personagem[], Ator *ator){
  pointerFilme *aux = ator->filmes, *retorno = NULL;

  while(aux != NULL){
    if(containsPersonagem(aux->personagens, personagem) != NULL){
      inserirPointerFilme(&retorno, aux->filme);
    }
    aux = aux->prox;
  }

  return retorno;
}

/**
* Operações relacionadas a ator
*/

void inserirAtor(Ator **inicio, Ator **fim, Ator *novoAtor) {
  Ator *aux = *inicio;
  if(*fim == NULL) {
    *inicio = novoAtor;
    *fim = *inicio;
  }
  else if(strcasecmp(novoAtor->nome, (*inicio)->nome) <= 0) {
    novoAtor->prox = *inicio;

    (*inicio)->ant = novoAtor;
    *inicio = novoAtor;
  }
  else if(strcasecmp(novoAtor->nome, (*fim)->nome) >= 0) {
    novoAtor->ant = *fim;

    (*fim)->prox = novoAtor;
    *fim = novoAtor;
  } else {
    while(aux->prox != NULL && strcasecmp((aux->prox)->nome, novoAtor->nome) < 0) {
      aux = aux->prox;
    }

  if(aux->prox != NULL){
      (aux->prox)->ant = novoAtor;
    }

    novoAtor->prox = aux->prox;
    novoAtor->ant = aux;
    aux->prox = novoAtor;
  }
}

Ator* containsAtor(Ator *ator, char nome[]){

  while(ator != NULL && strcasecmp(ator->nome, nome) <= 0) {
    if(strcasecmp(ator->nome, nome) == 0){
      return ator;
    }
    ator = ator->prox;
  }
  return NULL;
}

void removerAtor(Ator **inicio, Ator **fim, char nome[]){
  Ator *aux = *inicio;

  while(aux != NULL && strcasecmp(aux->nome, nome) < 0){
    aux = aux->prox;
  }

  if(aux != NULL){

    if(aux->ant == NULL){
      *inicio = aux->prox;
    }
    else if(aux->prox == NULL){
      *fim = aux->ant;
    } else {
      (aux->ant)->prox = aux->prox;
      (aux->prox)->ant = aux->ant;
    }

    removerAtorDeFilme(aux);

    free(aux);
    aux = NULL;
  }
}

void inserirPointerAtor(pointerAtor **pointer, Ator *ator){
  pointerAtor *novoPointer = (pointerAtor*)malloc(sizeof(pointerAtor));
  novoPointer->ator = ator;
  novoPointer->prox = *pointer;
  *pointer = novoPointer;
}

Ator* containsPointerAtor(pointerAtor *ator, char nome[]){

  while(ator != NULL) {
    if(strcasecmp((ator->ator)->nome, nome) == 0){
      return ator->ator;
    }
    ator = ator->prox;
  }
  return NULL;
}

void removerPointersAtorPorFilme(Filme *filme, Ator **inicio, Ator **fim){
  pointerAtor *pointer = filme->atores, *aux = NULL;

  while(pointer != NULL){
    removerPointerFilme((&(pointer->ator)->filmes), filme);

    if((pointer->ator)->filmes == NULL){
      removerAtor(inicio, fim, (pointer->ator)->nome);
    }

    aux = pointer;
    pointer = pointer->prox;
    free(aux);
    aux = NULL;
  }
}

void removerAtorDeFilme(Ator *ator){
  pointerFilme *pointer = ator->filmes, *aux = NULL;
  while(pointer != NULL){
    removerAtorDoFilme(pointer->filme, ator->nome);
    removerPersonagens(pointer->personagens);
    aux = pointer;
    pointer = pointer->prox;
    free(aux);
    aux = NULL;
  }
}

void removerPointerAtor(pointerAtor **inicio, char ator[]){
  pointerAtor *aux = *inicio, *auxRemo = NULL;

  if(*inicio != NULL){
    if(strcasecmp((((*inicio)->ator)->nome), ator) == 0){
      *inicio = (*inicio)->prox;
      free(aux);
      aux = NULL;
    } else {
      while(aux->prox != NULL && strcasecmp((((aux->prox)->ator)->nome), ator) != 0){
        aux = aux->prox;
      }

      if(aux != NULL){
        auxRemo = aux->prox;
        aux->prox = (aux->prox)->prox;
        free(auxRemo);
        auxRemo = NULL;
      }

    }
  }
}

void removeAllPointerAtor(pointerAtor **pointer){
  if(*pointer != NULL){
    removeAllPointerAtor(&((*pointer)->prox));
    free(*pointer);
    *pointer = NULL;
  }
}

pointerFilme* buscaFilmesConjunto(Ator *ator, pointerFilme *filmesBusca){
  pointerFilme *retorno = NULL;

  while(filmesBusca != NULL){
    if(containsPointerAtor((filmesBusca->filme)->atores, ator->nome) != NULL){
      inserirPointerFilme(&retorno, filmesBusca->filme);
    }
    filmesBusca = filmesBusca->prox;
  }
  return retorno;
}

/**
* Operações relacionadas a diretor
*/

void inserirDiretor(Diretor **inicio, Diretor **fim, Diretor *novoDiretor) {
  Diretor *aux = *inicio;
  if(*fim == NULL) {
    (*inicio) = novoDiretor;
    (*fim) = *inicio;
  }
  else if(strcasecmp(novoDiretor->nome, (*inicio)->nome) <= 0) {
    novoDiretor->prox = *inicio;

    (*inicio)->ant = novoDiretor;
    *inicio = novoDiretor;
  }
  else if(strcasecmp(novoDiretor->nome, (*fim)->nome) >= 0) {
    novoDiretor->ant = *fim;

    (*fim)->prox = novoDiretor;
    (*fim) = novoDiretor;
  } else {

    while(aux->prox != NULL && strcasecmp((aux->prox)->nome, novoDiretor->nome) < 0) {
      aux = aux->prox;
    }

    if(aux->prox != NULL){
      (aux->prox)->ant = novoDiretor;
    }

    novoDiretor->prox = aux->prox;
    aux->prox = novoDiretor;

  }
}

Diretor* containsDiretor(Diretor *diretor, char nome[]){

  while(diretor != NULL && strcasecmp(diretor->nome, nome) <= 0) {

    if(strcasecmp(diretor->nome, nome) == 0){
      return diretor;
    }
    diretor = diretor->prox;
  }
  return NULL;
}

void removerDiretor(Diretor **inicio, Diretor **fim, char nome[]){
  Diretor *aux = *inicio;

  while(aux != NULL && strcasecmp(aux->nome, nome) < 0){
    aux = aux->prox;
  }

  if(aux != NULL){

    if(aux->ant == NULL){
      *inicio = aux->prox;
    }
    else if(aux->prox == NULL){
      *fim = aux->ant;
    } else {
      (aux->ant)->prox = aux->prox;
      (aux->prox)->ant = aux->ant;
    }

    removerDiretorDeFilme(aux);

    free(aux);
    aux = NULL;
  }
}

void inserirPointerDiretor(pointerDiretor **pointer, Diretor *diretor){
  pointerDiretor *novoPointer = (pointerDiretor*)malloc(sizeof(pointerDiretor));
  novoPointer->diretor = diretor;
  novoPointer->prox = *pointer;
  *pointer = novoPointer;
}

Diretor* containsPointerDiretor(pointerDiretor *diretor, char nome[]){

  while(diretor != NULL) {
    if(strcasecmp((diretor->diretor)->nome, nome) == 0){
      return diretor->diretor;
    }
    diretor = diretor->prox;
  }
  return NULL;
}

void removerPointersDiretorPorFilme(Filme *filme, Diretor **inicio, Diretor **fim){
  pointerDiretor *pointer = filme->diretores, *aux = NULL;

  while(pointer != NULL){
    removerPointerFilme(&(pointer->diretor)->filmes, filme);

    if((pointer->diretor)->filmes == NULL){
      removerDiretor(inicio, fim, (pointer->diretor)->nome);
    }

    aux = pointer;
    pointer = pointer->prox;
    free(aux);
    aux = NULL;
  }
}

void removerDiretorDeFilme(Diretor *diretor){
  pointerFilme *pointer = diretor->filmes, *aux = NULL;
  while(pointer != NULL){
    removerDiretorDoFilme(pointer->filme, diretor->nome);

    aux = pointer;
    pointer = pointer->prox;
    free(aux);
    aux = NULL;
  }
}

void removerPointerDiretor(pointerDiretor **inicio, char diretor[]){
  pointerDiretor *aux = *inicio, *auxRemo = NULL;

  if(*inicio != NULL){
    if(strcasecmp((((*inicio)->diretor)->nome), diretor) == 0){
      *inicio = (*inicio)->prox;
      free(aux);
      aux = NULL;
    } else {
      while(aux != NULL && strcasecmp((((aux->prox)->diretor)->nome), diretor) != 0){
        aux = aux->prox;
      }

      if(aux != NULL){
        auxRemo = aux->prox;
        aux->prox = (aux->prox)->prox;
        free(auxRemo);
        auxRemo = NULL;
      }

    }
  }
}

pointerFilme* buscaFilmesConjuntoDiretor(Diretor *diretor, pointerFilme *filmesBusca){
  pointerFilme *retorno = NULL;

  while(filmesBusca != NULL){
    if(containsPointerDiretor((filmesBusca->filme)->diretores, diretor->nome) != NULL){
      inserirPointerFilme(&retorno, filmesBusca->filme);
    }
    filmesBusca = filmesBusca->prox;
  }
  return retorno;
}

/**
* Operações relacionadas a personagem
*/

void inserirPersonagem(Personagem **inicio, Personagem *novoPersonagem) {
  if(*inicio == NULL) {
    (*inicio) = novoPersonagem;
  } else {
    novoPersonagem->prox = *inicio;
    *inicio = novoPersonagem;
  }
}

Personagem* containsPersonagem(Personagem *personagem, char nome[]){

  while(personagem != NULL && strcasecmp(personagem->nome, nome) <= 0) {
    if(strcasecmp(personagem->nome, nome) == 0){
      return personagem;
    }
    personagem = personagem->prox;
  }
  return NULL;
}

void removerPersonagem(Personagem **inicio, char nome[]){
  Personagem *aux = *inicio, *auxRemo = NULL;

  if(*inicio != NULL){
    if(strcasecmp(((*inicio)->nome), nome) == 0){
      *inicio = (*inicio)->prox;
      free(aux);
      aux = NULL;
    } else {
      while(aux != NULL && strcasecmp((aux->nome), nome) != 0){
        aux = aux->prox;
      }

      if(aux != NULL){
        auxRemo = aux;
        aux = aux->prox;
        free(auxRemo);
        auxRemo = NULL;
      }
    }
  }
}

void removerPersonagens(Personagem *personagem){
  if(personagem != NULL){
    removerPersonagens(personagem->prox);
    free(personagem);
    personagem = NULL;
  }
}
