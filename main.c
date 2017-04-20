#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>
#include "structs.h"
#include "operations.h"
#include "arquivo.h"

int leInt(){
  int inteiro = 0;
  fflush(stdin);
  scanf("%d", &inteiro);
  return inteiro;
}

void leString(char string[]){
  fflush(stdin);
  scanf(" %149[^\n]", string);
}

void importarArquivo(char path[], Filme **inicioFilme, Filme **fimFilme, Ator **inicioAtor, Ator **fimAtor, Diretor **inicioDiretor, Diretor **fimDiretor){
  printf("Digite o diretório completo do arquivo:\n");
  leString(path);
  readFile(path, inicioFilme, fimFilme, inicioAtor, fimAtor, inicioDiretor, fimDiretor);
}

void exportarArquivo(Filme *inicio){
  char path[150];
  printf("\nATENÇÃO itens duplicados serão exportados como um único registro.\nInforme o arquivo para exportação dos dados:\n");
  leString(path);
  exportData(path, inicio);
}

void listarAtoresCrescente(Ator *ator){
  if(ator != NULL){
    printf("%s\n", ator->nome);
    listarAtoresCrescente(ator->prox);
  }
}

void listarAtoresDecrescente(Ator *ator){
  if(ator != NULL){
    printf("%s\n", ator->nome);
    listarAtoresDecrescente(ator->ant);
  }
}

void listarFilmesCrescente(Filme *filme){
  if(filme != NULL){
    printf("%s - %d\n", filme->nome, filme->ano);
    listarFilmesCrescente(filme->prox);
  }
}

void listarFilmesDecrescente(Filme *filme){
  if(filme != NULL){
    printf("%s - %d\n", filme->nome, filme->ano);
    listarFilmesDecrescente(filme->ant);
  }
}

void listarFilmesPorAtor(Ator *ator){
  Filme *filme = NULL, *auxRemo = NULL;

  if(ator != NULL){
    filme = filmesOrdemCronologica(ator->filmes);
  } else {
    printf("\nERRO: ator não cadastrado\n");
  }
  auxRemo = filme;
  while(filme != NULL){
    printf("%s - %d\n", filme->nome, filme->ano);
    filme = filme->prox;
  }

  removeListaFilme(&auxRemo);
}

void buscaDadosFilmePorAtor(Ator *inicio){
  char nomeAtor[300];
  printf("Digite o nome do ator:\n");
  leString(nomeAtor);
  listarFilmesPorAtor(containsAtor(inicio, nomeAtor));
}

void inserirDiretorEmFilme(Filme *filme, Diretor **inicioDiretor, Diretor **fimDiretor){
  Diretor *novoDiretor = NULL;
  char nomeDiretor[301];
  int len;

  printf("Insira o nome do diretor que deve ser inserido, caso não queira adicionar mais diretores digite 'end':\n");
  leString(nomeDiretor);
  while(strcasecmp(nomeDiretor, "end") != 0){

    if(containsPointerDiretor(filme->diretores, nomeDiretor) == NULL){

      novoDiretor = containsDiretor(*inicioDiretor, nomeDiretor);

      if(novoDiretor == NULL){
        novoDiretor = (Diretor*)malloc(sizeof(Diretor));

        len = strlen(nomeDiretor);

        memcpy(novoDiretor->nome, nomeDiretor, len);
        novoDiretor->nome[len] = '\0';

        novoDiretor->filmes = NULL;
        novoDiretor->prox = NULL;
        novoDiretor->ant = NULL;

        inserirDiretor(inicioDiretor, fimDiretor, novoDiretor);
      }

      inserirPointerFilme(&(novoDiretor->filmes), filme);
      inserirPointerDiretor(&(filme->diretores), novoDiretor);
    }else{
      printf("\nEste filme já contem este diretor.\n");
    }
    printf("\nInsira o nome do diretor que deve ser inserido, caso não queira adicionar mais diretores digite 'end':\n");
    leString(nomeDiretor);
  }
}

