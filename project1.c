#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

void  main()
{
  int i=0;
  int j=0;	
  pid_t pid;
  printf("Enter a number greater than zero:  \n"); 
  scanf("%d", &j);	
  pid = fork();
  if (pid== 0){
     printf("%d\n",j);
     while (j!=1){
	   if (j%2 == 0){
	      j = j/2;
	   }
	   else if (j%2 == 1){
		   j = 3 * (j) + 1;
	   }	
			
           printf("%d\n",j);
     }
		
     printf("Child process is completed.\n");
  }
  else{
     printf("Parent is waiting for child process to complete.\n");
     wait();
     printf("Parent process is completed.\n");
  }
	
}
