#ifndef GRAPH_H
#define GRAPH_H

#include "commit.h"
#include "repo.h"
#include <stdio.h>
#include <stdlib.h>

// ----------- FUNCTION DECLARATIONS ------------

// Print all commits in a repository (DAG traversal)
void displayCommitGraph(Repository *repo);

// Recursive helper for visualizing commits
void displayCommitNode(Commit *commit, int depth);

#endif
