#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include "basic.h"
#include "ioredirect.h"
#include "pipe_imp.h"
#include "bashrc.h"
using namespace std;
char global[10000];
void prints()
{
	string u=getenv("USER");
        string h=getenv("HOSTNAME");
        string ps=getenv("PS1");
	u[u.size()-1]='\0';
        h[h.size()-1]='\0';
	ps[ps.size()-1]='\0';
        cout<<endl<<u<<"@"<<h<<ps;
}
int main()
{
    getcwd(global,sizeof(global));
    setrc();
    const char * h=getenv("HOME");
    prints();
    char command[10000];  
    while(fgets(command,10000,stdin)!=NULL)
	{
            char *temp;
            char *temstring[10000];
            int len=strlen(command);
            
            FILE * fp= fopen("log.txt","a+");
            fputs(command,fp);
            fclose(fp);
           
            command[strlen(command)-1]='\0';
            if(strstr(command,"history"))
            {FILE *fp=fopen("log.txt","r");
                if (fp!= NULL)
                {char buff [ 10000 ];
                 int i=1;
                    while(fgets(buff,sizeof buff,fp)!=NULL)
                    {
                        printf("%3d. ",i);
                        fputs ( buff, stdout );
                        i++;
                    }
                fclose (fp);
               }
            }
            if(strstr(command,"cd")) 
            {
                temp=strtok(command," ");
                temp=strtok(NULL," ");
                if(temp!=NULL&&!strstr(temp,"~"))
                {
                 chdir(temp);
                 getcwd(global,sizeof(global));
                }
                else if(temp==NULL||strstr(temp,"~"))
                 {
                    //cout<<"in line h="<<h<<endl;
                    chdir(h);
                    getcwd(global,sizeof(global));
                 }
             goto l2;
            }
            if(strstr(command,"exit"))
            {
                exitfromshell();
		exit(0);
            }
            if(strstr(command,"echo"))
            {
                if(strstr(command,"$")&&!strstr(command,"$$"))
                {
                   temp=strtok(command,"$");
                    temp=strtok(NULL,"$");
                    cout<<getenv(temp);
                   goto l2;
                }
               else if(strstr(command,"$")&&strstr(command,"$$"))
               {
                 cout<<getpid();
                 
                 goto l2;
               }
                 
            }
            if(strstr(command,">>"))
           {
              if(!strstr(command,"|")){
                   temp=strtok(command,">>");
                    temstring[0]=temp;
                    temp=strtok(NULL,">>");
                    temstring[1]=temp;
                    dualoutp(temstring[0],temstring[1]);
             }
             else
             {
              char *ss;
              int i=1;
              temp=strtok(command,"|");
              temstring[0]=temp;
              while(temp!=NULL)
              {
                 temp=strtok(command,"|");
                 if(temp==NULL)
                   break;
                 temstring[i]=temp;
                 i=i+1;
               }
                    char *temp=temstring[i-1];
                    char *hg=strtok(temp,">>");
                    temstring[i-1]=hg;
                    hg=strtok(NULL,">>");
                    ss=hg;
                    outputpipedual(temstring,ss,i-1);
                    goto l2;
               
           }
         
      }
           else if(strstr(command,">"))
            {
               // cout<<"in >"<<endl;
                if(!strstr(command,"|"))
                {
                    temp=strtok(command,">");
                    temstring[0]=temp;
                    temp=strtok(NULL,">");
                    temstring[1]=temp;
                    outp(temstring[0],temstring[1]);
                }
                 else
                 {
                  char *ou;
                  int i=1;
                  temp=strtok(command,"|");
                  temstring[0]=temp;
                     //cout<<"in > | "<<endl;
                    while(temp!=NULL)
                    {
                    temp=strtok(NULL,"|");
                    if(temp==NULL)
                        break;
                    temstring[i]=temp;
                    i++;
                    }
                      //cout<<"in > | |"<<endl;
                    char *temp=temstring[i-1];
                    char *hg=strtok(temp,">");
                    temstring[i-1]=hg;
                    hg=strtok(NULL,">");
                    ou=hg;
                    outputpipe(temstring,ou,i-1);
                    goto l2;
                }
               
            }
           else if(strstr(command,"|"))
            {
                temp=strtok(command,"|");
                temstring[0]=temp;
                int i=1;
                while(temp!=NULL)
                {temp=strtok(NULL,"|");
                 if(temp==NULL)break;
                    temstring[i]=temp;
                    i++;
                }
                mp(temstring,i-1);
           }
          
           else
           {if(!strstr(command,"exit")&&!strstr(command,"history")&&!strstr(command,"cd"))
                 {
                         temstring[0]=command;
                         BasicEx(temstring[0]);
                         goto l2;
                 }
           }
       
         l2 : prints();

	}
}