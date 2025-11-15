#include "../include/graph.h"
#include "../include/commit.h"
#include "../include/repo.h"

// ----- Check if commit was already printed -----
int isVisited(int id, int *visited, int count) {
    for (int i = 0; i < count; i++) {
        if (visited[i] == id)
            return 1;
    }
    return 0;
}

// ----- Recursive DFS to print graph -----
void displayCommitNode(Commit *commit, int depth, int visited[], int *vCount) {
    if (!commit) return;

    for (int i = 0; i < depth; i++) printf("  ");

    printf("Commit %d | %s\n", commit->id, commit->message);

    // main parent
    if (commit->parent)
        displayCommitNode(commit->parent, depth + 1, visited, vCount);

    // merge parent
    if (commit->mergeParent)
        displayCommitNode(commit->mergeParent, depth + 1, visited, vCount);
}

// ----- Entry point to graph visualization -----
void displayCommitGraph(Repository *repo) {
    if (!repo || !repo->branches) {
        printf("Repository is empty.\n");
        return;
    }

    printf("\nCommit Graph Visualization:\n");

    Branch *temp = repo->branches;

    // dynamic visited list (worst case = all commits)
    int visited[1000];
    int visitedCount = 0;

    while (temp != NULL) {
        printf("\nBranch: %s\n", temp->name);
        printf("-----------------------------\n");

        displayCommitNode(temp->head, 0, visited, &visitedCount);

        printf("\n");
        temp = temp->next;
    }
}
