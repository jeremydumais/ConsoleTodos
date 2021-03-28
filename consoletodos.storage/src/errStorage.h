#ifndef ERRSTORAGE_H
#define ERRSTORAGE_H

const char *getLastStorageError();
void setError(const char *format, ...);

#endif
