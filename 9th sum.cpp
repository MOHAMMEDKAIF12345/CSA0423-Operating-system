#include <stdio.h>
#include <unistd.h>

int main() 
{
pid_t pid, ppid;
pid = fork();
if (pid < 0) {
printf("Fork failed\n");
return 1;
}
if (pid == 0) {
printf("This is the child process\n");
printf("Child process ID: %d\n", getpid());
printf("Child's parent process ID: %d\n", getppid());
} else {
printf("This is the parent process\n");
printf("Parent process ID: %d\n", getpid());
printf("Parent's parent process ID: %d\n", getppid());
}
return 0;
}
