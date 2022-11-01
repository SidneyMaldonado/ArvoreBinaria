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

/* A estrutura da �rvore � representada por um ponteiro
   para o n� raiz. Com esse ponteiro, temos acesso aos
   demais n�s. */

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

/* Fun��o que cria uma �rvore */
Tree* createTree()
{
  /* Uma �rvore � representada pelo endere�o do n� raiz,
     essa fun��o cria uma �rvore com nenhum elemento,
     ou seja, cria uma �rvore vazia, por isso retorna NULL. */
  return NULL;
}

/* Fun��o que verifica se uma �rvore � vazia */
int treeIsEmpty(Tree* t)
{
  /* Retorna 1 se a �rvore for vazia e 0 caso contr�rio */
  return t == NULL;

}

/* Fun��o que mostra a informa��o da �rvore */
void showTree(Tree* t, int level)
{
  /* Essa fun��o imprime os elementos de forma recursiva */
  level++;
  printf("\n %i -> ", level); /* nota��o para organizar na hora de mostrar os elementos */
  if(!treeIsEmpty(t)) /* se a �rvore n�o for vazia... */
  {
    /* Mostra os elementos em pr�-ordem */
    printf(" %d ", t->num); /* mostra a raiz */
    showTree(t->sae, level); /* mostra a sae (sub�rvore � esquerda) */
    showTree(t->sad, level); /* mostra a sad (sub�rvore � direita) */
  }
  printf(" "); /* nota��o para organizar na hora de mostrar os elementos */
}

/* Fun��o que insere um dado na �rvore */
void insertTree(Tree** t, int num)
{
	printf("inserindo %i \n", num);
  /* Essa fun��o insere os elementos de forma recursiva */
  if(*t == NULL)
  {
    *t = (Tree*)malloc(sizeof(Tree)); /* Aloca mem�ria para a estrutura */
    (*t)->sae = NULL; /* Sub�rvore � esquerda � NULL */
    (*t)->sad = NULL; /* Sub�rvore � direita � NULL */
    (*t)->num = num; /* Armazena a informa��o */
  } else {
    if(num < (*t)->num) /* Se o n�mero for menor ent�o vai pra esquerda */
    {
      /* Percorre pela sub�rvore � esquerda */
      insertTree(&(*t)->sae, num);
      rotateLeft(*t);
      rotateRight(*t);
    }
    if(num > (*t)->num) /* Se o n�mero for maior ent�o vai pra direita */
    {
      /* Percorre pela sub�rvore � direita */
      insertTree(&(*t)->sad, num);
      rotateLeft(*t);
      rotateRight(*t);
    }
  }
}

/* Fun��o que verifica se um elemento pertence ou n�o � �rvore */
int isInTree(Tree* t, int num) {

  if(treeIsEmpty(t)) { /* Se a �rvore estiver vazia, ent�o retorna 0 */
    return 0;
  }

  /* O operador l�gico || interrompe a busca quando o elemento for encontrado */
  return t->num==num || isInTree(t->sae, num) || isInTree(t->sad, num);
}

int main()
{
  Tree* t = createTree(); /* cria uma �rvore */

  insertTree(&t, 22); /* insere o elemento 12 na �rvore */
  insertTree(&t, 25); /* insere o elemento 15 na �rvore */
  insertTree(&t, 18); /* insere o elemento 10 na �rvore */
  insertTree(&t, 23); /* insere o elemento 13 na �rvore */
  insertTree(&t, 27); /* insere o elemento 12 na �rvore */
  insertTree(&t, 2); /* insere o elemento 15 na �rvore */
  insertTree(&t, 19); /* insere o elemento 10 na �rvore */
  insertTree(&t, 9); /* insere o elemento 13 na �rvore */

  showTree(t,0); /* Mostra os elementos da �rvore em pr�-ordem */

  if(treeIsEmpty(t)) /* Verifica se a �rvore est� vazia */
  {
    printf("\n\nArvore vazia!!\n");
  } else {
    printf("\n\nArvore NAO vazia!!\n");
  }

  if(isInTree(t, 15)) { /* Verifica se o n�mero 15 pertence a �rvore */
    printf("\nO numero 15 pertence a arvore!\n");
  } else {
     printf("\nO numero 15 NAO pertence a arvore!\n");
  }

  if(isInTree(t, 22)) { /* Verifica se o n�mero 22 pertence a �rvore */
    printf("\nO numero 22 pertence a arvore!\n\n");
  } else {
     printf("\nO numero 22 NAO pertence a arvore!\n\n");
  }

  free(t); /* Libera a mem�ria alocada pela estrutura �rvore */

  system("pause");
  return 0;
}
