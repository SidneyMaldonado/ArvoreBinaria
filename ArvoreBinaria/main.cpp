#include <iostream>

using namespace std;

#include <stdio.h>
#include <stdlib.h>


typedef struct tree
{
  int num;
  struct tree* sad;
  struct tree* sae;
} Tree;

/* A estrutura da árvore é representada por um ponteiro
   para o nó raiz. Com esse ponteiro, temos acesso aos
   demais nós. */

void rotateLeft(Tree* t) // rotaciona o no para a esquerda
{
    if (t->sae == NULL || t->sad == NULL){
        return;
    }

    // Verificar se ja esta balanceada
    if ( t->sae->num < t->num && t->sad->num > t->num ){
        return;
    }

    int e,d,s;

    s = t->sad->num;
    d = t->sae->num;
    e = t->num;

    t->num = s; // o no da direita sobe
    t->sae->num = e; // o no da esquerda sera o superior
    t->sad->num = d; // o no da direita sera o que era da esquerda;
    return;

}

void rotateRight(Tree * t){
    if (t->sae == NULL || t->sad == NULL){
        return;
    }
    // Verificar se ja esta balanceada
    if ( t->sae->num < t->num && t->sad->num > t->num ){
        return;
    }
    int e;
    int s;
    int d;

    s = t->sae->num;
    e = t->sad->num;
    d = t->num;

    t->num = s;
    t->sae->num = e;
    t->sad->num = d;

}

/* Função que cria uma árvore */
Tree* createTree()
{
  /* Uma árvore é representada pelo endereço do nó raiz,
     essa função cria uma árvore com nenhum elemento,
     ou seja, cria uma árvore vazia, por isso retorna NULL. */
  return NULL;
}

/* Função que verifica se uma árvore é vazia */
int treeIsEmpty(Tree* t)
{
  /* Retorna 1 se a árvore for vazia e 0 caso contrário */
  return t == NULL;

}

/* Função que mostra a informação da árvore */
void showTree(Tree* t, int level)
{
  /* Essa função imprime os elementos de forma recursiva */
  level++;
  printf("\n %i -> ", level); /* notação para organizar na hora de mostrar os elementos */
  if(!treeIsEmpty(t)) /* se a árvore não for vazia... */
  {
    /* Mostra os elementos em pré-ordem */
    printf(" %d ", t->num); /* mostra a raiz */
    showTree(t->sae, level); /* mostra a sae (subárvore à esquerda) */
    showTree(t->sad, level); /* mostra a sad (subárvore à direita) */
  }
  printf(" "); /* notação para organizar na hora de mostrar os elementos */
}

/* Função que insere um dado na árvore */
void insertTree(Tree** t, int num)
{
	printf("inserindo %i \n", num);
  /* Essa função insere os elementos de forma recursiva */
  if(*t == NULL)
  {
    *t = (Tree*)malloc(sizeof(Tree)); /* Aloca memória para a estrutura */
    (*t)->sae = NULL; /* Subárvore à esquerda é NULL */
    (*t)->sad = NULL; /* Subárvore à direita é NULL */
    (*t)->num = num; /* Armazena a informação */
  } else {
    if(num < (*t)->num) /* Se o número for menor então vai pra esquerda */
    {
      /* Percorre pela subárvore à esquerda */
      insertTree(&(*t)->sae, num);
      rotateLeft(*t);
      rotateRight(*t);
    }
    if(num > (*t)->num) /* Se o número for maior então vai pra direita */
    {
      /* Percorre pela subárvore à direita */
      insertTree(&(*t)->sad, num);
      rotateLeft(*t);
      rotateRight(*t);
    }
  }
}

/* Função que verifica se um elemento pertence ou não à árvore */
int isInTree(Tree* t, int num) {

  if(treeIsEmpty(t)) { /* Se a árvore estiver vazia, então retorna 0 */
    return 0;
  }

  /* O operador lógico || interrompe a busca quando o elemento for encontrado */
  return t->num==num || isInTree(t->sae, num) || isInTree(t->sad, num);
}

int main()
{
  Tree* t = createTree(); /* cria uma árvore */

  insertTree(&t, 22); /* insere o elemento 12 na árvore */
  insertTree(&t, 25); /* insere o elemento 15 na árvore */
  insertTree(&t, 18); /* insere o elemento 10 na árvore */
  insertTree(&t, 23); /* insere o elemento 13 na árvore */
  insertTree(&t, 27); /* insere o elemento 12 na árvore */
  insertTree(&t, 2); /* insere o elemento 15 na árvore */
  insertTree(&t, 19); /* insere o elemento 10 na árvore */
  insertTree(&t, 9); /* insere o elemento 13 na árvore */

  showTree(t,0); /* Mostra os elementos da árvore em pré-ordem */

  if(treeIsEmpty(t)) /* Verifica se a árvore está vazia */
  {
    printf("\n\nArvore vazia!!\n");
  } else {
    printf("\n\nArvore NAO vazia!!\n");
  }

  if(isInTree(t, 15)) { /* Verifica se o número 15 pertence a árvore */
    printf("\nO numero 15 pertence a arvore!\n");
  } else {
     printf("\nO numero 15 NAO pertence a arvore!\n");
  }

  if(isInTree(t, 22)) { /* Verifica se o número 22 pertence a árvore */
    printf("\nO numero 22 pertence a arvore!\n\n");
  } else {
     printf("\nO numero 22 NAO pertence a arvore!\n\n");
  }

  free(t); /* Libera a memória alocada pela estrutura árvore */

  system("pause");
  return 0;
}
