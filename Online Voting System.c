#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 100
#define MAX_VOTERS 1000
#define CANDIDATE_NAME_LENGTH 50

typedef struct {
    char name[CANDIDATE_NAME_LENGTH];
    int votes;
} Candidate;

void addCandidate(Candidate candidates[], int *numCandidates);
void castVote(Candidate candidates[], int numCandidates);
void displayResults(Candidate candidates[], int numCandidates);

int main() {
    Candidate candidates[MAX_CANDIDATES];
    int numCandidates = 0;
    int choice;

    while (1) {
        printf("\nOnline Voting System\n");
        printf("1. Add Candidate\n");
        printf("2. Cast Vote\n");
        printf("3. Display Results\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCandidate(candidates, &numCandidates);
                break;
            case 2:
                castVote(candidates, numCandidates);
                break;
            case 3:
                displayResults(candidates, numCandidates);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addCandidate(Candidate candidates[], int *numCandidates) {
    if (*numCandidates >= MAX_CANDIDATES) {
        printf("Cannot add more candidates.\n");
        return;
    }

    printf("Enter candidate name: ");
    scanf("%s", candidates[*numCandidates].name);
    candidates[*numCandidates].votes = 0;
    (*numCandidates)++;
    printf("Candidate added successfully.\n");
}

void castVote(Candidate candidates[], int numCandidates) {
    int i, choice;

    if (numCandidates == 0) {
        printf("No candidates available to vote.\n");
        return;
    }

    printf("Candidates:\n");
    for (i = 0; i < numCandidates; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }

    printf("Enter candidate number to vote: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > numCandidates) {
        printf("Invalid candidate number.\n");
    } else {
        candidates[choice - 1].votes++;
        printf("Vote casted successfully.\n");
    }
}

void displayResults(Candidate candidates[], int numCandidates) {
    int i;

    if (numCandidates == 0) {
        printf("No candidates to display.\n");
        return;
    }

    printf("Election Results:\n");
    for (i = 0; i < numCandidates; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }
}