void inserirPersonagemEmAtor(pointerFilme *ptFilme){
  Personagem *novoPersonagem = NULL;
  char nomePersonagem[301];
  int len;

  printf("\nInsira o nome do personagem que deve ser inserido, caso não queira adicionar mais personagens digite 'end':\n");
  leString(nomePersonagem);
  while(strcasecmp(nomePersonagem, "end") != 0){

    novoPersonagem = containsPersonagem(ptFilme->personagens, nomePersonagem);

    if(novoPersonagem == NULL){
      novoPersonagem = (Personagem*)malloc(sizeof(Personagem));

      len = strlen(nomePersonagem);

      memcpy(novoPersonagem->nome, nomePersonagem, len);
      novoPersonagem->nome[len] = '\0';

      novoPersonagem->prox = NULL;

      inserirPersonagem(&(ptFilme->personagens), novoPersonagem);
    } else {
      printf("\nEste filme já contem este personagem.\n");
    }
    printf("\nInsira o nome do personagem que deve ser inserido, caso não queira adicionar mais personagens digite 'end':\n");
    leString(nomePersonagem);
  }
}

void inserirAtorEmFilme(Filme *filme, Ator **inicioAtor, Ator **fimAtor){
  Ator *novoAtor = NULL;
  char nomeAtor[301];
  int len;

  printf("Insira o nome do ator que deve ser inserido, caso não queira adicionar mais atores digite 'end':\n");
  leString(nomeAtor);
  while(strcasecmp(nomeAtor, "end") != 0){

    if(containsPointerAtor(filme->atores, nomeAtor) == NULL){

      novoAtor = containsAtor(*inicioAtor, nomeAtor);

      if(novoAtor == NULL){
        novoAtor = (Ator*)malloc(sizeof(Ator));

        len = strlen(nomeAtor);

        memcpy(novoAtor->nome, nomeAtor, len);
        novoAtor->nome[len] = '\0';

        novoAtor->filmes = NULL;
        novoAtor->prox = NULL;
        novoAtor->ant = NULL;

        inserirAtor(inicioAtor, fimAtor, novoAtor);
      }

      inserirPointerFilme(&(novoAtor->filmes), filme);

      inserirPersonagemEmAtor(buscaPointerFilme(novoAtor->filmes, filme->nome, filme->ano));

      inserirPointerAtor(&(filme->atores), novoAtor);
    }else{
      printf("\nEste filme já contem este ator.\n");
    }
    printf("Insira o nome do ator que deve ser inserido, caso não queira adicionar mais atores digite 'end':\n");
    leString(nomeAtor);
  }
}

void inserirNovoFilme(Filme **inicioFilme, Filme **fimFilme, Ator **inicioAtor, Ator **fimAtor, Diretor **inicioDiretor, Diretor **fimDiretor){
  Filme *novoFilme = NULL;
  char nomeFilme[301];
  int anoFilme = 0, len;

  printf("Insira o nome do filme:\n");
  leString(nomeFilme);

  printf("Insira o ano do filme, ou para filmes com ano desconhecido, digite 0:\n");
  anoFilme = leInt();

  novoFilme = containsFilme(*inicioFilme, nomeFilme, anoFilme);

  if(novoFilme == NULL){

    novoFilme = (Filme*)malloc(sizeof(Filme));

    len = strlen(nomeFilme);

    memcpy(novoFilme->nome, nomeFilme, len);
    novoFilme->nome[len] = '\0';
    novoFilme->ano = anoFilme;

    novoFilme->atores = NULL;
    novoFilme->diretores = NULL;
    novoFilme->prox = NULL;
    novoFilme->ant = NULL;

    inserirFilme(inicioFilme, fimFilme, novoFilme);
    inserirDiretorEmFilme(novoFilme, inicioDiretor, fimDiretor);
    inserirAtorEmFilme(novoFilme, inicioAtor, fimAtor);

    printf("\nFilme inserido com sucesso!\n");

  } else {
    printf("\nERRO: Este filme já está cadastrado\n");
  }
}

void buscaDadosRemoverFilme(Filme **inicioFilme, Filme **fimFilme, Ator **inicioAtor, Ator **fimAtor,  Diretor **inicioDiretor, Diretor **fimDiretor){
  char nomeFilme[301];
  int anoFilme = 0;

  printf("Insira o nome do filme:\n");
  leString(nomeFilme);

  printf("Insira o ano do filme, ou para filmes com ano desconhecido, digite 0:\n");
  anoFilme = leInt();

  printf("%s", removerFilme(inicioFilme, fimFilme, nomeFilme, anoFilme, inicioAtor, fimAtor, inicioDiretor, fimDiretor));
}

