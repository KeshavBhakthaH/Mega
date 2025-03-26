#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#define BUFFER_SIZE 1024
// Function to reverse a word
void reverseWord(char *word) {
 int len = strlen(word);
 for (int i = 0; i < len / 2; i++) {
 char temp = word[i];
 word[i] = word[len - i - 1];
 word[len - i - 1] = temp;
 }
}
// Function to reverse words in a string
void reverseWords(char *str) {
 char *word = strtok(str, " ");
 while (word != NULL) {
 reverseWord(word);
 word = strtok(NULL, " ");
 }
}
// Function to count words in a string
int countWords(char *str) {
 int count = 0;
 char *token = strtok(str, " ");
 while (token != NULL) {
 count++;
 token = strtok(NULL, " ");
 }
 return count;
}
int main() {
 int fd1[2], fd2[2]; // Pipes: fd1 for P1 -> P2, fd2 for P2 -> P1
 char inputStr[BUFFER_SIZE], modifiedStr[BUFFER_SIZE];
 if (pipe(fd1) == -1 || pipe(fd2) == -1) {
 perror("Pipe failed");
 return 1;
 }
 pid_t pid = fork();
 if (pid < 0) {
 perror("Fork failed");
 return 1;
 }
 if (pid > 0) { // Parent Process (P1)
 close(fd1[0]); // Close unused read end
 close(fd2[1]); // Close unused write end
 printf("P1: Enter a string: ");
 fgets(inputStr, BUFFER_SIZE, stdin);
 inputStr[strcspn(inputStr, "\n")] = 0; // Remove newline
 write(fd1[1], inputStr, strlen(inputStr) + 1);
 close(fd1[1]); // Close write end
 read(fd2[0], modifiedStr, BUFFER_SIZE);
 printf("P1: Reversed Words: %s\n", modifiedStr);
 close(fd2[0]); // Close read end
 } else { // Child Process (P2)
 close(fd1[1]); // Close unused write end
 close(fd2[0]); // Close unused read end
 read(fd1[0], inputStr, BUFFER_SIZE);
 close(fd1[0]); // Close read end
 char tempStr[BUFFER_SIZE];
 strcpy(tempStr, inputStr);
 int wordCount = countWords(tempStr);
 printf("P2: Word Count = %d\n", wordCount);
 strcpy(tempStr, inputStr); // Restore original string
 reverseWords(tempStr);
 write(fd2[1], tempStr, strlen(tempStr) + 1);
 close(fd2[1]); // Close write end
 }
 return 0;
} 
