#include <stdio.h>
#include <stdlib.h>

#ifndef _LIST_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void Delete(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
ElementType Retrieve(Position P);

#endif /*** _LIST_H ***/

struct Node {
  ElementType Element;
  Position Next;
};

int IsLast(Position P, List L) { return P->Next == NULL; }

Position Find(ElementType X, List L) {
  Position P = L->Next;
  while (P != NULL && P->Element != X) {
    P = P->Next;
  }
  return P;
}

void Delete(ElementType X, List L) {
  Position P, tmp;
  P = FindPrevious(X, L);
  if (!IsLast(P, L)) {
    tmp = P->Next;
    P->Next = tmp->Next;
    free(tmp);
  }
}

Position FindPrevious(ElementType X, List L) {// 寻找 P 前面的那个元素
  Position P;
  P = L;
  while (P->Next != NULL && P->Next->Element != X) {
    P = P->Next;
  }
  return P;
}

void Insert(ElementType X, List L, Position P) {
  Position tmp;
  tmp = (Position)(malloc(sizeof(struct Node)));
  if (tmp == NULL) {
  }
  tmp->Element = X;
  tmp->Next = P->Next;
  P->Next = tmp;
}

void DeleteList(List L) {
  Position P, tmp;
  P = L->Next;
  L->Next = NULL;
  while (P != NULL) {
    tmp = P->Next;
    free(P);
    P = tmp;
  }
}