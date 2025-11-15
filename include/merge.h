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
void mergeBranches(Repository *repo, const char *sourceBranchName);

// Internal helper to create a merge commit node
Commit* createMergeCommit(Repository *repo, const char *message, Commit *parent, Commit *mergeParent);

#endif
