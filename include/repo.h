#ifndef REPO_H
#define REPO_H

#include "commit.h"  // Commit structure
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------- STRUCT DEFINITIONS ------------

typedef struct Branch {
    char name[50];
    struct Commit *head;     // Latest commit in this branch
    struct Branch *next;     // For maintaining a linked list of branches
} Branch;

typedef struct Repository {
    Branch *branches;        // Linked list of all branches
    Branch *currentBranch;   // Active branch
    int commitCount;         // For assigning unique commit IDs
} Repository;

// ----------- FUNCTION DECLARATIONS ------------

// Initialize an empty repository with a master branch
Repository* initRepository();

// Create a new branch
void createBranch(Repository *repo, const char *branchName);

// Switch between branches
void switchBranch(Repository *repo, const char *branchName);

// Create a new commit in the current branch
void createCommitInRepo(Repository *repo, const char *message);

// Display commit history of the current branch
void viewCommitHistory(Repository *repo);

// Utility to find a branch by name
Branch* findBranch(Repository *repo, const char *branchName);

#endif
