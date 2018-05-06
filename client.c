//Most of the code taken from an online source
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <netdb.h>
 #include <strings.h>


void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");



{
    printf("How many numbers should I add together? ");

    bzero(buffer,256); //makes buffer null??
    /*
     The bzero() function writes n zeroed bytes to the string s.  If n is zero,
     bzero() does nothing.
    */
    fgets(buffer,255,stdin);
    /*
    The fgets() function reads at most one less than the number of characters
     specified by size from the given stream and stores them in the string str.
     Reading stops when a newline character is found, at end-of-file or error.
     The newline, if any, is retained.  If any characters are read and there is
     no error, a `\0' character is appended to end the string.
    */
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) {
         error("ERROR writing to socket");
     }

 }
    int numberOfInputs = atoi(buffer);
    int i = 0;
    for(i=0; i< numberOfInputs; i++){
        printf("\n Enter a number: " );
         bzero(buffer,256);
         fgets(buffer,255,stdin);
         n = write(sockfd,buffer, strlen(buffer));
        if (n < 0) {
         error("ERROR writing to socket");
     }
    }  
    //gets message from server 
    // {
    // bzero(buffer,256); // makes buffer null
    // n = read(sockfd,buffer,255); // reads from server 
    // if (n < 0) {
    //      error("ERROR reading from socket");
    //  }
    // printf("%s\n",buffer); //prints string
    // }
    return 0;
}
