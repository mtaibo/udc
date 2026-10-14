#include "simplelist.h"

int AddElement (SimpleList l, void *el) {
    int i;
    if (el == NULL) { errno=EFAULT; return -1; }
    for (i=0; l[i] != NULL; i++);
    if (i == MAX_LIST-1) { errno=ENOSPC; return -1; }
    l[i] = el;
    l[++i] = NULL;
    return i;
}

void PrintListFirst (SimpleList l, int count, int numbered, void (*print_element) (void*)) {
    int i;
    for (i=0; l[i] != NULL && i < count; i++){
        if (numbered) printf("%d->", i);
	    (*print_element) (l[i]);
    }
}

int ListLength (SimpleList l) {
    int i;
    for (i=0; l[i] != NULL; i++) if (i == MAX_LIST-1) return MAX_LIST;
	return i;
}

void PrintListLast (SimpleList l, int count, int numbered, void (*print_element) (void*)) {
    int i=0, num=ListLength(l);
    if ((i = num-count) < 0) i=0;
    for (; l[i] != NULL; i++){
        if (numbered) printf ("%d->", i);
	    (*print_element) (l[i]);
    }
}

void PrintFullList (SimpleList l, int numbered, void (*print_element) (void*)) {
    PrintListFirst(l, MAX_LIST, numbered, print_element);
}

void * GetElementAtPos (SimpleList l, int n) {
    int i;
    if (n < 0) return NULL;
    for (i=0; i < n; i++) if (l[i] == NULL) return NULL;
    return l[n];
}

int RemoveElementAtPos (SimpleList l, int pos) {
    int i;
    if (GetElementAtPos(l, pos) != NULL){
        free(l[pos]);
        for (i=pos; l[i]!=NULL;i++) l[i] = l[i+1];
        return 0;
    }
    return -1;
}

int FindElement (SimpleList l, void * el, int (*cmp) (void*, void*)) {
    int i;
    if (el == NULL) { errno=EFAULT; return -1; }
    for (i=0; l[i] != NULL; i++) if (!(*cmp) (l[i], el)) return i;
    if (i == MAX_LIST -1) { errno=ENOSPC; return -1; }
    return -1;
}

int RemoveElement (SimpleList l, void * el, int (*cmp) (void*, void*)) {
    int pos, i;
    if ((pos=FindElement(l, el, cmp)) == -1) { errno=ENOENT; return -1; }
    free(l[pos]);
    for (i=pos; l[i] != NULL; i++) l[i] = l[i+1];
    return 0;
}

void ClearList(SimpleList l) {
    int i;
    for (i=0; l[i] != NULL; i++) { free(l[i]); l[i]=NULL; }
}

void * GetNextElementAfter (SimpleList l, void * el, int (*cmp) (void*, void*)) {
    int pos;
    if ((pos=FindElement(l, el, cmp)) == -1) { errno=ENOENT; return NULL; }
    return (l[pos+1]);
}

void * GetFirstOrNextElement (SimpleList l, int first) {
   static int current=0;
   if (first == 1) current=0;
   return (l[current++]);
}

void * GetFirstElement (SimpleList l) {
    return GetFirstOrNextElement(l, 1);
}

void * GetNextElement (SimpleList l) {
    return GetFirstOrNextElement(l, 0);
}
