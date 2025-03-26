#include <stdio.h>

// Function to perform Best-Fit Memory Allocation
void BestFIT(int Block[], int sB, int Process[], int sP) {
    int allocate[sP];

    // Initialize allocation array to -1 (indicating not allocated)
    for (int i = 0; i < sP; i++)
        allocate[i] = -1;

    // Iterate over each process
    for (int i = 0; i < sP; i++) {
        int bestindex = -1;

        // Find the best (smallest suitable) block for the process
        for (int j = 0; j < sB; j++) {
            if (Process[i] <= Block[j] && (bestindex == -1 || Block[j] < Block[bestindex])) {
                bestindex = j;
            }
        }

        // Allocate memory if a suitable block is found
        if (bestindex != -1) {
            allocate[i] = bestindex;
            Block[bestindex] -= Process[i];  // Reduce available block size
        }
    }

    // Print allocation results
    printf("\nProcess\tSize\tBlock\n");
    for (int i = 0; i < sP; i++) {
        printf("%d\t%d\t", i + 1, Process[i]);
        if (allocate[i] == -1)
            printf("Not allocated\n");
        else
            printf("%d\n", allocate[i] + 1);
    }
}

int main() {
    int sB, sP;

    // Input number of memory blocks
    printf("Enter the number of blocks: ");
    scanf("%d", &sB);
    int Block[sB];

    // Input block sizes
    for (int i = 0; i < sB; i++) {
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &Block[i]);
    }

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &sP);
    int Process[sP];

    // Input process sizes
    for (int i = 0; i < sP; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &Process[i]);
    }

    // Call Best-Fit function
    BestFIT(Block, sB, Process, sP);

    return 0;
}
