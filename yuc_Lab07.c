#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define SizeLine 100

int main(int argc, char **argv) {
    pid_t pid;
    int status;
    char Line[SizeLine];
    char Exute[100] = "/usr/bin/";
    char *starttime, *endtime;

    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }


    FILE *testfile = NULL;
    testfile = fopen(argv[1],"r");
    FILE *log = NULL;
    log = fopen("output.log", "w");
    fclose(log);


    if (testfile == NULL)
        {
        printf("error in read\n");
        exit (-1);
        }

    int count;
    char Argument[100], Commend[100];
    double getstart, getend;

    while (fgets(Line, SizeLine, testfile) != NULL)
    {

	if(Line[strlen(Line) - 1] == '\n'){
		Line[strlen(Line) - 1] = '\0';
	}


	FILE *log = NULL;
	log = fopen("output.log", "a");

	time_t start = time(NULL);
	starttime = ctime(&start);
	//printf("Ctime---starttime =  %s",starttime);
	fprintf(log,"%s  %s ", Line, starttime);


	pid = fork();

	if (pid == 0) { /* this is child process */

		//printf("from child\n");


                if(strstr(Line,"/") == NULL){
                        strcat(Exute,Line);
                        strcpy(Line,Exute);
//                      printf("EXE =  %s\n",Line);
                }

		//printf("%s\n",Line);

		if(strstr(Line," ") != NULL){
			char * token = strtok(Line, " ");
			strcpy(Commend,token);
			token = strtok(NULL," ");
			strcpy(Argument,token);
		}
		else{
			strcpy(Commend,Line);
		}

		//printf("commend = %s\n",Commend);
		//printf("Argument = %s\n", Argument);

		if(strcmp(Argument,"") != 0){
                	execl(Commend, Commend, Argument,(char *)NULL);
	      		perror("execl");
		}
		else{
			//printf("hi\n");
                	execl(Commend, Commend, (char *)NULL);
                	perror("execl");
	        }
	       	perror("execl");
		exit(-1);

	} else if (pid > 0) { /* this is the parent process */
        	//printf("Wait for the child process to terminate\n");
        	wait(&status); /* wait for the child process to terminate */
		time_t end = time(NULL);
		endtime = ctime(&end);
		//printf("Ctime---endtime = %s\n", endtime);
		//printf("Commend = %s\n",Line);

		fprintf(log,"%s\n", endtime);
		fclose(log);

		if (WIFEXITED(status)) { /* child process terminated normally */
        	    //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        	} else { /* child process did not terminate normally */
        	    printf("Child process did not terminate normally!\n");
            	/* look at the man page for wait (man 2 wait) to determine
               	how the child process was terminated */
        	}
	} else { /* we have an error */
        	perror("fork"); /* use perror to print the system error message */
        	exit(EXIT_FAILURE);
    	}


    }

    fclose(testfile);


/*	if(strcmp(Argument[0],"") != 0){
                execl(Commend[0], Commend[0], Argument[0],(char *)NULL);
               	perror("execl");
        }
        else{
                execl(Commend[2], Commend[2], (char *)NULL);
                perror("execl");
        }

*/

    return 0;
}
