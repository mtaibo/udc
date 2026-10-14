/*
 *   Miguel Taibo Perez   (miguel.taibo.perez@udc.es)
 *   Aaron Mendez Agbamu  (aaron.mendez@udc.es)
 */

#include "commands.h"
#include "files.c"
#include "list.c"

struct COMMAND C[] = {

    {"exit", Cmd_end, "exit: Termina la ejecución del shell"},
    {"bye", Cmd_end, "bye: Termina la ejecución del shell"},
    {"date", Cmd_date, "date: [-d | -t]\tMuestra la fecha y/o la hora actual"},
    {"pid", Cmd_pid, "pid: [-p]\tMuestra el pid del shell o de su proceso padre"},
    {"authors", Cmd_authors, "authors: [-n | -l]\tMuestra los nombres y/o logins de los autores"},
    {"sysinfo", Cmd_sysinfo, "sysinfo: \tMuestra informacion de la maquina donde corre el shell"},
    {"help", Cmd_help, "help: [cmd]\tMuestra ayuda sobre los comandos"},
    {"chdir", Cmd_chdir, "chdir: [dir]\tCambia (o muestra) el directorio actual del shell"},
    {"open", Cmd_open,
        "open: test m1 m2...\n\nAbre el fichero test y lo añade a la lista de ficheros abiertos del shell.\n"
        "m1, m2,... es el modo de apertura (or bit a bit de los siguientes):\n\n"
        "\tcr: O_CREAT\n"
        "\tap: O_APPEND\n"
        "\tex: O_EXCL\n"
        "\tro: O_RDONLY\n"
        "\trw: O_RDWR\n"
        "\two: O_WRONLY\n"
        "\ttr: O_TRUNC"},
    {"close", Cmd_close, "close: df [-f]\tCierra el descriptor df y lo elimina de la lista de ficheros abiertos\n\t-f: cierra el descriptor aunque corresponda a un mapeo activo"},
    {"listopen", Cmd_listopen, "listopen: [n]\tLista los ficheros abiertos (los n primeros) del shell"},
    {"dup", Cmd_dup, "dup: df Duplica el descriptor de fichero df y anade una nueva entrada a la lista ficheros abiertos"},
    {"lseek", Cmd_lseek,
        "lseek: df off ref\n\nPosiciona el offset en df en off. ref es la referencia:\n"
        "\tSEEK_SET principio fichero\n"
        "\tSEEK_CUR posicion actual\n"
        "\tSEEK_END final del fichero"},
    {"readstr", Cmd_readstr, "readstr: df cont\tLee cont bytes del fichero con descriptor df y los muestra en pantalla"},
    {"writestr", Cmd_writestr, "writestr: df string\tEscribe el string string en el fichero descrito por df"},
    {"makefile", Cmd_makefile, "makefile: [name]\tCrea un fichero de nombre name"},
    {"makedir", Cmd_makedir, "makedir: [name]\tCrea un directorio de nombre name"},
    {"delete", Cmd_delete, "delete: [name1 name2 ..]\tBorra ficheros o directorios vacios"},
    {"deltree", Cmd_deltree, "deltree: [name1 name2 ..]\tBorra ficheros o directorios no vacios recursivamente"},
    {"listfile", Cmd_listfile,
        "listfile: [-long][-link][-acc] name1 name2 ... \tlista ficheros;\n"
        "\t-long: listado largo\n"
        "\t-acc: acesstime\n"
        "\t-link: si es enlace simbolico, el path contenido"},
    {"list", Cmd_list,
        "list: [-reca] [-recb] [-hid][-long][-link][-acc] n1 n2 .. lista contenidos de directorios\n"
        "\t-long: listado largo\n"
        "\t-hid: incluye los ficheros ocultos\n"
        "\t-recb: recursivo (antes)\n"
        "\t-reca: recursivo (despues)\n"
        "\t-acc: acesstime\n"
        "\t-link: si es enlace simbolico, el path contenido"},

    // Extra commands for easier shell navigation
    {"clear", Cmd_clear, "clear: \tLimpia la pantalla del shell"},
    {"l", Cmd_l, "l: \tAlias de list -long ."},
    {"cd", Cmd_cd, "cd: \tAlias de chdir"},

    {NULL, NULL, NULL}
};

// AUX FUNCTIONS

