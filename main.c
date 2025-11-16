#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/repo.h"
#include "include/branch.h"
#include "include/merge.h"
#include "include/graph.h"
#include "include/utils.h"

// Display menu with current branch
void displayMenu(Repository *repo) {
    printf("\n========= Mini Git Simulation =========\n");
    printf("Current Branch: [%s]\n", repo->currentBranch->name);
    printf("--------------------------------------\n");
    printf("1. Create Commit\n");
    printf("2. View Commit History\n");
    printf("3. Create Branch\n");
    printf("4. Switch Branch\n");
    printf("5. List Branches\n");
    printf("6. Merge Branches\n");
    printf("7. Visualize Commit Graph\n");
    printf("8. Revert to a Specific Commit\n");
    printf("9. Exit\n");
    printf("======================================\n");
    printf("Enter your choice: ");
}

int main() {
    // Initialize repository
    Repository *repo = initRepository();

    // Load previous commits, branches, merges, and reverts from commits.log
    loadRepositoryFromLog(repo, "data/commits.log");

    int choice;
    char message[256];
    char branchName[64];
    char source[64], target[64];

    while (1) {
        displayMenu(repo);

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }
        getchar(); // remove leftover newline

        switch (choice) {
            case 1:
                printf("Enter commit message: ");
                fgets(message, sizeof(message), stdin);
                trimNewline(message);

                if (strlen(message) == 0) {
                    printf("Commit message cannot be empty.\n");
                    break;
                }

                createCommitInRepo(repo, message);
                break;

            case 2:
                viewCommitHistory(repo);
                break;

            case 3:
                printf("Enter new branch name: ");
                fgets(branchName, sizeof(branchName), stdin);
                trimNewline(branchName);

                if (strlen(branchName) == 0) {
                    printf("Branch name cannot be empty.\n");
                    break;
                }

                createBranch(repo, branchName);
                break;

            case 4:
                printf("Enter branch name to switch: ");
                fgets(branchName, sizeof(branchName), stdin);
                trimNewline(branchName);

                if (strlen(branchName) == 0) {
                    printf("Branch name cannot be empty.\n");
                    break;
                }

                switchBranch(repo, branchName);
                break;

            case 5:
                listBranches(repo);
                break;

            case 6:
                printf("Enter source branch (merge FROM): ");
                fgets(source, sizeof(source), stdin);
                trimNewline(source);

                printf("Enter target branch (merge INTO): ");
                fgets(target, sizeof(target), stdin);
                trimNewline(target);

                if (strlen(source) == 0 || strlen(target) == 0) {
                    printf("Branch names cannot be empty.\n");
                    break;
                }

                mergeBranches(repo, source); // merge INTO current branch
                break;

            case 7:
                displayCommitGraph(repo);
                break;

            case 8: {
                int id;
                printf("Enter commit ID to revert to: ");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid commit ID.\n");
                    while (getchar() != '\n');
                    break;
                }
                revertToCommit(repo, id);
                break;
            }

            case 9:
                printf("\nExiting Mini Git Simulation... Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
