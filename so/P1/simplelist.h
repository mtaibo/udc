#ifndef SIMPLELIST_H
#define SIMPLELIST_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// This list is a simple pointer array ended with NULL
// It is used for commands like path, open, close,...

#define MAX_LIST 4096
typedef void * SimpleList [MAX_LIST];

int AddElement(SimpleList l, void *el);
void PrintListFirst(SimpleList l, int count, int numbered,void (*print_element)(void*));
void PrintListLast(SimpleList l, int count, int numbered,void (*print_element)(void*));
void PrintFullList(SimpleList l, int numbered,void (*print_element)(void*));
void ClearList(SimpleList l);

void * GetFirstElement(SimpleList l);
void * GetNextElement(SimpleList l);
void * GetNextElementAfter(SimpleList l, void * el,int (*cmp)(void *,void*));
void * GetElementAtPos (SimpleList l, int n);
int RemoveElementAtPos (SimpleList l, int n);
int FindElement(SimpleList l, void * el, int (*cmp)(void*,void*));
int RemoveElement(SimpleList l, void * el,int (*cmp)(void*,void*));

#endif // SIMPLELIST_H