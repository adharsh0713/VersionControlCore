#ifndef MERGE_H
#define MERGE_H

#include "repo.h"
#include "branch.h"
#include "commit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------- FUNCTION DECLARATIONS ------------

// Merge sourceBranch into targetBranch
void mergeBranches(Repository *repo, const char *sourceBranchName, const char *targetBranchName);

// Internal helper to create a merge commit node
Commit* createMergeCommit(Repository *repo, Commit *parent1, Commit *parent2, const char *message);

#endif
