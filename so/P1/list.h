#ifndef LIST_H
#define LIST_H

// Width arguments on PrintEntry were introduced with clean printing purpose
void PrintEntry (const char *path, const char *name, int longFlag, int linkFlag, int accFlag, int inoWidth, int userWidth, int groupWidth);
void ListDirectory (const char *path, int longFlag, int linkFlag, int accFlag, int hidFlag, int recMode);

#endif //LIST_H