// Parses a string to a file descriptor (int), returns -1 if invalid
static int ParseFd (const char *s) {
    char *endptr;
    long v = strtol(s, &endptr, 10);
    if (endptr == s || *endptr != '\0' || v < 0 || v > INT_MAX) return -1;
    return (int) v;
}

static void ShowCurrentDir () {
    char dir[MAXNAME];
    if (getcwd(dir, MAXNAME) == NULL) { printf("\n"); perror("Imposible obtener directorio"); }
    else printf("\n%s\n", dir);
}

static const char * GetCommandHelp (const char *name) {
    for (int i = 0; C[i].name != NULL; i++)
        if (!strcmp(name, C[i].name)) return C[i].help;
    return NULL;
}

static void RemoveTree (const char *path) {

    struct stat st;
    if (lstat(path, &st) == -1) { printf("\nImposible borrar %s: %s\n", path, strerror(errno)); return; }

    // If it's not a directory, remove
    if (!S_ISDIR(st.st_mode)) { if (unlink(path) == -1) printf("\nImposible borrar %s: %s\n", path, strerror(errno)); return; }

    // Otherwise, open the directory
    DIR *dir = opendir(path);
    if (dir == NULL) { printf("\nImposible abrir directorio %s: %s\n", path, strerror(errno)); return; }

    struct dirent *entry;
    char child[MAXNAME];

    // For every entry in the directory, delete subdirs via recursive calls
    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue; // Avoid . and .. to prevent infinite loops
        snprintf(child, sizeof(child), "%s/%s", path, entry->d_name); // Build child path
        RemoveTree(child); // Recursive call to remove subdirs
    }

    // After deleting all subdirs, delete current dir
    closedir(dir);
    if (rmdir(path) == -1) printf("\nImposible borrar %s: %s\n", path, strerror(errno));
}

// SHELL COMMANDS

void Cmd_end (char *args[]) {
    exit(0);
}

void Cmd_date (char *args[]) {

    char buf[64];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // Format date according to the args
    if (args[0] != NULL && !strcmp(args[0], "-d")) strftime(buf, sizeof(buf), "%d/%m/%Y", tm);
    else if (args[0] != NULL && !strcmp(args[0], "-t")) strftime(buf, sizeof(buf), "%H:%M:%S", tm);
    else strftime(buf, sizeof(buf), "%H:%M:%S\n%d/%m/%Y", tm);

    printf("\n%s\n", buf);
}

void Cmd_pid (char * args[]) {
    if (args[0] == NULL) printf("\nPid de shell: %d\n", (int) getpid());
    else if (!strcmp(args[0], "-p")) printf("\nPid del padre del shell: %d\n", (int) getppid());
}

void Cmd_authors (char *args[]) {
  if (args[0] != NULL && !strcmp(args[0], "-l")) printf("\nmiguel.taibo.perez@udc.es\naaron.mendez@udc.es\n");
  else if (args[0] != NULL && !strcmp(args[0], "-n")) printf("\nMiguel Taibo\nAaron Mendez\n");
  else printf("\nMiguel Taibo: miguel.taibo.perez@udc.es\nAaron Mendez: aaron.mendez@udc.es\n");
}

void Cmd_sysinfo (char *args[]) {

    struct utsname u;

    if (uname(&u) == -1) { printf("\n"); perror("Imposible obtener informacion del sistema"); }
    else
        printf("\n%s (%s), OS: %s-%s-%s\n",
            u.nodename, u.machine,
            u.sysname, u.release, u.version
        );
}

void Cmd_help (char *args[]) {

    if (args[0] == NULL) {
        printf("\nComandos disponibles:\n\n");
        printf("exit bye date pid authors sysinfo help chdir\n");
        printf("open close listopen dup lseek readstr writestr\n");
        printf("makefile makedir delete deltree listfile list clear l cd\n\n");

    } else {
        const char *help = GetCommandHelp(args[0]);
        if (help != NULL) printf("\n%s\n", help);
        else printf("\n%s: no encontrado\n", args[0]);
    }
}

void Cmd_chdir (char * args[]) {
    if (args[0] == NULL) ShowCurrentDir();
    else if (chdir(args[0]) == -1) { printf("\n"); perror("Imposible cambiar directorio"); }
}

