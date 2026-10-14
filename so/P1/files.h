#ifndef FILES_H
#define FILES_H

#define NUM_DESCRIPTORS 20

void InitStdFiles(void);

void ShowFileDescriptors(int limit);

int AddNewFile(int fd, const char *name, int flags);
int RemoveFile(int fd);
int DuplicateFile(int oldfd, int newfd);

#endif //FILES_H
