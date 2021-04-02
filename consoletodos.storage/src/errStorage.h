#ifndef ERRSTORAGE_H
#define ERRSTORAGE_H

/**
 * @brief Get the last storage error string from the storage module
 * 
 * @return The last error message as a const char* 
 */
const char *getLastStorageError();

/**
 * @brief Set the last error message object. The value from format and the
 * other arguments will be pass to the internal vsnprintf function.
 * 
 * @param format the same format as printf from stdio.h
 * @param ... all the values related to the format string
 */
void setError(const char *format, ...);

#endif
