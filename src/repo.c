#include "../include/repo.h"
#include "../include/commit.h"

// ---------- Repository Initialization ----------
Repository* initRepository() {
    Repository *repo = (Repository*)malloc(sizeof(Repository));
    repo->branches = NULL;
    repo->currentBranch = NULL;
    repo->commitCount = 0;

    // Create master branch
    Branch *master = (Branch*)malloc(sizeof(Branch));
    strcpy(master->name, "master");
    master->head = createCommit(repo->commitCount++, "Initial commit", NULL, NULL);
    master->next = NULL;

    repo->branches = master;
    repo->currentBranch = master;

    printf("Repository initialized with master branch.\n");
    return repo;
}

// ---------- Create Branch ----------
void createBranch(Repository *repo, const char *branchName) {
    Branch *newBranch = (Branch*)malloc(sizeof(Branch));
    strcpy(newBranch->name, branchName);
    newBranch->head = repo->currentBranch->head;  // start from current head
    newBranch->next = repo->branches;
    repo->branches = newBranch;

    printf("Branch '%s' created at commit #%d.\n", branchName, newBranch->head->id);
}

// ---------- Switch Branch ----------
void switchBranch(Repository *repo, const char *branchName) {
    Branch *target = findBranch(repo, branchName);
    if (!target) {
        printf("Branch '%s' not found.\n", branchName);
        return;
    }
    repo->currentBranch = target;
    printf("Switched to branch '%s'.\n", branchName);
}

// ---------- Create Commit ----------
void createCommitInRepo(Repository *repo, const char *message) {
    Commit *parent = repo->currentBranch->head;
    Commit *newCommit = createCommit(repo->commitCount++, message, parent, NULL);
    repo->currentBranch->head = newCommit;

    printf("Commit #%d created on branch '%s'.\n", newCommit->id, repo->currentBranch->name);
}

// ---------- View Commit History ----------
void viewCommitHistory(Repository *repo) {
    printf("\n--- Commit History for Branch '%s' ---\n", repo->currentBranch->name);
    Commit *temp = repo->currentBranch->head;
    while (temp != NULL) {
        printCommit(temp);
        temp = temp->parent1; // traverse backward
    }
    printf("--------------------------------------\n");
}

// ---------- Find Branch ----------
Branch* findBranch(Repository *repo, const char *branchName) {
    Branch *temp = repo->branches;
    while (temp != NULL) {
        if (strcmp(temp->name, branchName) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
