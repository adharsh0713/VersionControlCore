#include "../include/merge.h"
#include "../include/commit.h"
#include "../include/repo.h"
#include "../include/branch.h"

// ---------- CREATE MERGE COMMIT ----------
Commit* createMergeCommit(Repository *repo, Commit *parent1, Commit *parent2, const char *message) {
    Commit *mergeCommit = createCommit(repo->commitCount++, message, parent1, parent2);
    return mergeCommit;
}

// ---------- MERGE BRANCHES ----------
void mergeBranches(Repository *repo, const char *sourceBranchName, const char *targetBranchName) {
    if (!repo) {
        printf("Error: Repository not initialized.\n");
        return;
    }

    Branch *source = findBranch(repo, sourceBranchName);
    Branch *target = findBranch(repo, targetBranchName);

    if (!source) {
        printf("Source branch '%s' not found.\n", sourceBranchName);
        return;
    }

    if (!target) {
        printf("Target branch '%s' not found.\n", targetBranchName);
        return;
    }

    if (source == target) {
        printf("Cannot merge a branch into itself.\n");
        return;
    }

    printf("Merging branch '%s' into '%s'...\n", sourceBranchName, targetBranchName);

    // Create a merge commit that combines both heads
    Commit *mergeCommit = createMergeCommit(repo, target->head, source->head, "Merge commit between branches");

    target->head = mergeCommit;

    // If current branch is the target, update it too
    if (repo->currentBranch == target)
        repo->currentBranch->head = mergeCommit;

    printf("Merge successful! Created commit #%d linking '%s' and '%s'.\n", mergeCommit->id, targetBranchName, sourceBranchName);
}