#include <stdio.h>
 #include <stdlib.h>
  
void setrc() {
      FILE *fp = fopen(".mybashrc.txt", "r");
      if(fp == NULL) {
          perror("Unable to open file!");
          exit(1);
    }
    char chunk[128]; 
    fgets(chunk, sizeof(chunk), fp);
    setenv("HOME",chunk,1);
    fgets(chunk, sizeof(chunk), fp);
    setenv("PATH",chunk,1);
    fgets(chunk, sizeof(chunk), fp);
    setenv("USER",chunk,1);
    fgets(chunk, sizeof(chunk), fp);
    setenv("HOSTNAME",chunk,1);
    fgets(chunk,sizeof(chunk),fp);
    setenv("PS1",chunk,1);
     fclose(fp);
}
