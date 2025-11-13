#ifndef BRANCH_H
#define BRANCH_H

#include "commit.h"
#include "repo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------- FUNCTION DECLARATIONS ------------

// Create a new branch starting from current head
void createBranch(Repository *repo, const char *branchName);

// Switch to another branch
void switchBranch(Repository *repo, const char *branchName);

// List all existing branches
void listBranches(Repository *repo);

// Delete a branch (optional, to keep structure clean)
void deleteBranch(Repository *repo, const char *branchName);

// Utility to find branch by name
Branch* findBranch(Repository *repo, const char *branchName);

#endif
