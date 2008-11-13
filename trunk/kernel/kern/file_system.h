#ifndef KERN_FILE_SYSTEM_H_
#define KERN_FILE_SYSTEM_H_
#include <lib/dirent.h>
#include <lib/stat.h>

void file_system_init(void);
int getattr(const char *path, stat *stbuf);
int opendir(const char *name);
dirent *readdir(int fd);
off_t seekdir(int fd, off_t offset);
off_t telldir(int fd);
int closedir(int fd);
int open(const char *path, int flags, mode_t mode);
ssize_t read(int fd, void *buf, size_t count);
off_t lseek(int fd, off_t offset, int whence);
int close(int fd);

#endif /* KERN_FILE_SYSTEM_H_*/
