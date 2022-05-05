#include <stdlib.h>

#ifndef _STACK_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef int ElementType;

int IsEmpty(Stack S);
Stack CreateStack();
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Pop(Stack S);
ElementType Top(Stack S);

#endif

struct Node {
  ElementType Element;
  PtrToNode Next;
};

int IsEmpty(Stack S) { return S->Next == NULL; }

Stack CreateStack() {
  Stack S;
  S = (Stack)(malloc(sizeof(struct Node)));
  if (S == NULL) {
  }
  S->Next = NULL;
  MakeEmpty(S);
  return S;
}

void MakeEmpty(Stack S) {
  if (S == NULL) {
  } else {
    while (!IsEmpty(S)) {
      Pop(S);
    }
  }
}

void Push(ElementType X, Stack S) {
  PtrToNode tmp;
  tmp = (PtrToNode)(malloc(sizeof(struct Node)));
  if (tmp == NULL) {
  } else {
    tmp->Element = X;
    tmp->Next = S->Next;
    S->Next = tmp;
  }
}

ElementType Top(Stack S) {
  if (!IsEmpty(S)) {
    return S->Next->Element;
  }
  return 0;
}

ElementType Pop(Stack S) {
  PtrToNode cell;
  ElementType tmp;
  if (!IsEmpty(S)) {
    cell = S->Next;
    S->Next = cell->Next;
    tmp = cell->Element;
    free(cell);
  }
  return 0;
}