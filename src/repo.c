#include "../include/repo.h"
#include "../include/utils.h"
#include <sys/stat.h>
#include <ctype.h>

// ----------------- Helper -----------------
int fileExists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

// ----------------- Repository Init -----------------
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
    repo->allCommits = root;

    // Log REPO_INIT only if commits.log doesn't exist
    if (!fileExists("data/commits.log")) {
        logJsonEvent("REPO_INIT", "master", "Repository initialized", -1);
    }

    return repo;
}

// ----------------- Create Commit -----------------
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

    printf("Commit created on branch '%s' with ID #%d\n", repo->currentBranch->name, newCommit->id);

    logJsonEvent("CREATE_COMMIT", repo->currentBranch->name, message, newCommit->id);
}

// ----------------- View Commit History -----------------
void viewCommitHistory(Repository *repo) {
    if (!repo || !repo->currentBranch) {
        printf("Repository not initialized.\n");
        return;
    }

    printf("\nCommit History for branch [%s]:\n", repo->currentBranch->name);
    printf("--------------------------------------\n");

    Commit *current = repo->currentBranch->head;
    while (current) {
        printCommit(current);
        current = current->parent;
    }

    printf("--------------------------------------\n");
}

// ----------------- Revert to Commit -----------------
void revertToCommit(Repository *repo, int commitId) {
    if (!repo || !repo->currentBranch) {
        printf("Repository or branch not initialized!\n");
        return;
    }

    Branch *branch = repo->currentBranch;
    Commit *head = branch->head;

    // Step 1: Find target commit in ancestry
    Commit *target = head;
    while (target != NULL && target->id != commitId) {
        target = target->parent;
    }

    if (target == NULL) {
        printf("Commit ID %d not found in current branch history!\n", commitId);
        return;
    }

    // Step 2: Free commits after target
    Commit *node = head;
    while (node != target) {
        Commit *prev = node->parent;
        free(node);
        node = prev;
    }

    // Step 3: Move HEAD to target
    branch->head = target;

    // Step 4: Log REVERT
    char msg[256];
    snprintf(msg, sizeof(msg), "Reverted branch '%s' to commit #%d", branch->name, commitId);
    logJsonEvent("REVERT", branch->name, msg, commitId);

    printf("Branch '%s' reverted to commit ID %d.\n", branch->name, commitId);
}

// ----------------- Helper: simple JSON field extractor -----------------
void extractJsonString(const char *line, const char *field, char *output, size_t size) {
    output[0] = '\0';
    const char *pos = strstr(line, field);
    if (!pos) return;
    pos = strchr(pos, ':'); // move to colon
    if (!pos) return;
    pos++; // skip colon
    while (*pos && (isspace(*pos) || *pos == '"')) pos++;
    size_t i = 0;
    while (*pos && *pos != '"' && i < size - 1) {
        output[i++] = *pos++;
    }
    output[i] = '\0';
}

int extractJsonInt(const char *line, const char *field) {
    const char *pos = strstr(line, field);
    if (!pos) return -1;
    pos = strchr(pos, ':');
    if (!pos) return -1;
    return atoi(pos + 1);
}

// ----------------- Load Repository from Log -----------------
void loadRepositoryFromLog(Repository *repo, const char *logFilePath) {
    FILE *f = fopen(logFilePath, "r");
    if (!f) return;

    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        trimNewline(line);

        char event[50], branchName[50], message[256];
        int commitId;

        extractJsonString(line, "\"event\"", event, sizeof(event));
        extractJsonString(line, "\"branch\"", branchName, sizeof(branchName));
        extractJsonString(line, "\"message\"", message, sizeof(message));
        commitId = extractJsonInt(line, "\"commit\"");

        if (strcmp(event, "REPO_INIT") == 0) {
            continue;
        } 
        else if (strcmp(event, "CREATE_COMMIT") == 0) {
            Branch *b = findBranch(repo, branchName);
            if (!b) {
                b = (Branch*)malloc(sizeof(Branch));
                strcpy(b->name, branchName);
                b->head = NULL;
                b->next = repo->branches;
                repo->branches = b;
            }
            Commit *parent = b->head;
            Commit *newCommit = createCommit(commitId, message, parent, NULL);
            newCommit->parent = repo->allCommits;
            repo->allCommits = newCommit;
            b->head = newCommit;
            if (commitId >= repo->commitCounter) repo->commitCounter = commitId + 1;
        }
        else if (strcmp(event, "REVERT") == 0) {
            Branch *b = findBranch(repo, branchName);
            if (!b) continue;

            Commit *target = b->head;
            while (target && target->id != commitId) {
                target = target->parent;
            }
            if (!target) continue;

            Commit *node = b->head;
            while (node != target) {
                Commit *prev = node->parent;
                free(node);
                node = prev;
            }
            b->head = target;
        }
        else if (strcmp(event, "MERGE") == 0) {
            // Optional: reconstruct mergeParent if desired
        }
    }

    fclose(f);
}
