#include <stdio.h>
#include <stdlib.h>

int main()
{

   	FILE *fp;//pointer to file
	char word_ok[7];
	char* ok="yes";

	
//	fp = fopen("/mnt/usb/test.txt", "r"); // reading mode to file
	fp = fopen("/proc/rev", "r");

	if (fp == NULL)
   	{
     		printf("Error while opening file.\n");
      		exit(1);//if file doesn't exit or failed to open
   	}	
	
	while(fscanf(fp, "%s",&word_ok) != EOF){ //reding one string from file till the end

		if(strcmp(word_ok, ok) == 0)//returns 0 if string are equal, symbols
		{
			printf("USER AUTHENTICATION APPROVED\n");
		}
		else 
		{
		printf("USER AUTHENTICATION FAILED\n");
		}
	}
	

   fclose(fp); 
  
   return 0;
}
