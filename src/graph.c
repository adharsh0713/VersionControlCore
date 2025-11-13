#include "../include/graph.h"
#include "../include/commit.h"
#include "../include/repo.h"

// Helper function to avoid visiting same commit twice
int isVisited(int id, int *visited, int count) {
    for (int i = 0; i < count; i++)
        if (visited[i] == id)
            return 1;
    return 0;
}

// Recursive DFS visualization
void displayCommitNode(Commit *commit, int depth) {
    if (!commit)
        return;

    // Indentation for depth
    for (int i = 0; i < depth; i++)
        printf("   ");

    printf("• Commit #%d: %s\n", commit->id, commit->message);

    // If merge commit, show both parents
    if (commit->parent2) {
        for (int i = 0; i < depth + 1; i++)
            printf("   ");
        printf("↳ Merge parents: #%d and #%d\n",
               commit->parent1 ? commit->parent1->id : -1,
               commit->parent2 ? commit->parent2->id : -1);
    }

    // Recurse on parent(s)
    if (commit->parent1)
        displayCommitNode(commit->parent1, depth + 1);

    if (commit->parent2)
        displayCommitNode(commit->parent2, depth + 1);
}

// Main visualization entry
void displayCommitGraph(Repository *repo) {
    if (!repo || !repo->branches) {
        printf("Repository is empty.\n");
        return;
    }

    printf("\nCommit Graph Visualization:\n");

    Branch *temp = repo->branches;
    while (temp != NULL) {
        printf("\nBranch: %s\n", temp->name);
        printf("-----------------------------\n");
        displayCommitNode(temp->head, 0);
        printf("\n");
        temp = temp->next;
    }
}
