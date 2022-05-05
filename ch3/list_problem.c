#include "list.h"

/***

这个文件里是和链表有关的题目的函数实现

****/

// 3.1 print all elements in a list

void PrintElement(ElementType x) { printf("%d", x); }

void PrintList(List L) {
  Position P = L;
  while (P->Next != NULL) {
    P = P->Next;
    PrintElement(P->Element);
  }
}

// 3.2 print a list of elements of another list, in O(M+N) complexity

void PrintListByAnotherList(List x, List y) {
  Position p, q;
  p = x;
  q = y;
  unsigned count = 0;
  while (q != NULL) {
    while (count != q->Element) {
      count++;
      if (p != NULL) {
        p = p->Next;
      } else {
        // error!
      }
    }
    PrintElement(p->Element);
    q = q->Next;
  }
}

// 3.3 swap adjacent elements (only for one-direction list)

void SwapAdjacentElement(List L, Position P) { // swap P and P->Next
  Position prev = FindPrevious(P->Element, L);
  if (!IsLast(prev, L) && P->Next != NULL) {
    prev->Next = P->Next;
    P->Next = P->Next->Next;
    P->Next->Next = P;
  } else {
    // error!
  }
}

// 3.4 intersect of two increasing lists, assume that there's no duplicate
// elements

void Add(ElementType x, List l) {
  Position p = l;
  while (p->Next != NULL) {
    p = p->Next;
  }
  Position last = (Position)(malloc(sizeof(struct Node)));
  last->Next = NULL;
  p->Next = last;
}

List IntersectOrderedList(List x, List y) {
  List res;
  res = (List)(malloc(sizeof(struct Node)));
  res->Next = NULL;
  res->Element = -1;

  Position p, q;
  p = x;
  q = y;
  while (p != NULL && q != NULL) {
    if (p->Element > q->Element) {
      q = q->Next;
    } else if (p->Element < q->Element) {
      p = p->Next;
    } else {
      Add(p->Element, res);
    }
  }
  return res;
}

// 3.5 union of two increasing lists

List UnionOrderedList(List x, List y) {
  List res;
  res = (List)(malloc(sizeof(struct Node)));
  res->Next = NULL;
  res->Element = -1;

  Position p, q;
  p = x;
  q = y;
  while (p != NULL && q != NULL) {
    if (p->Element > q->Element) {
      q = q->Next;
    } else if (p->Element < q->Element) {
      p = p->Next;
    }
    Add(p->Element, res);
  }
  return res;
}

// 3.10 Josephus Game, construct a doubly linked list and move
