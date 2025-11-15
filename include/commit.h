#ifndef COMMIT_H
#define COMMIT_H

#include <time.h>

// ----------------------------
// Commit Node Structure
// ----------------------------
typedef struct Commit {
    int id;                        // Unique commit ID
    char message[256];             // Commit message
    char timestamp[64];            // Timestamp string
    struct Commit *parent;         // Points to previous commit (main parent)
    struct Commit *mergeParent;    // Used when merges occur
} Commit;

// ----------------------------
// Commit Function Prototypes
// ----------------------------

// Allocate and initialize a new commit node
Commit* createCommit(int id, const char *message, Commit *parent, Commit *mergeParent);

// Generate timestamp for commits
void generateTimestamp(char *buffer, int size);

// Print commit details (debug / display)
void printCommit(const Commit *commit);

#endif
