#include "../include/repo.h"
#include "../include/utils.h"

// Initialize Repository
Repository* initRepository() {
    Repository *repo = (Repository*)malloc(sizeof(Repository));
    if (!repo) {
        printf("Memory error\n");
        exit(1);
    }

    repo->allCommits = NULL;
    repo->branches = NULL;
    repo->commitCounter = 1;

    // create root commit
    Commit *root = createCommit(repo->commitCounter++, "Initial commit", NULL, NULL);

    // create master branch
    Branch *master = (Branch*)malloc(sizeof(Branch));
    strcpy(master->name, "master");
    master->head = root;
    master->next = NULL;

    repo->branches = master;
    repo->currentBranch = master;

    // add to allCommits list
    repo->allCommits = root;

    // log initialization 
    logJsonEvent("REPO_INIT", "master", "Repository initialized", -1);

    return repo;
}

// Create Commit
void createCommitInRepo(Repository *repo, const char *message) {
    if (!repo || !repo->currentBranch) {
        printf("Repository error.\n");
        return;
    }

    Commit *parent = repo->currentBranch->head;
    Commit *newCommit = createCommit(repo->commitCounter++, message, parent, NULL);

    // Insert into global commit list
    newCommit->parent = repo->allCommits;
    repo->allCommits = newCommit;

    // Update branch head
    repo->currentBranch->head = newCommit;

    printf("✅ Commit created on branch '%s' with ID #%d\n",
           repo->currentBranch->name, newCommit->id);

    // LOG: Commit created
    char logEntry[256];
    snprintf(logEntry, sizeof(logEntry),
             "Commit #%d created on branch '%s' with message '%s'",
             newCommit->id, repo->currentBranch->name, message);

    logJsonEvent("CREATE_COMMIT", repo->currentBranch->name, message, newCommit->id);
}

// View Commit History
void viewCommitHistory(Repository *repo) {
    if (!repo || !repo->currentBranch) {
        printf("Repository not initialized.\n");
        return;
    }

    printf("\nCommit History for branch [%s]:\n",
           repo->currentBranch->name);
    printf("--------------------------------------\n");

    Commit *current = repo->currentBranch->head;
    while (current) {
        printCommit(current);
        current = current->parent;
    }

    printf("--------------------------------------\n");
}
