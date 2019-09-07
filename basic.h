#include "myheader.h"
int BasicEx(char *strin)
{int count=1,st;
    char *temp=strtok(strin," ");
    char *command[100];
    command[0]=temp;
    while(temp!=NULL)
    {
temp=strtok(NULL," ");
        if(temp==NULL)
            break;
        command[count]=temp;
        count++;
    }
    command[count]=NULL;
    if(fork()==0)
    {
        execvp(*command,command);
        fprintf(stderr," %s is invalid command\n",*command);
    }
    else
    {
          wait(&st);
    }
}
void exitfromshell()
{
                printf("good bye\n");
                
}
