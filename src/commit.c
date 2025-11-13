#include "../include/commit.h"

Commit* createCommit(int id, const char *message, Commit *parent1, Commit *parent2) {
    Commit *newCommit = (Commit*)malloc(sizeof(Commit));
    if (!newCommit) {
        printf("Memory allocation failed for commit.\n");
        exit(1);
    }

    newCommit->id = id;
    strcpy(newCommit->message, message);
    time_t t = time(NULL);
    strftime(newCommit->timestamp, sizeof(newCommit->timestamp),
             "%Y-%m-%d %H:%M:%S", localtime(&t));

    newCommit->parent1 = parent1;
    newCommit->parent2 = parent2;
    newCommit->next = NULL;

    return newCommit;
}

void printCommit(Commit *commit) {
    if (commit)
        printf("Commit #%d | %s | %s\n", commit->id, commit->message, commit->timestamp);
}
