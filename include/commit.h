#ifndef COMMIT_H
#define COMMIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Commit {
    int id;
    char message[100];
    char timestamp[50];
    struct Commit *parent1;
    struct Commit *parent2;  // For merge commits
    struct Commit *next;     // For undo/redo (optional)
} Commit;

// Function prototypes
Commit* createCommit(int id, const char *message, Commit *parent1, Commit *parent2);
void printCommit(Commit *commit);

#endif
