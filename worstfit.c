#include <stdio.h>
#define MAX 10

// Best-Fit Memory Allocation Function
void bestfit(int block[], int m, int process[], int n) {
    int allocat[n];  // Stores allocated block index for each process

    // Initialize allocation array (-1 means not allocated)
    for (int i = 0; i < n; i++) {
        allocat[i] = -1;
    }

    // Allocate memory to each process
    for (int i = 0; i < n; i++) {
        int bestidx = -1;

        // Find the best (smallest suitable) block for the process
        for (int j = 0; j < m; j++) {
            if (process[i] <= block[j] && (bestidx == -1 || block[j] < block[bestidx])) {
                bestidx = j;
            }
        }

        // Allocate if a suitable block is found
        if (bestidx != -1) {
            allocat[i] = bestidx;  // Store allocated block index
            block[bestidx] -= process[i];  // Reduce available memory in the block
        }
    }

    // Print Allocation Results
    printf("\nProcess\tSize\tBlock Allocated\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t", i + 1, process[i]);
        if (allocat[i] == -1) {
            printf("Not Allocated\n");
        } else {
            printf("%d\n", allocat[i] + 1);  // Print 1-based block index
        }
    }
}

int main() {
    int block[MAX] = {100, 500, 200, 300, 600};
    int process[MAX] = {212, 417, 112, 426};
    int m = 5, n = 4;

    bestfit(block, m, process, n);
    return 0;
}
