#include <stdio.h>
#include <string.h>
#include <errno.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <unistd.h>
#include<sys/stat.h>
#include<sys/types.h>


int main (int i, char *j[]) {

    int pipep[5]; 
    char chdBuffer[150];
    int filelength;
    char buffer[150];

    if (i != 3) {
      perror("filecopy: copied input.txt to copy.txt. \n");
      exit(1);
    } 
    char* SourceFile= j[1];
    char* DestinationFile = j[2];
    if (pipe(pipep) < 0) {
      printf("An error creating the pipe. %s\n", strerror(errno));
      exit(1);
    }
    switch(fork()) {
      case -1:
        printf("An error on forking child process. %s\n", strerror(errno));
        exit(1);
     case 0: 
        close(pipep[1]);                                                       
        ssize_t child = read(pipep[0], chdBuffer, sizeof(chdBuffer));   
        close(pipep[0]);                                                        
        int dstFile = open(DestinationFile, O_CREAT | O_WRONLY);                                  
        write(dstFile, chdBuffer, child);                            
      default: 
        close(pipep[0]);                                              
        int read_file = open(SourceFile, O_RDONLY);                       
        ssize_t bytes = read(read_file, buffer, sizeof(buffer));   
        write(pipep[1], buffer, bytes);                           
        close(pipep[1]);                                              
    }
    return 0;
}

