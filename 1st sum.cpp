#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h>
main(int argc, char *argv[])
{
int fd, n, len; 
char buf[100],name[30];
printf("enter the file name");
scanf("%s",&name);
fd = open(name, O_WRONLY|O_CREAT|O_TRUNC, 0644); 
if(fd < 0)
{
printf("File creation problem\n"); 
exit(-1);
}
printf("Press Ctrl+D at end in a new line:\n"); 
while((n = read(0, buf, sizeof(buf))) > 0)
{
len = strlen(buf); 
write(fd, buf, len);
}
close(fd);
}
