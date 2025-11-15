#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/commit.h"

// ----------------------------------------------------
// Generate timestamp in "YYYY-MM-DD HH:MM:SS" format
// ----------------------------------------------------
void generateTimestamp(char *buffer, int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

// ----------------------------------------------------
// Create a new commit node
// ----------------------------------------------------
Commit* createCommit(int id, const char *message, Commit *parent, Commit *mergeParent) {
    Commit *newCommit = (Commit*)malloc(sizeof(Commit));
    if (!newCommit) {
        printf("❌ Error: Memory allocation failed for Commit.\n");
        return NULL;
    }

    newCommit->id = id;
    strncpy(newCommit->message, message, sizeof(newCommit->message));
    newCommit->message[sizeof(newCommit->message) - 1] = '\0';

    generateTimestamp(newCommit->timestamp, sizeof(newCommit->timestamp));

    newCommit->parent = parent;
    newCommit->mergeParent = mergeParent;

    return newCommit;
}

// ----------------------------------------------------
// Print commit details
// ----------------------------------------------------
void printCommit(const Commit *commit) {
    if (!commit) return;

    printf("\n------------------------------\n");
    printf("Commit ID      : %d\n", commit->id);
    printf("Message        : %s\n", commit->message);
    printf("Timestamp      : %s\n", commit->timestamp);

    if (commit->parent)
        printf("Parent Commit  : %d\n", commit->parent->id);
    else
        printf("Parent Commit  : None\n");

    if (commit->mergeParent)
        printf("Merge Parent   : %d\n", commit->mergeParent->id);

    printf("------------------------------\n");
}
