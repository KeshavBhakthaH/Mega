#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void splitArray(int arr[], int n, int key, int b[], int *bSize, int c[], int *cSize) {
 *bSize = *cSize = 0;
 for (int i = 0; i < n; i++) {
 if (arr[i] <= key)
 b[(*bSize)++] = arr[i];
 else
 c[(*cSize)++] = arr[i];
 }
}
int main() {
 int fd1[2], fd2[2];
 pipe(fd1);
 pipe(fd2);
 if (fork() == 0) { // Child P2
 close(fd1[1]);
 close(fd2[0]);
 int arr[10], n, key, B[10], C[10], bSize, cSize;
 read(fd1[0], &n, sizeof(int));
 read(fd1[0], arr, sizeof(arr));
 read(fd1[0], &key, sizeof(int));
 close(fd1[0]);
 splitArray(arr, n, key, B, &bSize, C, &cSize);
 write(fd2[1], &bSize, sizeof(int));
 write(fd2[1], B, sizeof(B));
 write(fd2[1], &cSize, sizeof(int));
 write(fd2[1], C, sizeof(C));
 close(fd2[1]);
 exit(0);
 } else { // Parent P1
 close(fd1[0]);
 close(fd2[1]);
 int arr[10], n, key;
 printf("Enter number of elements: ");
 scanf("%d", &n);
 printf("Enter array elements: ");
 for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
 printf("Enter key: ");
 scanf("%d", &key);
 write(fd1[1], &n, sizeof(int));
 write(fd1[1], arr, sizeof(arr));
 write(fd1[1], &key, sizeof(int));
 close(fd1[1]);
 int B[10], C[10], bSize, cSize;
 read(fd2[0], &bSize, sizeof(int));
 read(fd2[0], B, sizeof(B));
 read(fd2[0], &cSize, sizeof(int));
 read(fd2[0], C, sizeof(C));
 close(fd2[0]);
 printf("Subarray B (≤ key): ");
 for (int i = 0; i < bSize; i++) printf("%d ", B[i]);
 printf("\nSubarray C (> key): ");
 for (int i = 0; i < cSize; i++) printf("%d ", C[i]);
 printf("\n");
 }
 return 0;
} 