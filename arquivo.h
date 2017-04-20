Filme* insereFilme(Filme **inicioFilme, Filme **fimFilme, char nomeFilme[], int *anoFilme){
  Filme *filme = containsFilme(*inicioFilme, nomeFilme, *anoFilme);

  if(filme != NULL){
    filme->cont = filme->cont + 1;
  } else {
    filme = (Filme*)malloc(sizeof(Filme));
    strcpy(filme->nome, nomeFilme);
    filme->ano = *anoFilme;
    filme->cont = 1;
    filme->atores = NULL;
    filme->diretores = NULL;
    filme->prox = NULL;
    filme->ant = NULL;

    strcpy(nomeFilme, "");
    *anoFilme = 0;

    inserirFilme(inicioFilme, fimFilme, filme);
  }
    return filme;
}

void insereDiretor(Diretor **inicioDiretor, Diretor **fimDiretor, char nomeDiretor[], Filme *filme){
  Diretor *diretor = containsDiretor(*inicioDiretor, nomeDiretor);

  if(diretor == NULL){
    diretor = (Diretor*)malloc(sizeof(Diretor));
    strcpy(diretor->nome,nomeDiretor);
    diretor->filmes = NULL;
    diretor->prox = NULL;
    diretor->ant = NULL;
    inserirDiretor(inicioDiretor, fimDiretor, diretor);
  }

  if(containsPointerFilme(diretor->filmes, filme->nome, filme->ano) == NULL){
    inserirPointerFilme(&(diretor->filmes), filme);
  }
  if(containsPointerDiretor(filme->diretores, diretor->nome) == NULL){
    inserirPointerDiretor(&(filme->diretores), diretor);
  }

}

int isDiretor(char nome[]){
  int len = strlen(nome);
  char aux[len];

  if(len > 4){
    strncpy(aux, nome, 4);
    if(strcasecmp(aux, "dir:") == 0){
      memcpy(nome, &nome[4], len);
      nome[len] = '\0';
      return 1;
    }
  }
  return 0;
}

int findChar(char string[]){
  int len = strlen(string);

  for(int i = 0; i < len; i++){
    if(string[i] == '='){
      return i;
    }
  }
  return len;
}

void getNomeAtor(char nomeAtor[], char nome[]){
  int index = findChar(nome);
  memcpy(nomeAtor, &nome[0], index);
  nomeAtor[index] = '\0';
}

void getNomePersonagem(char nomePersonagem[], char nome[]){
  int index = strlen(nome), chr = findChar(nome);

  if(chr < index){
    memcpy(nomePersonagem, &nome[chr + 1], index);
    nomePersonagem[index] = '\0';
  }

}

void insereAtor(Ator **inicioAtor, Ator **fimAtor, Filme *filme, char nome[]){
  Ator *ator = NULL;
  Personagem *personagem;
  pointerFilme *ptFilme = NULL;
  char nomeAtor[strlen(nome)], nomePersonagem[strlen(nome)];
  int len;
  getNomeAtor(nomeAtor, nome);
  getNomePersonagem(nomePersonagem, nome);

  ator = containsAtor(*inicioAtor, nomeAtor);
  len = strlen(nomeAtor);
  if(ator == NULL){
    ator = (Ator*)malloc(sizeof(Ator));
    memcpy(ator->nome,nomeAtor, len);
    ator->nome[len] = '\0';
    ator->filmes = NULL;
    ator->prox = NULL;
    ator->ant = NULL;

    inserirAtor(inicioAtor, fimAtor, ator);
  }

  if(buscaPointerFilme(ator->filmes, filme->nome, filme->ano) == NULL){
    inserirPointerFilme(&(ator->filmes), filme);
  }

  if(containsPointerAtor(filme->atores, ator->nome) == NULL){
    inserirPointerAtor(&(filme->atores), ator);
  }

  ptFilme = buscaPointerFilme(ator->filmes, filme->nome, filme->ano);

  if(nomePersonagem != NULL && strlen(nomePersonagem) > 0 && containsPersonagem(ptFilme->personagens, nomePersonagem) == NULL){
    personagem = (Personagem*)malloc(sizeof(Personagem));
    len = strlen(nomePersonagem);
    memcpy(personagem->nome, nomePersonagem, len);
    personagem->nome[len] = '\0';
    personagem->prox = NULL;

    inserirPersonagem(&(ptFilme->personagens), personagem);
  }

}

