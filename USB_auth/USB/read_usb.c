#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
#define MAX 6
int main() 
{ 
    FILE *fp;
    fp=fopen("/mnt/usb/test.txt", "r"); 
    char buf[MAX]; 
	
    fgets(buf, MAX, fp); 
   printf("Parol: %s\n", buf); 
  
	int fd = open("/proc/ae", O_RDWR);
	//read(fd, buf, 100);
	//puts(buf);
 
	lseek(fd, 0 , SEEK_SET);
	write(fd, buf, MAX);
	
	lseek(fd, 0 , SEEK_SET);
	read(fd, buf, MAX);
	puts(buf);
 return 0; 
} 
