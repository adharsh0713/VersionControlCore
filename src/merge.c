#include "../include/merge.h"
#include <stdio.h>

Commit* createMergeCommit(Repository *repo, const char *message, Commit *parent, Commit *mergeParent) {
    return createCommit(repo->commitCounter++, message, parent, mergeParent);
}

void mergeBranches(Repository *repo, const char *sourceBranchName) {
    Branch *src = repo->branches;
    while (src && strcmp(src->name, sourceBranchName) != 0)
        src = src->next;

    if (!src) {
        printf("Branch not found.\n");
        return;
    }

    Commit *targetHead = repo->currentBranch->head;
    Commit *sourceHead = src->head;

    Commit *mergeCommit = createMergeCommit(repo, "Merge commit", targetHead, sourceHead);

    mergeCommit->parent = targetHead;
    mergeCommit->mergeParent = sourceHead;

    repo->currentBranch->head = mergeCommit;

    logJsonEvent(
        "MERGE",
        repo->currentBranch->name,
        "Merged branch",
        mergeCommit->id
    );
}