void readFile(char path[], Filme **inicioFilme, Filme **fimFilme, Ator **inicioAtor, Ator **fimAtor,
  Diretor **inicioDiretor, Diretor **fimDiretor){

  FILE *acervoFilmes;
  char dadoEntrada[10000], *token, nomeFilme[301];
  int anoFilme = 0;
  const char s[2] = ",";
  int virgula;
  Filme *filme = NULL;

  if((acervoFilmes = fopen(path, "rt")) != NULL){
    while(fgets(dadoEntrada, 9999, acervoFilmes)) {
      if(dadoEntrada[strlen(dadoEntrada) -1] == '\n'){
        dadoEntrada[strlen(dadoEntrada) - 1] = '\0';
      }
      if(dadoEntrada[strlen(dadoEntrada) -1] == '\r'){
        dadoEntrada[strlen(dadoEntrada) - 1] = '\0';
      }
      //dadoEntrada[strlen(dadoEntrada) - 2] = '\0';
      virgula = 0;

      token = strtok(dadoEntrada, s);
      while(token != NULL){

        switch (virgula) {
          case 0:
            strcpy(nomeFilme, token);
            virgula++;
            break;
          case 1:
            if(token !=  NULL){
              anoFilme = atoi(token);
            }
            filme = insereFilme(inicioFilme, fimFilme,nomeFilme, &anoFilme);
            virgula++;
            break;
          case 2:
            if(token != NULL){
              insereDiretor(inicioDiretor, fimDiretor, token, filme);
            }
            virgula++;
            break;
          default:
            if(token != NULL){
              if(isDiretor(token)){
                insereDiretor(inicioDiretor, fimDiretor, token, filme);
              } else {
                insereAtor(inicioAtor, fimAtor, filme, token);
              }
            }
            break;
        }

        token = strtok(NULL, s);
      }
    }
    fclose(acervoFilmes);
    printf("\nArquivo importado com sucesso!\n");
  } else {
    printf("\nErro na leitura do arquivo: %s\n", path);
  }
}

void exportData(char path[], Filme *inicio){
  pointerDiretor *diretores = NULL;
  pointerAtor *atores = NULL;
  pointerFilme *filme = NULL;
  Personagem *personagens = NULL;
  FILE *outputFile = NULL;

  if((outputFile = fopen(path, "wt")) != NULL){

    while(inicio != NULL) {
      diretores = inicio->diretores;
      atores = inicio->atores;

      if(inicio->ano != 0) {
        fprintf(outputFile, "%s,%d,", inicio->nome, inicio->ano);
      } else {
        fprintf(outputFile, "%s,,", inicio->nome);
      }

      if(diretores != NULL) {
        fprintf(outputFile, "%s", (diretores->diretor)->nome);
        diretores = diretores->prox;

        while(diretores != NULL){
          fprintf(outputFile, ",dir:%s", (diretores->diretor)->nome);
          diretores = diretores->prox;
        }
      }

      while(atores != NULL){
        filme = buscaPointerFilme((atores->ator)->filmes, inicio->nome, inicio->ano);

        if(filme != NULL){
          personagens = filme->personagens;
        }

        if(personagens != NULL){
          while(personagens != NULL){
              fprintf(outputFile, ",%s=%s", (atores->ator)->nome, personagens->nome);
              personagens = personagens->prox;
          }
        } else {
            fprintf(outputFile, ",%s", (atores->ator)->nome);
        }

        atores = atores->prox;
      }
      fprintf(outputFile, "\n");
      inicio = inicio->prox;
    }
    fclose(outputFile);
    printf("\nArquivo exportado com sucesso para: %s\n",path);
  } else {
    printf("\nFalha na exportação dos dados, verifique o endereço e tente novamente!\n");
  }
}
