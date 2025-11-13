#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Generate current timestamp string
void getCurrentTimestamp(char *buffer, size_t size);

// Allocate memory safely and exit if fails
void* safeMalloc(size_t size);

// Trim newline character from strings (used for fgets input)
void trimNewline(char *str);

#endif