void Cmd_open (char *args[]) {

    int flags = 0;
    int nargs = 0;

    // If there's no args, work as listopen, otherwise count how many args were given
    if (args[nargs] == NULL) { ShowFileDescriptors(0); return; }
    while (args[nargs] != NULL) nargs++;

    // Read the args and toggle the flags
    for (int i = 1; i < nargs; i++) {
        if (!strcmp(args[i], "cr")) flags |= O_CREAT;
        else if (!strcmp(args[i], "ex")) flags |= O_EXCL;
        else if (!strcmp(args[i], "ro")) flags |= O_RDONLY;
        else if (!strcmp(args[i], "wo")) flags |= O_WRONLY;
        else if (!strcmp(args[i], "rw")) flags |= O_RDWR;
        else if (!strcmp(args[i], "ap")) flags |= O_APPEND;
        else if (!strcmp(args[i], "tr")) flags |= O_TRUNC;
    }

    // Open the given file with the given flags and get a file descriptor
    int fd = open(args[0], flags, 0777);
    if (fd == -1) { printf("\n"); perror("Imposible abrir fichero"); }

    // Add the file descriptor to the open files list
    else if (AddNewFile(fd, args[0], flags) == -1) close(fd);
    else printf("\nAnadida entrada %d a la tabla ficheros abiertos\n", fd);
}

void Cmd_close (char *args[]) {
    if (args[0] == NULL) { ShowFileDescriptors(0); return; }
    int fd = ParseFd(args[0]);
    if (fd == -1) { printf("\nDescriptor invalido: %s\n", args[0]); return; }
    if (close(fd) == -1) { perror("Imposible cerrar descriptor"); return; }
    RemoveFile(fd);
}

void Cmd_listopen (char *args[]) {

    int n = 0;

    // If an arg was given, check if it's an int and show n descriptors
    if (args[0] != NULL) {
        char *endptr;
        long v = strtol(args[0], &endptr, 10);
        if (endptr != args[0] && *endptr == '\0' && v > 0) n = (int) v;
    }

    ShowFileDescriptors(n);
}

void Cmd_dup (char *args[]) {
    if (args[0] == NULL) { ShowFileDescriptors(0); return; }
    int fd = ParseFd(args[0]);
    if (fd == -1) { printf("\nDescriptor invalido: %s\n", args[0]); return; }
    int newfd = dup(fd);
    if (newfd == -1) { perror("Imposible duplicar descriptor"); return; }
    if (DuplicateFile(fd, newfd) == -1) close(newfd);
}

void Cmd_lseek (char *args[]) {

    if (args[0] == NULL || args[1] == NULL) { printf("\nParametros incorrectos\n"); return; }

    int fd = ParseFd(args[0]);
    if (fd == -1) { printf("\nDescriptor invalido: %s\n", args[0]); return; }
    long off = atol(args[1]);
    int initPos = SEEK_SET; // Default initPos at the first byte of the file

    if (args[2] != NULL) { // Third arg related with the initPos to seek is optional
        if (!strcmp(args[2], "SEEK_SET")) initPos = SEEK_SET;
        else if (!strcmp(args[2], "SEEK_CUR")) initPos = SEEK_CUR;
        else if (!strcmp(args[2], "SEEK_END")) initPos = SEEK_END;
    }

    off_t result = lseek(fd, off, initPos);
    if (result == -1) printf("\nError al intentar posicionar el descriptor %d en el offset  %ld: %s\n", fd, off, strerror(errno));
    else printf("\nDescriptor %d posicionado en %lld\n", fd, (long long) result);
}

void Cmd_readstr (char *args[]) {

    if (args[0] == NULL || args[1] == NULL) { printf("\nParametros incorrectos\n"); return; }

    int fd = ParseFd(args[0]);
    if (fd == -1) { printf("\nDescriptor invalido: %s\n", args[0]); return; }
    long count = atol(args[1]);
    if (count < 0) count = 0; // Safety check

    char *buf = malloc(count + 1);
    if (buf == NULL) { printf("\n"); perror("Imposible asignar memoria"); return; }

    ssize_t n = read(fd, buf, count);
    if (n == -1) { printf("\nError al intentar leer del descriptor %d: %s\n", fd, strerror(errno)); free(buf); return; }

    buf[n] = '\0';
    printf("\nLeidos %zd bytes del descriptor %d\n", n, fd);
    printf("%s\n", buf);
    free(buf);
}

