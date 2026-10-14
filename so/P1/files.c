#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "files.h"
#include "simplelist.c"

typedef struct {
    int fd;
    char name[256];
    int flags;
} OpenFile;

static SimpleList openFiles;

// AUX FUNCTIONS

static int CmpFd (void *a, void *b) {
    return ((OpenFile *) a)->fd - ((OpenFile *) b)->fd;
}

static void FlagsToString (int flags, char *str, size_t size) {
    str[0] = '\0';
    switch (flags & O_ACCMODE) {
        case O_WRONLY: strncat(str, "O_WRONLY ", size - strlen(str) - 1); break;
        case O_RDWR:   strncat(str, "O_RDWR ",   size - strlen(str) - 1); break;
    }
    if (flags & O_CREAT)  strncat(str, "O_CREAT ",  size - strlen(str) - 1);
    if (flags & O_EXCL)   strncat(str, "O_EXCL ",   size - strlen(str) - 1);
    if (flags & O_APPEND) strncat(str, "O_APPEND ", size - strlen(str) - 1);
    if (flags & O_TRUNC)  strncat(str, "O_TRUNC ",  size - strlen(str) - 1);
}

// Find a fd name that was not opened by open
static ssize_t ReadInheritedFdPath (int fd, char *buf, size_t size) {
    char procPath[32];
    snprintf(procPath, sizeof(procPath), "/proc/self/fd/%d", fd);
    ssize_t n = readlink(procPath, buf, size - 1);
    if (n > 0) buf[n] = '\0';
    return n;
}

// Returns the highest fd that was found on openFiles list
static int HighestTrackedFd (void) {
    int highest = -1;
    int len = ListLength(openFiles);
    for (int i = 0; i < len; i++) {
        OpenFile *f = GetElementAtPos(openFiles, i);
        if (f != NULL && f->fd > highest) highest = f->fd;
    }
    return highest;
}

// MAIN FUNCTIONS

void InitStdFiles (void) {

    static const char * STD_NAMES[] = { "entrada estandar", "salida estandar", "error estandar" };

    for (int fd = 0; fd <= 2; fd++) {
        if (fcntl(fd, F_GETFD) == -1) continue;
        int flags = fcntl(fd, F_GETFL);
        AddNewFile(fd, STD_NAMES[fd], (flags == -1) ? 0 : flags);
    }
}

void ShowFileDescriptors (int limit) {

    printf("\n");
    int base = HighestTrackedFd() + 1;
    if (base < NUM_DESCRIPTORS) base = NUM_DESCRIPTORS;
    int max = (limit > 0 && limit < base) ? limit : base;

    for (int fd = 0; fd < max; fd++) {

        off_t offset = lseek(fd, 0, SEEK_CUR);

        char offsetStr[16] = "  ";
        if (offset != -1) snprintf(offsetStr, sizeof(offsetStr), "%lld", (long long) offset);

        char nameBuf[256] = "";
        char flagsStr[64] = "";

        OpenFile key = { .fd = fd };
        int pos = FindElement(openFiles, &key, CmpFd);
        OpenFile *found = (pos == -1) ? NULL : GetElementAtPos(openFiles, pos);

        if (found != NULL) {
            strncpy(nameBuf, found->name, sizeof(nameBuf) - 1);
            FlagsToString(found->flags, flagsStr, sizeof(flagsStr));

        } else if (fcntl(fd, F_GETFD) != -1) {
            if (ReadInheritedFdPath(fd, nameBuf, sizeof(nameBuf)) <= 0)
                strncpy(nameBuf, "heredado (nombre desconocido)", sizeof(nameBuf) - 1);
            int flags = fcntl(fd, F_GETFL);
            if (flags != -1) FlagsToString(flags, flagsStr, sizeof(flagsStr));

        } else strncpy(nameBuf, "no usado ", sizeof(nameBuf) - 1);

        printf("descriptor: %d, offset: (%s)-> %s %s\n", fd, offsetStr, nameBuf, flagsStr);
    }
}

int AddNewFile (int fd, const char *name, int flags) {

    OpenFile *f = malloc(sizeof(OpenFile));
    if (f == NULL) { printf("\n"); perror("Imposible asignar memoria"); return -1; }

    f->fd = fd;
    strncpy(f->name, name, sizeof(f->name) - 1);
    f->name[sizeof(f->name) - 1] = '\0';
    f->flags = flags;

    int pos = AddElement(openFiles, f);
    if (pos == -1) free(f);
    return pos;
}

int RemoveFile (int fd) {
    OpenFile key = { .fd = fd };
    return RemoveElement(openFiles, &key, CmpFd);
}

int DuplicateFile (int oldfd, int newfd) {

    OpenFile key = { .fd = oldfd };
    int pos = FindElement(openFiles, &key, CmpFd);
    OpenFile *found = (pos == -1) ? NULL : GetElementAtPos(openFiles, pos);
    if (found == NULL) return -1;

    char name[sizeof(found->name) + 32];
    snprintf(name, sizeof(name), "duplicado de %d (%s)", oldfd, found->name);
    return AddNewFile(newfd, name, found->flags);
}
