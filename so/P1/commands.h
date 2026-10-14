#ifndef COMMANDS_H
#define COMMANDS_H

#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#define MAXNAME 1024

struct COMMAND {
    char * name;
    void (*func)(char**);
    const char * help;
};

extern struct COMMAND C[];

void Cmd_end (char * args[]);
void Cmd_date (char * args[]);
void Cmd_pid (char * args[]);
void Cmd_authors(char *args[]);
void Cmd_sysinfo (char *args[]);
void Cmd_help (char *args[]);
void Cmd_chdir (char * args[]);
void Cmd_open (char *args[]);
void Cmd_close (char *args[]);
void Cmd_listopen (char *args[]);
void Cmd_dup (char *args[]);
void Cmd_lseek (char *args[]);
void Cmd_readstr (char *args[]);
void Cmd_writestr (char *args[]);
void Cmd_makefile (char *args[]);
void Cmd_makedir (char *args[]);
void Cmd_delete (char *args[]);
void Cmd_deltree (char *args[]);
void Cmd_listfile (char *args[]);
void Cmd_list (char *args[]);

// Custom commands for easier shell navigation
void Cmd_clear (char *args[]);
void Cmd_l (char *args[]);
void Cmd_cd (char *args[]);

#endif //COMMANDS_H
