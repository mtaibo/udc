#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

#include "list.h"

#define MAX_PATH_LEN 1024

// AUX FUNCTIONS

static void FormatPerms (mode_t m, char out[11]) {

    if (S_ISDIR(m)) out[0] = 'd';
    else if (S_ISLNK(m)) out[0] = 'l';
    else if (S_ISCHR(m)) out[0] = 'c';
    else if (S_ISBLK(m)) out[0] = 'b';
    else if (S_ISFIFO(m)) out[0] = 'p';
    else if (S_ISSOCK(m)) out[0] = 's';
    else out[0] = '-';

    out[1] = (m & S_IRUSR) ? 'r' : '-';
    out[2] = (m & S_IWUSR) ? 'w' : '-';
    out[3] = (m & S_IXUSR) ? 'x' : '-';
    out[4] = (m & S_IRGRP) ? 'r' : '-';
    out[5] = (m & S_IWGRP) ? 'w' : '-';
    out[6] = (m & S_IXGRP) ? 'x' : '-';
    out[7] = (m & S_IROTH) ? 'r' : '-';
    out[8] = (m & S_IWOTH) ? 'w' : '-';
    out[9] = (m & S_IXOTH) ? 'x' : '-';
    out[10] = '\0';
}

static int DigitCount (unsigned long n) {
    int d = 1;
    while (n >= 10) { n /= 10; d++; }
    return d;
}

// MAIN FUNCTIONS

void PrintEntry (const char *path, const char *name, int longFlag, int linkFlag, int accFlag, int inoWidth, int userWidth, int groupWidth) {

    struct stat st;
    if (lstat(path, &st) == -1) { printf(" ****error al acceder a %s:%s\n", path, strerror(errno)); return; }

    // If the file is a dir, add / at the end of the name
    char dispName[MAX_PATH_LEN + 2];
    snprintf(dispName, sizeof(dispName), S_ISDIR(st.st_mode) ? "%s/" : "%s", name);

    char linkStr[MAX_PATH_LEN + 8] = "";

    if (linkFlag && S_ISLNK(st.st_mode)) {
        char target[MAX_PATH_LEN];
        ssize_t n = readlink(path, target, sizeof(target) - 1);
        if (n != -1) {
            target[n] = '\0';
            snprintf(linkStr, sizeof(linkStr), " -> %s", target);
        }
    }

    if (!longFlag) {
        char dateStr[32] = "";
        if (accFlag) {
            char datebuf[20];
            strftime(datebuf, sizeof(datebuf), "%Y/%m/%d-%H:%M", localtime(&st.st_atime));
            snprintf(dateStr, sizeof(dateStr), "%s ", datebuf);
        }
        printf("%8lld  %s%s%s\n", (long long) st.st_size, dateStr, dispName, linkStr);
        return;
    }

    char datebuf[32];
    time_t t = accFlag ? st.st_atime : st.st_mtime;
    strftime(datebuf, sizeof(datebuf), "%Y/%m/%d-%H:%M", localtime(&t));

    char perms[11];
    FormatPerms(st.st_mode, perms);

    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);
    const char *userName = pw != NULL ? pw->pw_name : "??????";
    const char *groupName = gr != NULL ? gr->gr_name : "??????";

    // Count widths to print the entry clean and organized
    int width = inoWidth > 0 ? inoWidth : DigitCount((unsigned long) st.st_ino);
    int uWidth = userWidth > 0 ? userWidth : (int) strlen(userName);
    int gWidth = groupWidth > 0 ? groupWidth : (int) strlen(groupName);

    printf("%s %3lu ( %*lu ) %-*s %-*s %s %8lu %s%s\n",
        datebuf,
        (unsigned long) st.st_nlink,
        width,
        (unsigned long) st.st_ino,
        uWidth,
        userName,
        gWidth,
        groupName,
        perms,
        (unsigned long) st.st_size,
        dispName,
        linkStr
    );
}

void ListDirectory (const char *path, int longFlag, int linkFlag, int accFlag, int hidFlag, int recMode) {

    // If path is not a directory, works as listfile
    struct stat topSt;
    if (lstat(path, &topSt) == -1) { printf("\n ****error al acceder a %s:%s\n", path, strerror(errno)); return; }
    if (!S_ISDIR(topSt.st_mode)) { PrintEntry(path, path, longFlag, linkFlag, accFlag, 0, 0, 0); return; }

    DIR *dir = opendir(path);
    if (dir == NULL) { printf("\n ****error al acceder a %s:%s\n", path, strerror(errno)); return; }

    struct dirent *entry;
    char child[MAX_PATH_LEN];

    // -recb flag, displays subdirs before the current dir with a recursive call
    if (recMode == 1) {

        while ((entry = readdir(dir)) != NULL) {

            // Avoid . and .. to prevent infinite loop
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
            if (!hidFlag && entry->d_name[0] == '.') continue;

            snprintf(child, sizeof(child), "%s/%s", path, entry->d_name);
            struct stat st;
            if (lstat(child, &st) == 0 && S_ISDIR(st.st_mode))
                ListDirectory(child, longFlag, linkFlag, accFlag, hidFlag, recMode);
        }
        rewinddir(dir);
    }

    // Display path dir

    // Previous loop to find the widest inode/user/group to organize the columns
    int inoWidth = 1, userWidth = 1, groupWidth = 1;
    if (longFlag) {
        while ((entry = readdir(dir)) != NULL) {
            if (!hidFlag && (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") || entry->d_name[0] == '.')) continue;
            snprintf(child, sizeof(child), "%s/%s", path, entry->d_name);
            struct stat st;
            if (lstat(child, &st) == 0) {
                int d = DigitCount((unsigned long) st.st_ino);
                if (d > inoWidth) inoWidth = d;

                struct passwd *pw = getpwuid(st.st_uid);
                struct group *gr = getgrgid(st.st_gid);
                int uLen = (int) strlen(pw != NULL ? pw->pw_name : "??????");
                int gLen = (int) strlen(gr != NULL ? gr->gr_name : "??????");
                if (uLen > userWidth) userWidth = uLen;
                if (gLen > groupWidth) groupWidth = gLen;
            }
        }
        rewinddir(dir);
    }

    printf("\n************ %s\n", path);
    while ((entry = readdir(dir)) != NULL) {
        if (!hidFlag && (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") || entry->d_name[0] == '.')) continue;
        snprintf(child, sizeof(child), "%s/%s", path, entry->d_name);
        PrintEntry(child, entry->d_name, longFlag, linkFlag, accFlag, inoWidth, userWidth, groupWidth);
    }

    // -reca flag, displays subdirs after the current dir with a recursive call
    if (recMode == 2) {
        rewinddir(dir);
        while ((entry = readdir(dir)) != NULL) {
            // Nunca recursionar en . o .. (bucle infinito), ni siquiera con hidFlag
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
            if (!hidFlag && entry->d_name[0] == '.') continue;

            snprintf(child, sizeof(child), "%s/%s", path, entry->d_name);
            struct stat st;
            if (lstat(child, &st) == 0 && S_ISDIR(st.st_mode))
                ListDirectory(child, longFlag, linkFlag, accFlag, hidFlag, recMode);
        }
    }

    closedir(dir);
}