void listarFilmesPorDiretor(Diretor *diretor){
  Filme *filme = NULL, *auxRemo = NULL;

  if(diretor != NULL){
    filme = filmesOrdemCronologica(diretor->filmes);
  } else {
    printf("\nERRO: diretor não cadastrado!\n");
  }

  auxRemo = filme;
  while(filme != NULL){
    printf("%s - %d\n", filme->nome, filme->ano);
    filme = filme->prox;
  }

  removeListaFilme(&auxRemo);
}

void buscaDadosFilmePorDiretor(Diretor *inicio){
  char nomeDiretor[300];
  printf("Digite o nome do diretor:\n");
  leString(nomeDiretor);
  listarFilmesPorDiretor(containsDiretor(inicio, nomeDiretor));
}

void atoresQueTrabalharamComDeterminadoAtor(Ator *ator){
  pointerAtor *atoresJaExibidos = NULL, *atores = NULL;
  pointerFilme *filmes = NULL, *filmesConjunto = NULL, *aux = NULL;

  if(ator != NULL){
    filmes = ator->filmes;

    while(filmes != NULL){
      atores = (filmes->filme)->atores;
      while(atores != NULL){
        if(containsPointerAtor(atoresJaExibidos, (atores->ator)->nome) == NULL && strcasecmp((atores->ator)->nome, ator->nome) != 0){

          filmesConjunto = buscaFilmesConjunto(ator, (atores->ator)->filmes);

          if(filmesConjunto != NULL){
            printf("Ator %s: %s - %d", (atores->ator)->nome, (filmesConjunto->filme)->nome, (filmesConjunto->filme)->ano);
            aux = filmesConjunto->prox;

            while(aux != NULL){
              printf(", %s - %d", (aux->filme)->nome, (aux->filme)->ano);
              aux = aux->prox;
            }

            printf("\n");

            removeAllPointerFilme(&filmesConjunto);
          }

          inserirPointerAtor(&atoresJaExibidos, atores->ator);
        }

        atores = atores->prox;
      }

      filmes = filmes->prox;
    }
    removeAllPointerAtor(&atoresJaExibidos);
  } else {
    printf("\nERRO: Ator não encontrado\n");
  }
}

void buscaFilmesConjuntoAtor(Ator *inicio){
  char nomeAtor[300];
  printf("Digite o nome do ator:\n");
  leString(nomeAtor);
  atoresQueTrabalharamComDeterminadoAtor(containsAtor(inicio, nomeAtor));
}

void atoresQueTrabalharamComDeterminadoDiretor(Diretor *diretor){
  pointerAtor *atoresJaExibidos = NULL, *atores = NULL;
  pointerFilme *filmes = NULL, *filmesConjunto = NULL, *aux = NULL;

  if(diretor != NULL){
    filmes = diretor->filmes;

    while(filmes != NULL){
      atores = (filmes->filme)->atores;
      while(atores != NULL){
        if(containsPointerAtor(atoresJaExibidos, (atores->ator)->nome) == NULL){

          filmesConjunto = buscaFilmesConjuntoDiretor(diretor, (atores->ator)->filmes);

          if(filmesConjunto != NULL){
            printf("Ator %s: %s - %d", (atores->ator)->nome, (filmesConjunto->filme)->nome, (filmesConjunto->filme)->ano);
            aux = filmesConjunto->prox;

            while(aux != NULL){
              printf(", %s - %d", (aux->filme)->nome, (aux->filme)->ano);
              aux = aux->prox;
            }

            printf("\n");

            removeAllPointerFilme(&filmesConjunto);
          }

          inserirPointerAtor(&atoresJaExibidos, atores->ator);
        }

        atores = atores->prox;
      }

      filmes = filmes->prox;
    }
    removeAllPointerAtor(&atoresJaExibidos);
  } else {
    printf("\nERRO: Diretor não encontrado\n");
  }
}

void buscaDadosFilmesConjuntoDiretor(Diretor *inicio){
  char nomeDiretor[300];
  printf("Digite o nome do diretor:\n");
  leString(nomeDiretor);
  atoresQueTrabalharamComDeterminadoDiretor(containsDiretor(inicio, nomeDiretor));
}

void listarFilmesDuplicados(Filme *inicio){
  int flag = 0;
  while(inicio != NULL){
    if(inicio->cont > 1) {
      printf("Filme: %s - %d. Quantidade: %d\n", inicio->nome, inicio->ano, inicio->cont);
      flag = 1;
    }
    inicio = inicio->prox;
  }

  if(!flag){
    printf("\nNenhum registro duplicado foi encontrado\n");
  }
}

