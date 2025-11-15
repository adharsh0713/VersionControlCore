#ifndef GRAPH_H
#define GRAPH_H

#include "commit.h"
#include "repo.h"
#include <stdio.h>
#include <stdlib.h>

// Print the commit graph for all branches
void displayCommitGraph(Repository *repo);

// Recursive visualization helper
void displayCommitNode(Commit *commit, int depth, int *visited, int *vCount);

#endif
