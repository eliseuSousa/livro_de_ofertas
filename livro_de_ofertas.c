#include <stdio.h>
#include <stdlib.h>

// Implementando a estrutura de dados
// lista encadeada
typedef struct Produto {
  double valor;
  int quantidade;
  struct Produto *proximo;
} Produto;

typedef struct 
{
  struct Produto *inicio;
  int tamanho;
} LivroDeOfertas;

void inicializarLivroDeOfertas(LivroDeOfertas *livroDeOfertas) {
  livroDeOfertas->inicio = NULL;
  livroDeOfertas->tamanho = 0;
}

void inserirInicio(LivroDeOfertas *livroDeOfertas, double valor, int quantidade) {
  Produto *novoProduto = (Produto *) malloc(sizeof(Produto));
  novoProduto->proximo = livroDeOfertas->inicio;
  novoProduto->valor = valor;
  novoProduto->quantidade = quantidade;
  livroDeOfertas->inicio = novoProduto;
  livroDeOfertas->tamanho++;
}

void inserirFim(LivroDeOfertas *livroDeOfertas, double valor, int quantidade) {
  Produto *produtoAtual,*novoProduto = (Produto *)malloc(sizeof(Produto));

  if(livroDeOfertas->tamanho == 1) {
    inserirInicio(livroDeOfertas, valor, quantidade);
  } else {

    novoProduto->proximo = NULL;
    novoProduto->valor = valor;
    novoProduto->quantidade = quantidade;
    produtoAtual = livroDeOfertas->inicio;

    while(produtoAtual->proximo != NULL) {
      produtoAtual = produtoAtual->proximo;
    }

    produtoAtual->proximo = novoProduto;
    livroDeOfertas->tamanho++;
  }
}

void inserir(LivroDeOfertas *livroDeOfertas, int posicao, double valor, int quantidade) {
  Produto *produtoAtual, *novoProduto = (Produto *)malloc(sizeof(Produto));

  int count = 1;
  if(posicao == 1) {
    inserirInicio(livroDeOfertas, valor, quantidade);
  } else if (posicao == livroDeOfertas->tamanho) {
    inserirFim(livroDeOfertas, valor, quantidade);
  } else if (posicao > livroDeOfertas->tamanho) {
    printf("%d está fora dos limites da lista que tem tamanho %d \n", posicao, livroDeOfertas->tamanho);
    printf("Operação: %i,0,%.2f,%i foi rejeitada \n", posicao, valor, quantidade);
  } else {
    produtoAtual = livroDeOfertas->inicio;
    while(count < (posicao - 1)) {
      produtoAtual = produtoAtual->proximo;
      count++;
    }
    novoProduto->proximo = produtoAtual->proximo;
    produtoAtual->proximo = novoProduto;
    novoProduto->valor = valor;
    novoProduto->quantidade = quantidade;
    livroDeOfertas->tamanho++;
  }
}

void modificar(LivroDeOfertas *livroDeOfertas, int posicao, double valor, int quantidade) {

  Produto *produto = livroDeOfertas->inicio;
  
  int count = 1;
  if(posicao > livroDeOfertas->tamanho) {
    printf("%d está fora dos limites da lista que tem tamanho %d \n", posicao, livroDeOfertas->tamanho);
    printf("Operação: %i,0,%.2f,%i foi rejeitada\n", posicao, valor, quantidade);
  } else {
    while(count != posicao) {
      produto = produto->proximo;
      count++;  
    }
    produto->valor = valor;
    produto->quantidade = quantidade;
  }
}

void removerInicio(LivroDeOfertas *livroDeOfertas) {
  Produto *produtoAlvo = (Produto *)malloc(sizeof(Produto));
  produtoAlvo = livroDeOfertas->inicio;

  if(livroDeOfertas->tamanho == 1) {
    livroDeOfertas->inicio = NULL;
  } else {
    livroDeOfertas->inicio = produtoAlvo->proximo;
  }

  free(produtoAlvo);
  livroDeOfertas->tamanho--;
}

void removerFinal(LivroDeOfertas *livroDeOfertas) {

  int count = 1;
  Produto *produtoAtual, *produtoAlvo = (Produto *) malloc(sizeof(produtoAlvo));
  if (livroDeOfertas->tamanho == 1) {
    removerInicio(livroDeOfertas);
  } else {
    produtoAlvo = livroDeOfertas->inicio;

    while(count < (livroDeOfertas->tamanho - 1)) {
      produtoAlvo = produtoAlvo->proximo;
      count++;
    }

    produtoAlvo = produtoAtual->proximo;
    produtoAtual->proximo = NULL;
    free(produtoAlvo);
    livroDeOfertas->tamanho--;
  }

}

void remover(LivroDeOfertas *livroDeOfertas, int posicao) {
  int count = 1;
  Produto *produtoAtual, *produtoAlvo = (Produto *) malloc(sizeof(Produto));

  produtoAtual = livroDeOfertas->inicio;

  if(posicao == 1) {
    removerInicio(livroDeOfertas);
  } else if (posicao == livroDeOfertas->tamanho) {
    removerFinal(livroDeOfertas);
  } else if (posicao > livroDeOfertas->tamanho) {
    printf("%d está fora dos limites da lista que tem tamanho %d \n", posicao, livroDeOfertas->tamanho);
    printf("Operação: %i,0,0,0 foi rejeitada\n", posicao);
  }
  else {
    while(count < (posicao - 1)) {
      produtoAtual = produtoAtual->proximo;
      count++;
    }
    produtoAlvo = produtoAtual->proximo;
    produtoAtual->proximo = produtoAlvo->proximo;
    free(produtoAlvo);
    livroDeOfertas->tamanho--;
  }
}

