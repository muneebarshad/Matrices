#include "assignment3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function for quicksort
int cmpfunc(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);

} // Code taken from stackoverflow

static SLnodePtr createbottomnode(int m, int key) {

  srand(time(NULL));
  int x = rand() % m + 1;
  int *b = malloc(sizeof(int) * x);

  if (x == 1) {

    return NULL;
  }

  else {

    for (int j = 0; j < x; j++) {
      b[j] = rand()%100;
    }

    qsort(b, m, sizeof(int), cmpfunc);

    SLnodePtr head = NULL;
    SLnodePtr ptr = NULL;
    SLnodePtr new = NULL;

    for (int i = 0; i < x; i++) {

      new = malloc(sizeof(struct SLnode));
      new->key = b[i] + key;
      new->next = NULL;
      if (head == NULL) {
        head = new;

      }

      else {
        ptr = head;
        while (ptr->next != NULL)
          ptr = ptr->next;
        ptr->next = new;
      }
    }
    free(b);
    return head;
  }
}

HBnodePtr createHBlist(int n, int m) {
  // Create an array of size n and quicksort it.
  int *a = malloc(sizeof(int) * n);
  srand(time(NULL));
  for (int j = 0; j < n; j++) {

    a[j] = rand()%100;
  }

  qsort(a, n, sizeof(int), cmpfunc);

  HBnodePtr ptr = NULL;
  HBnodePtr head = NULL;
  HBnodePtr p = NULL;

  for (int i = 0; i < n; i++) {

    ptr = malloc(sizeof(struct HBnode));
    ptr->key = a[i];
    ptr->next = NULL;

    if (head == NULL) {

      head = ptr;

    }

    else {
      p = head;
      while (p->next != NULL)
        p = p->next;
      p->next = ptr;
    }
  }

  HBnodePtr A = NULL;
  A = head;

  while (A != NULL) {
    A->bottom = createbottomnode(m, A->key);
    A = A->next;
  }
  free(a);
  return head;
}

static SLnodePtr mergelist(HBnodePtr a, HBnodePtr b) {
  SLnodePtr result = NULL;
  SLnodePtr head = NULL;
  if (a == NULL) {
    return b;
  }

  if (b == NULL) {
    return a;
  }

  if (a->key <= b->key) {
    result = a;
    a = a->next;

  } else {
    result = b;
    b = b->next;
  }

  head = result;

  while (a != NULL && b != NULL) {
    if (a->key <= b->key) {
      result->next = a;
      result = a;
      a = a->next;

    }

    else {
      result->next = b;
      result = b;
      b = b->next;
    }
  }
  if (a == NULL) {
    result->next = b;
  }
  if (b == NULL) {
    result->next = a;
  }

  return head;
}

SLnodePtr flattenList(const HBnodePtr L) {
  SLnodePtr list = NULL;
  HBnodePtr p = NULL;
  SLnodePtr head = NULL;
  SLnodePtr q = NULL;
  SLnodePtr ptr = NULL;
  p = L;

  list = mergelist(p->bottom, (p->next)->bottom);
  p = p->next;

  while (p->next != NULL) {

    list = mergelist(list, (p->next)->bottom);
    p = p->next;
  }

  list = mergelist(list, L);

  while (list != NULL) {

    ptr = malloc(sizeof(struct SLnode));
    ptr->key = list->key;
    ptr->next = NULL;
    list = list->next;

    if (head == NULL) {
      head = ptr;
    }

    else {
      q = head;
      while (q->next != NULL)
        q = q->next;
      q->next = ptr;
    }
  }

  return head;
}

void freeSLlist(SLnodePtr L) {
  SLnodePtr P = L;
  SLnodePtr temp;

  while (P != NULL) {
    temp = P;
    P = P->next;
    free(temp);
  }
}

void freeHBlist(HBnodePtr L) {
  SLnodePtr temp1;
  HBnodePtr p = L;
  SLnodePtr q = NULL;

  while (p != NULL) {

    q = p->bottom;
    freeSLlist(q);
    temp1 = p;
    p = p->next;
    free(temp1);
  }
}

void printSLlist(SLnodePtr result) {

  while (result != NULL) {
    printf("%d-> ", result->key);
    result = result->next;
  }
}

void printHBlist(HBnodePtr head) {

  HBnodePtr p = NULL;
  HBnodePtr q = NULL;
  if (head == NULL) {
    printf("\nEmpty:\n");
  } else {
    p = head;
    while (p != NULL) {
      printf("%d->", p->key);
      q = p->bottom;
      while (q != NULL) {
        printf("%d  ", q->key);
        q = q->next;
      }
      printf("\n");
      p = p->next;
    }
  }
}# Data-Structures
