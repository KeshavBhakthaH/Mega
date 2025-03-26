#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);

    if (fork() == 0) { // Child P2
        close(fd1[1]); // Close writing end of fd1
        int nums[5], posNums[5], count = 0;
        
        read(fd1[0], nums, sizeof(nums));
        close(fd1[0]); // Close reading end of fd1
        
        // Filter positive numbers
        for (int i = 0; i < 5; i++) {
            if (nums[i] >= 0) posNums[count++] = nums[i];
        }

        close(fd2[0]); // Close reading end of fd2
        write(fd2[1], posNums, count * sizeof(int)); // Write only valid numbers
        close(fd2[1]); // Close writing end of fd2
        
        exit(0);
    } 
    else if (fork() == 0) { // Child P3
        close(fd2[1]); // Close writing end of fd2
        int posNums[5], sum = 0, bytesRead;
        
        bytesRead = read(fd2[0], posNums, sizeof(posNums));
        close(fd2[0]); // Close reading end of fd2

        int count = bytesRead / sizeof(int); // Number of integers received
        for (int i = 0; i < count; i++) {
            sum += posNums[i];
        }

        printf("Sum of positive numbers: %d\n", sum);
        exit(0);
    } 
    else { // Parent P1
        close(fd1[0]); // Close reading end of fd1
        int nums[5] = {-2, 5, -9, 3, 8};

        write(fd1[1], nums, sizeof(nums)); // Send numbers to P2
        close(fd1[1]); // Close writing end of fd1

        wait(NULL); // Wait for child P2
        wait(NULL); // Wait for child P3
    }

    return 0;
}