// Imprimindo o livro de ofertas
void imprimirLivroDeOfertas(LivroDeOfertas *livroDeOfertas) {
  int i = 1;
  Produto *produtoAtual = livroDeOfertas->inicio;

  printf("\nLivro de Ofertas:\n");
  while(produtoAtual != NULL) {
    printf("%i,%.2f,%i\n", i, produtoAtual->valor, produtoAtual->quantidade);
    produtoAtual = produtoAtual->proximo;
    i++;
  }
  printf("\n");
}

// Pegando as informações passadas pelo usuário
int getPosicao(char *parametros, int *ponteiro) {
   char buffer[5];
   int posicao, i;

   i = 0;
   while(parametros[*ponteiro] != ',') {
      buffer[i] = parametros[*ponteiro];
      (*ponteiro)++;
      i++;
   }
   buffer[i] = '\0';
   posicao = atoi(buffer);
   
   return posicao;
}

int getAcao(char *parametros, int *ponteiro) {
   char buffer[5];
   int acao, i;

   i = 0;
   (*ponteiro)++;
   while(parametros[*ponteiro] != ',') {
      buffer[i] = parametros[*ponteiro];
      (*ponteiro)++;
      i++;
   }
   buffer[i] = '\0';
   acao = atoi(buffer);

   return acao;
}

double getValor(char *parametros, int *ponteiro) {
   char buffer[5];
   double valor;
   int i = 0;

   (*ponteiro)++;
   while(parametros[*ponteiro] != ',') {
      buffer[i] = parametros[*ponteiro];
      (*ponteiro)++;
      i++;
   }
   buffer[i] = '\0';
   valor = atof(buffer);
   
   return valor;
}

int getQuantidade(char *parametros, int *ponteiro) {
   char buffer[5];
   int quantidade, i;

   (*ponteiro)++;
   i = 0;
   while(parametros[*ponteiro] != '\0') {
      buffer[i] = parametros[*ponteiro];
      (*ponteiro)++;
      i++;
   }
   buffer[i] = '\0';
   quantidade = atoi(buffer);

   return quantidade;
}

int main() {

   LivroDeOfertas livroDeOfertas;
   int numDeNotificacoes;
   int numDeNotificacoesProcessadas = 0;
   int ponteiro;
   char parametros[30];
   int posicao, acao, quantidade;
   double valor;

   inicializarLivroDeOfertas(&livroDeOfertas);

   // Inicializando o Livro de Ofertas
   inserirInicio(&livroDeOfertas, 15.4, 50);
   inserirFim(&livroDeOfertas, 15.4, 10);
   inserirFim(&livroDeOfertas, 15.9, 20);
   inserirFim(&livroDeOfertas, 16.1, 100);
   inserirFim(&livroDeOfertas, 16.2, 20);
   inserirFim(&livroDeOfertas, 16.43, 30);
   inserirFim(&livroDeOfertas, 17.20, 70);
   inserirFim(&livroDeOfertas, 17.35, 80);
   inserirFim(&livroDeOfertas, 17.5, 200);
   imprimirLivroDeOfertas(&livroDeOfertas);

   printf("");
   scanf("%i", &numDeNotificacoes);

   while(numDeNotificacoesProcessadas < numDeNotificacoes) {

    printf("");
    scanf("%s", parametros);

    ponteiro = 0;

    posicao = getPosicao(parametros, &ponteiro);
    acao = getAcao(parametros, &ponteiro);
    valor = getValor(parametros, &ponteiro);
    quantidade = getQuantidade(parametros, &ponteiro);

    switch(acao) {
      case 0:
        if((valor > 0) && (quantidade > 0)) {
          inserir(&livroDeOfertas, posicao, valor, quantidade);
        } else {
          printf("Inserções esperam valores positivos e não nulos para \"valor\" e \"quantidade\".\n");
          printf("Operação: %i,0,%.2f,%i foi rejeitada!\n", posicao, valor, quantidade);
        }
        break;

      case 1:
        if((valor > 0) && (quantidade > 0)) {
          modificar(&livroDeOfertas, posicao, valor, quantidade);
        } else {
          printf("Modificações esperam valores positivos e não nulos para \"valor\" e \"quantidade\".\n");
          printf("Operação: %i,1,%.2f,%i foi rejeitada!\n", posicao, valor, quantidade);
        }
        break;

      case 2:
        if(valor == 0 && quantidade == 0) {
          remover(&livroDeOfertas, posicao);
        } else {
          printf("Remoções esperam valores zero para \"valor\" e \"quantidade\".\n");
          printf("Operação: %i,2,%.2f,%i foi rejeitada!\n", posicao, valor, quantidade);
        }
        break;

      default:
        printf("Operação: %i,0,%.2f,%i é inválida\n", posicao, valor, quantidade);
    }

    numDeNotificacoesProcessadas++;
  }

  imprimirLivroDeOfertas(&livroDeOfertas);
}