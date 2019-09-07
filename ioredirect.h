
int outp(char *str1,char *str2)
{
    int i=1,st;
    char *temp=strtok(str1," ");
    char *command[100];
    command[0]=temp;
//cout<<"befor1"<<" "<<str1<<" "<<str2<<endl;
    while(temp!=NULL)
    {
        temp=strtok(NULL," ");
        if(temp==NULL)
            break;
        command[i]=temp;
        i++;
    }
    command[i]=NULL;
    char *dest=str2;
    //cout<<dest<<endl;
    int out;
    int f = fork();
    //cout<<"befor"<<endl;
    out = open(dest, O_WRONLY | O_TRUNC | O_CREAT|O_APPEND,0777);
    //cout<<"after"<<endl;
    if (f == 0)
    {
        dup2(out,1);
        close(out);
        //cout<<command[1]<<endl;
        execvp(*command,command);
	exit(0);
    }
   else wait(&st);
  close(out);
}
int dualoutp(char *str1,char *str2)
{
    int i=1,st;
    char *temp=strtok(str1," ");
    char *command[100];
    command[0]=temp;//cout<<"befor1"<<" "<<str1<<" "<<str2<<endl;
    while(temp!=NULL)
    {
        temp=strtok(NULL," ");
        if(temp==NULL)
            break;
        command[i]=temp;
        i++;
    }
    command[i]=NULL;
    char *dest=str2;
    //cout<<dest<<endl;
    int out;
    int f = fork();
    //cout<<"befor"<<endl;
    out = open(dest, O_WRONLY|O_APPEND|O_CREAT,0777);
    //cout<<"after"<<endl;
    if (f == 0)
    {dup2(out,1);
        close(out);
        //cout<<command[1]<<endl;
        execvp(*command,command);
	exit(0);
    }
    else wait(&st);
close(out);
}

