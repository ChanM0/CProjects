/*
Proejct Requirments

Parent Processes
	Parent Process should wait till children are finished
		So I will use wait(NULL)
	Parent Processes then must call
		system("ps -H");
Children Process
	Children must do all the work
		So input must go here
			Needs to be able to take either filename or wild card as input
	Create as many Child Processes as their are files
		Maybe add another fork
		then add a for loop to itterate till all files are read
		Or add for loop then add a fork?
		print filename and pid here
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{

	size_t readlen, writelen, slen;
	pid_t cpid, mypid, cpid2;
	pid_t pid = getpid(); /* get current processes PID */
//	printf("Parent pid: %d\n", pid);

	int i =0;

	cpid = fork(); //forks the childs processes

	if (cpid > 0) { // Parent Process
//		sleep(1);
		wait(NULL); // waits till children processes are completed
		mypid = getpid();//gets pid
		printf("\n CHILD FINISHED");
		system("ps -H");
		exit(0);
	}

	 else if (cpid == 0) { // Child Process
		mypid = getpid();
//		printf("\n [%d] child\n", mypid);

		//argc is argument count
		//arg v is a one dimensional array of strings
		for(i=0;i<argc ;i++){

			cpid2=fork();


			pid_t currentChildPid = getpid();

/*			if(cpid2 > 0) {//parent
				wait(NULL);
				exit(0);
			}


			else */ if(cpid2 == 0) {//child
			//work is done here
//sleep(1);
				printf("\n Filename: %s",argv[i]);  //prints file name works because its a string
				printf("   PID: %d \n",currentChildPid);
				exit(0);
			}
/*
			else{
			printf("ERROR IN SECOND CHILD PROCESS");
			exit(1);

			}
*/
		}
		exit(0);
	}
	 else {

		perror("Fork failed");
		exit(1);
	}
	exit(0);
}