void Cmd_writestr (char *args[]) {

    if (args[0] == NULL || args[1] == NULL) { printf("\nParametros incorrectos\n"); return; }

    int fd = ParseFd(args[0]);
    if (fd == -1) { printf("\nDescriptor invalido: %s\n", args[0]); return; }

    // Count str length
    size_t len = 0;
    for (int i = 1; args[i] != NULL; i++) len += strlen(args[i]) + 1;

    char *str = malloc(len);
    if (str == NULL) { printf("\n"); perror("Imposible asignar memoria"); return; }

    // Read full str coming from different args and concat
    str[0] = '\0';
    for (int i = 1; args[i] != NULL; i++) {
        strcat(str, args[i]);
        if (args[i + 1] != NULL) strcat(str, " ");
    }

    ssize_t n = write(fd, str, strlen(str));
    if (n == -1) printf("\nError intentar escribir %zu bytes en el descriptor %d: %s\n", strlen(str), fd, strerror(errno));
    free(str);
}

void Cmd_makefile (char *args[]) {
    if (args[0] == NULL) { ShowCurrentDir(); return; }
    int fd = open(args[0], O_CREAT | O_EXCL, 0777);
    if (fd == -1) printf("\nImposible crear %s: %s\n", args[0], strerror(errno));
    else close(fd);
}

void Cmd_makedir (char *args[]) {
    if (args[0] == NULL) { ShowCurrentDir(); return; }
    if (mkdir(args[0], 0777) == -1) printf("\nImposible crear %s: %s\n", args[0], strerror(errno));
}

void Cmd_delete (char *args[]) {

    if (args[0] == NULL) ShowCurrentDir();

    for (int i = 0; args[i] != NULL; i++) {

        struct stat st;
        if (lstat(args[i], &st) == -1) { printf("\nImposible borrar %s: %s\n", args[i], strerror(errno)); continue; }

        // Check if is a file or a dir to do unlink or rmdir
        if (S_ISDIR(st.st_mode)) { if (rmdir(args[i]) == -1) printf("\nImposible borrar %s: %s\n", args[i], strerror(errno)); }
        else if (unlink(args[i]) == -1) printf("\nImposible borrar %s: %s\n", args[i], strerror(errno));
    }
}

void Cmd_deltree (char *args[]) {
    if (args[0] == NULL) ShowCurrentDir();
    for (int i = 0; args[i] != NULL; i++) RemoveTree(args[i]);
}

void Cmd_listfile (char *args[]) {

    int longFlag = 0, linkFlag = 0, accFlag = 0;
    int i = 0;

    // Read the args and toggle the flags
    for (; args[i] != NULL && args[i][0] == '-'; i++) {
        if (!strcmp(args[i], "-long")) longFlag = 1;
        else if (!strcmp(args[i], "-link")) linkFlag = 1;
        else if (!strcmp(args[i], "-acc")) accFlag = 1;
        else break;
    }

    if (args[i] == NULL) ShowCurrentDir();

    printf("\n");
    for (; args[i] != NULL; i++) PrintEntry(args[i], args[i], longFlag, linkFlag, accFlag, 0, 0, 0);
}

void Cmd_list (char *args[]) {

    int longFlag = 0, linkFlag = 0, accFlag = 0, hidFlag = 0, recMode = 0;
    int i = 0;

    // Read the args and toggle the flags
    for (; args[i] != NULL && args[i][0] == '-'; i++) {
        if (!strcmp(args[i], "-long")) longFlag = 1;
        else if (!strcmp(args[i], "-link")) linkFlag = 1;
        else if (!strcmp(args[i], "-acc")) accFlag = 1;
        else if (!strcmp(args[i], "-hid")) hidFlag = 1;
        else if (!strcmp(args[i], "-recb")) recMode = 1;
        else if (!strcmp(args[i], "-reca")) recMode = 2;
        else break;
    }

    printf("\nDirectorio actual: ");
    ShowCurrentDir();
    for (; args[i] != NULL; i++) ListDirectory(args[i], longFlag, linkFlag, accFlag, hidFlag, recMode);
}


// CUSTOM COMMANDS FOR EASIER SHELL NAVIGATION

void Cmd_clear (char *args[]) {
    const char seq[] = "\033[H\033[2J\033[3J";
    write(STDOUT_FILENO, seq, sizeof(seq) - 1);
}

void Cmd_l (char *args[]) {
    char *largs[] = {"-long", ".", NULL};
    Cmd_list(largs);
}

void Cmd_cd (char *args[]) {
    Cmd_chdir(args);
}
