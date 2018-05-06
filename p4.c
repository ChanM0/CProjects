#include <unistd.h>
#include <sys/dir.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>

void randomwait();
void barber_run();
void customer_run();

int seats[2];
int customers[2];
int barber[2];
int freeseats[2];



void V(int pd[]) {
/*	
an atomic operation that increments the
semaphore by 1, waking up a waiting P, if any
» This of this as the signal() operation
*/
	int a=1;
	write(pd[1],&a,sizeof(int));
}

void P(int pd[]) {
/*
an atomic operation that waits for semaphore to
become greater than zero, then decrements it by 1
» Think of this as the wait() operation
*/
	int a;
	read(pd[0],&a,sizeof(int));
}

void main() {
	pipe(seats); // lock to modify freeseats
	pipe(customers); // how many customers are waiting for the barber
	pipe(barber); // barber ready to cut?  0=no 1=yes	
	
	pipe(freeseats); // store the integer value for number of seats
	
	V(seats); // release the lock on seats by setting to 1
	
	int num=3; // Free Seats = 3
	write(freeseats[1],&num,sizeof(int));
	
	if (fork() == 0) {  // Start 1 barber
		srand(time(0)+11); // Randomized seed
		barber_run();
		return;
	}
	int i;
	for (i=1;i<=10;i++) { // Start 10 customers randomly
		if (fork() == 0) {
			randomwait(i); // random wait before next customer arrives
			srand(time(0)+ i); // different seed than barber for different delays
			customer_run();
			return;
		}
	}
}

void barber_run() {
	int num,i;
	for (i=1;i<11;++i) { // at most 10 customers will get their hair cut

		P(customers); //locks customers
		 // gets customer, which decrements the number of customers i think
		
		P(seats); // locks seats
		printf("Barber %d is trying to get a customer\n",i);
		printf("Barber %d is waiting for the seat to become free\n",i);
		 // leaves free seats decrements the value of taken waiting room seats
		read(freeseats[0],&num,sizeof(int));
		num++;
		write(freeseats[1],&num,sizeof(int));
		printf("Barber %d iis increasing the number of free seats to %d\n",i, num);

		V(seats) ; // frees seats
		V(barber); // frees barber

		printf("Barber is now cutting hair %d\n",i);
		randomwait(1); // random wait before finishing haircut
	}
}

void customer_run() {
	int num,i;
	
	for (i=1;i<3;++i) { // at most 10 customers will get their hair cut
		printf("- New customer trying to find a seat\n");
		P(seats); // locks seats
		read(freeseats[0],&num,sizeof(int));
		if(num < 0){ // if there are no seats available 
			write(freeseats[1],&num,sizeof(int));
			V(seats);// opens free seats
			printf("Customer leaves, no free seats\n");
		}
		else{
			
			printf("- Customer is decreasing the number of free seats to %d \n", num);
			// decrements the number of free seats
			num--;
			write(freeseats[1],&num,sizeof(int));
			// frees up customer and seats
			V(customers);
			V(seats);
			
			printf("-Customer is now waiting for barbe\nr");
			P(barber);// lock barber
			printf("Barber is now cutting hair\n");
		}
		randomwait(1); // random wait before finishing haircut
	}	
		
		// Insert code here
		
		
}

void randomwait(int d) { // random 0 to d sec delay
	int delay;
	struct timespec tim, tim2;
    tim.tv_sec = 0;
	delay = abs(rand() % 1000000000) * d;
	tim.tv_nsec = delay;
	nanosleep(&tim,&tim2);
}

