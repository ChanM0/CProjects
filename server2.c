
/*
Most of the code taken from an online source

 A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
   gcc server2.c -lsocket
*/
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netdb.h>

void dostuff(int); /* function prototype */
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen, pid;
     struct sockaddr_in serv_addr, cli_addr;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     while (1) {
         newsockfd = accept(sockfd, 
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0) 
             error("ERROR on accept");
         pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
             dostuff(newsockfd);
             close(newsockfd);
             exit(0);
         }
         else close(newsockfd);

         // close(newsockfd);
         // close(sockfd);
     } /* end of while */
     return 0; /* we never get here */
}

/******** DOSTUFF() *********************
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
void dostuff (int sock)
{
   int n;
   int i =0;

   char buffer[256];

   int incomingNumber;
      
   // this code is what we are suppose to use to read the length of the array; 
    bzero(buffer,256);
   n = read(sock,buffer,255);
   if (n < 0) error("ERROR reading from socket");

  int numberOfInputs = atoi(buffer); // gets size of for loop and array 
   int numbersToBeAdded[numberOfInputs];
   //printf("How many numbers should I add together? : %d\n",atoi(buffer));
 
 //Puts numbers into an array 
  for(i=0;i<numberOfInputs;i++){
    bzero(buffer,256);
    n = read(sock,buffer,256);
    if (n < 0) error("ERROR reading from socket");
    incomingNumber = atoi(buffer);
    numbersToBeAdded[i] = incomingNumber;
    printf("Received number %d: %d\n",i,incomingNumber);
  }
 
//adds numbers together
  int total = 0;
  for(i=0; i<numberOfInputs; i++){
    total = total + numbersToBeAdded[i];
  }
  printf("Here are the numbers added together: %d\n",total);



  //sends message to client side so use this to send like added numbers 
   // n = write(sock,"I got your message",18);
   // if (n < 0) error("ERROR writing to socket");
}
