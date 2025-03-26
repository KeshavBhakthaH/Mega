#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
int sumOfDigits(int num) {
 int sum = 0;
 while (num) {
 sum += num % 10;
 num /= 10;
 }
 return sum;
}
int main() {
 int shmid = shmget(IPC_PRIVATE, 10 * sizeof(int), 0666 | IPC_CREAT);
 int *shm = (int *)shmat(shmid, NULL, 0);
 int numbers[4] = {234, 712, 4562, 8356};
 for (int i = 0; i < 4; i++) shm[i] = numbers[i];
 if (fork() == 0) { // Child P2
 for (int i = 0; i < 4; i++) shm[i + 4] = sumOfDigits(shm[i]);
 exit(0);
 } else {
 wait(NULL);
 printf("Number\tSum of Digits\n");
 for (int i = 0; i < 4; i++)
 printf("%d\t%d\n", shm[i], shm[i + 4]);
 shmdt(shm);
 shmctl(shmid, IPC_RMID, NULL);
 }
 return 0;
}