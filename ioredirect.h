
void outp(char *str1,char *str2)
{
    int count=1,st;
    char *temp=strtok(str1," ");
    char *command[1000];
    command[0]=temp;
//cout<<"befor1"<<" "<<str1<<" "<<str2<<endl;
    for(; ;)
    {
        if(temp==NULL) break;
        temp=strtok(NULL," ");
        if(temp==NULL)
            break;
        command[count]=temp;
        count++;
    }
    command[count]=NULL;
    
    int op;
    int f = fork();
    //cout<<"befor"<<endl;
    op = open(str2, O_WRONLY | O_TRUNC | O_CREAT|O_APPEND,0777);
    //cout<<"after"<<endl;
    if (f == 0)
    {
        dup2(op,1);
        close(op);
        //cout<<command[1]<<endl;
        execvp(*command,command);
	exit(0);
    }
   else wait(&st);
  close(op);
}
void dualoutp(char *str1,char *str2)
{
    int count=1,st;
    char *temp=strtok(str1," ");
    char *command[1000];
    command[0]=temp;//cout<<"befor1"<<" "<<str1<<" "<<str2<<endl;
    for( ; ; )
    {
         if(temp==NULL) break;
        temp=strtok(NULL," ");
        if(temp==NULL)
            break;
        command[count]=temp;
        count++;
    }
    command[count]=NULL;
    
    int op;
    int f = fork();
    //cout<<"befor"<<endl;
    op = open(str2, O_WRONLY|O_APPEND|O_CREAT,0777);
    //cout<<"after"<<endl;
    if (f == 0)
    {dup2(op,1);
        close(op);
        //cout<<command[1]<<endl;
        execvp(*command,command);
	exit(0);
    }
    else wait(&st);
close(op);
}

