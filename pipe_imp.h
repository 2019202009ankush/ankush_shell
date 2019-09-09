
int mp(char *strin[],int c)
{
    int m=2*c,ou,s;
    int fd[m];
    for(int i=0;i<m;i=i+2)
    pipe(fd+i);
    for(int kk=0;kk<c+1;kk++)
    {
        char *tem;
        char *command[10000];
        tem=strtok(strin[kk]," ");
        command[0]=tem;
        int mmm=1;
        for( ; ; )
        {
         if(tem==NULL) break;
        tem=strtok(NULL," ");
        if(tem==NULL)
            break;
        command[mmm]=tem;
        mmm++;
        }
        command[mmm]=NULL;
        if(fork()==0)
        {
            if(kk==0)
            {
                dup2(fd[1],1);
                for(int k=0;k<m;k++) close(fd[k]);
                 execvp(*command, command);
            }
           else if(kk==c)
            {
                dup2(fd[m-2],0);
                for(int k=0;k<m;k++) close(fd[k]);
                 execvp(*command, command);
            }
            else
            {
                dup2(fd[2*kk+1],1);
                dup2(fd[2*(kk-1)],0);
                for(int k=0;k<m;k++) close(fd[k]);
                 execvp(*command, command);
            }
        }
    }
     for(int k=0;k<m;k++) close(fd[k]);
    for(int k=0;k<m-1;k++)
        wait(&s);

}

void outputpipe(char *strin[],char *o,int c)
{
    int m=2*c,ou,s;
    int fd[m];
    for(int i=0;i<m;i=i+2)
    pipe(fd+i);
    ou = open(o,O_WRONLY|O_TRUNC|O_CREAT|O_APPEND,0777);
    for(int kk=0;kk<c+1;kk++)
    {
        char *tem;
        char *command[10000];
        tem=strtok(strin[kk]," ");
        command[0]=tem;
        int mmm=1;
         for( ; ; )
        {
         if(tem==NULL) break;
        tem=strtok(NULL," ");
        if(tem==NULL)
            break;
        command[mmm]=tem;
        mmm++;
        }
        command[mmm]=NULL;
        if(fork()==0)
        {
            if(kk==0)
            {
                dup2(fd[1],1);
                for(int k=0;k<m;k++) close(fd[k]);
                 execvp(*command, command);
            }
           else if(kk==c)
            {
                dup2(fd[m-2],0);
                dup2(ou,1);
                for(int k=0;k<m;k++) close(fd[k]);
                close(ou);
                 execvp(*command, command);
            }
            else
            {
                dup2(fd[2*kk+1],1);
                dup2(fd[2*(kk-1)],0);
                for(int k=0;k<m;k++) close(fd[k]);
                 execvp(*command, command);
            }
        }
    }
     for(int k=0;k<m;k++) close(fd[k]);
     close(ou);
    for(int k=0;k<m-1;k++)
        wait(&s);
}

 
