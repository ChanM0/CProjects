

#include <sys/types.h>
#include <sys/dir.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	pid_t cpid;
	int i = 0;
	int boolean = 0;

	struct dirent **namelist;
	int n;

	struct stat buf;

	int numberOfFiles = 0;

	char cwd[512];
	if(argc < 2){ // uses scan directory if argc is less than 2
		n = scandir(".", &namelist, NULL, alphasort);
		if (n == -1) {
			perror("scandir");
			exit(EXIT_FAILURE);
		}
		//printf("N: %d\n", n);
		numberOfFiles=n;
		boolean = 1;
	 }
	 else{ // use arg c 
	 	numberOfFiles=argc;
	 }


	 for(i=1;i< numberOfFiles;i++){
	 	cpid = fork();
	 	
	 	if (cpid > 0) { // Parent Process
			wait(NULL); // waits till children processes are completed
			system("ps -H");
			exit(0);
		}
		
		else if(cpid == 0){//child   work is done here
			if(boolean == 1){
				while (n--) {
					printf("%s\n", namelist[n]->d_name);
					stat(namelist[n]->d_name, &buf); //assigns file name to buf  
					printf("\nFilename: %s",namelist[n]->d_name); // this is for argc option
					if(getuid() == buf.st_uid){ //checks userid 
						printf("\nI have User Permissions\n");
						if (buf.st_mode & 400){ 
							printf("Read ");
						}
						else{
							printf("Cant Read ");
						}
						if (buf.st_mode & 200){
							printf("Write ");
						}
						else{
							printf("Cant Write ");
						}
						if (buf.st_mode & 100){
							printf("Execute ");
						}
						else{
							printf("Cant Execute ");
						}
					}
					else if (getgid() == buf.st_gid){ //checks group id
						printf("\nI have Group Permissions\n");
						if (buf.st_mode & 40){
							printf("Read ");
						}
						else{
							printf("Cant Read ");
						}
						if (buf.st_mode & 20){
							printf("Write ");
						}
						else{
							printf("Cant Write ");
						}
						if (buf.st_mode & 10){
							printf("Execute ");
						}
						else{
							printf("Cant Execute ");
						}
					}
					else{ // this is for other 
						printf("\nI have General Permissions\n");
						if (buf.st_mode & 4){
							printf("Read " );
						}
						else{
							printf("Cant Read ");
						}
						if (buf.st_mode & 2){
							printf("Write ");
						}
						else{
							printf("Cant Write ");
						}
						if (buf.st_mode & 1){
							printf("Execute ");
						}
						else{
							printf("Cant Execute ");
						}
					}
					printf("\n");
					sleep(1);
				}
				exit(0);
			}
			else{
				stat(argv[i], &buf);
				printf("\nFilename: %s",argv[i]); // this is for 
				if(getuid() == buf.st_uid){ //checks userid 
					printf("\nI have User Permissions\n");
					if (buf.st_mode & 400){ 
						printf("Read ");
					}
					else{
						printf("Cant Read ");
					}
					if (buf.st_mode & 200){
						printf("Write ");
					}
					else{
						printf("Cant Write ");
					}
					if (buf.st_mode & 100){
						printf("Execute ");
					}
					else{
						printf("Cant Execute ");
					}
				}
				else if (getgid() == buf.st_gid){ //checks group id
					printf("\nI have Group Permissions\n");
					if (buf.st_mode & 40){
						printf("Read ");
					}
					else{
						printf("Cant Read ");
					}
					if (buf.st_mode & 20){
						printf("Write ");
					}
					else{
						printf("Cant Write ");
					}
					if (buf.st_mode & 10){
						printf("Execute ");
					}
					else{
						printf("Cant Execute ");
					}
				}
				else{ // this is for other 
					printf("\nI have General Permissions\n");
					if (buf.st_mode & 4){
						printf("Read " );
					}
					else{
						printf("Cant Read ");
					}
					if (buf.st_mode & 2){
						printf("Write ");
					}
					else{
						printf("Cant Write ");
					}
					if (buf.st_mode & 1){
						printf("Execute ");
					}
					else{
						printf("Cant Execute ");
					}
				}
				printf("\n");
				sleep(1);
				exit(0);
			}
		}
			else{
				perror("Fork Failed");
				exit(1); // if fork fails
			}
		}
	
	exit(0);
}