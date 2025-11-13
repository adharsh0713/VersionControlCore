#include "../include/branch.h"
#include "../include/repo.h"
#include "../include/commit.h"

// ----------- CREATE BRANCH ------------
void createBranch(Repository *repo, const char *branchName) {
    if (!repo) {
        printf("Error: Repository not initialized.\n");
        return;
    }

    // Check if branch already exists
    if (findBranch(repo, branchName)) {
        printf("Branch '%s' already exists.\n", branchName);
        return;
    }

    Branch *newBranch = (Branch*)malloc(sizeof(Branch));
    strcpy(newBranch->name, branchName);
    newBranch->head = repo->currentBranch->head;   // start from current head
    newBranch->next = repo->branches;
    repo->branches = newBranch;

    printf("✅ Branch '%s' created at commit #%d.\n", branchName, newBranch->head->id);
}

// ----------- SWITCH BRANCH ------------
void switchBranch(Repository *repo, const char *branchName) {
    if (!repo) {
        printf("Error: Repository not initialized.\n");
        return;
    }

    Branch *target = findBranch(repo, branchName);
    if (!target) {
        printf("❌ Branch '%s' not found.\n", branchName);
        return;
    }

    repo->currentBranch = target;
    printf("🔀 Switched to branch '%s'.\n", branchName);
}

// ----------- LIST BRANCHES ------------
void listBranches(Repository *repo) {
    if (!repo || !repo->branches) {
        printf("No branches available.\n");
        return;
    }

    printf("\n📂 Existing Branches:\n");
    Branch *temp = repo->branches;
    while (temp != NULL) {
        if (repo->currentBranch == temp)
            printf(" → %s (current)\n", temp->name);
        else
            printf("   %s\n", temp->name);
        temp = temp->next;
    }
    printf("---------------------------\n");
}

// ----------- DELETE BRANCH ------------
void deleteBranch(Repository *repo, const char *branchName) {
    if (!repo || !repo->branches) {
        printf("No branches to delete.\n");
        return;
    }

    Branch *temp = repo->branches;
    Branch *prev = NULL;

    while (temp) {
        if (strcmp(temp->name, branchName) == 0) {
            if (temp == repo->currentBranch) {
                printf("❌ Cannot delete the current active branch.\n");
                return;
            }
            if (prev)
                prev->next = temp->next;
            else
                repo->branches = temp->next;

            free(temp);
            printf("🗑️  Branch '%s' deleted.\n", branchName);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Branch '%s' not found.\n", branchName);
}

// ----------- FIND BRANCH (UTILITY) ------------
Branch* findBranch(Repository *repo, const char *branchName) {
    Branch *temp = repo->branches;
    while (temp != NULL) {
        if (strcmp(temp->name, branchName) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
