#ifndef _LIST_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

#endif /*** _LIST_H ***/

List MakeEmpty(List L);
int IsEmpty(List L);