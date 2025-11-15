#ifndef REPO_H
#define REPO_H

#include "commit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"   

typedef struct Branch {
    char name[50];
    Commit *head;
    struct Branch *next;
} Branch;

typedef struct Repository {
    Commit *allCommits;       // linked list of all commits
    Branch *branches;         // linked list of branches
    Branch *currentBranch;    // active branch
    int commitCounter;        // auto increment commit IDs
} Repository;

// Initialize repo
Repository* initRepository();

// Create new commit node into current branch
void createCommitInRepo(Repository *repo, const char *message);

// Print commit history
void viewCommitHistory(Repository *repo);

#endif