void listarPorPersonagem(char personagem[], Ator *inicio){
  pointerFilme *filmes = NULL, *aux = NULL;
  int flag = 0;

  while(inicio != NULL){
    if(personagem != NULL && inicio != NULL){
      filmes = buscaFilmesPorPersonagemDeAtor(personagem, inicio);

      if(filmes != NULL){
        printf("Ator %s: %s - %d", inicio->nome, (filmes->filme)->nome, (filmes->filme)->ano);
        aux = filmes->prox;

        while(aux != NULL){
          printf(", %s - %d", (aux->filme)->nome, (aux->filme)->ano);
          aux = aux->prox;
        }

        printf("\n");

        removeAllPointerFilme(&filmes);

        flag = 1;
      }
    }
    inicio = inicio->prox;
  }
  if(!flag){
    printf("\nNenhum registro foi encontrado!\n");
  }
}

void buscaAtoresPersonagem(Ator *inicioAtor){
  char personagem[300];
  printf("Digite o nome do personagem:\n");
  leString(personagem);
  listarPorPersonagem(personagem, inicioAtor);
}

int menu(){
  int opc = 0;

  printf("\nSelecione a opção desejada.\n1 - Importar dados de arquivo.\n2 - Listar todos atores em ordem alfabética.\n3 - Listar todos atores em ordem alfabética reversa.\n4 - Listar filmes de um determinado ator em ordem cronologica.\n5 - Listar todos os filmes em ordem alfabética.\n6 - Listar todos os filmes em ordem alfabética reversa.\n7 - Inserir novo filme.\n8 - Remover filme.\n9 - Listar filmes de um determinado diretor em ordem cronologica.\n10 - Listar todos atores que trabalharam diretamente com determinado ator.\n11 - Listar todos atores que trabalharam diretamente com determinado diretor.\n12 - Listar todos os filmes duplicados.\n13 - Listar todos os atores que interpretaram um dado personagem.\n14 - Exportar dados.\n0 - Sair.\n");
  opc = leInt();

  return opc;
}

void executaOperacao(char path[], Filme **inicioFilme, Filme **fimFilme, Ator **inicioAtor, Ator **fimAtor,  Diretor **inicioDiretor, Diretor **fimDiretor, int opc){

  switch(opc){
    case 0:
      break;
    case 1:
      importarArquivo(path, inicioFilme, fimFilme, inicioAtor, fimAtor, inicioDiretor, fimDiretor);
      break;
    case 2:
      listarAtoresCrescente(*inicioAtor);
      break;
    case 3:
      listarAtoresDecrescente(*fimAtor);
      break;
    case 4:
      buscaDadosFilmePorAtor(*inicioAtor);
      break;
    case 5:
      listarFilmesCrescente(*inicioFilme);
      break;
    case 6:
      listarFilmesDecrescente(*fimFilme);
      break;
    case 7:
      inserirNovoFilme(inicioFilme, fimFilme, inicioAtor, fimAtor, inicioDiretor, fimDiretor);
      break;
    case 8:
      buscaDadosRemoverFilme(inicioFilme, fimFilme, inicioAtor, fimAtor, inicioDiretor, fimDiretor);
      break;
    case 9:
      buscaDadosFilmePorDiretor(*inicioDiretor);
      break;
    case 10:
      buscaFilmesConjuntoAtor(*inicioAtor);
      break;
    case 11:
      buscaDadosFilmesConjuntoDiretor(*inicioDiretor);
      break;
    case 12:
      listarFilmesDuplicados(*inicioFilme);
      break;
    case 13:
      buscaAtoresPersonagem(*inicioAtor);
      break;
    case 14:
      exportarArquivo(*inicioFilme);
      break;
    default:
      printf("\nOperação inválida\n");
  }

}

int main(){
  setlocale(LC_ALL, "");
  char path[150];// = {"/media/files/disco F/trabalhos/Universidade de Caxias do Sul/Programacao 2/Trabalho/resumo.txt"};
  Filme *inicioFilme = NULL, *fimFilme = NULL;
  Ator *inicioAtor = NULL, *fimAtor = NULL;
  Diretor *inicioDiretor = NULL, *fimDiretor = NULL;
  int opc = menu();



  while(opc != 0) {
    executaOperacao(path, &inicioFilme, &fimFilme, &inicioAtor, &fimAtor, &inicioDiretor, &fimDiretor, opc);
    opc = menu();
  }
}
