#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "p1.h"
//program is executed by typing the following command in the terminal
//gcc <filename>.c -pthread - this will automatically create "a.out"
//use ls to see the directory
//type ./a.out to execute.
//mutex customer order lock
struct stats{
    struct timespec * waitTimesForCallAgent;
    struct timespec *customerServiceTimes;
    struct timespec* coolingTimes;
    int cancelledOrders;
    int revenue;
};
pthread_mutex_t customerLock;           //here are all the different mutex locks used to synchronize and restrict..
pthread_mutex_t ovenLock;              //..the flow
pthread_mutex_t prepLock;
pthread_mutex_t deliveryLock;
int currentAvailableOvens = Noven;
int availableAgents = Ntel;
int deliveryPeople = Ndeliverer;
struct stats * restaurantStats;

enum { NS_PER_SECOND = 1000000000 };

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
} 
void time_delay (int secs){
    int ms = 1000*secs;
    clock_t startTime = clock();
    while (clock() < startTime + ms);
}
int returnRandom (int lower, int higher) {
    return (rand()%(higher-lower+1)) + lower;   //function to generate random integers
}
int prepPizza(int noOfPizza, int customerID){
    sleep(noOfPizza);                           //to put the thread to sleep.
    printf("Order %d's pizzas prepared in %d minutes\n", customerID, noOfPizza);
    //time_delay(noOfPizza);
    return 1;
}
int bakePizzas(int quantity, int customerID) {
    //printf("!! Baking Pizza !!"); 
    sleep(Tbake);
    printf("Order %d's pizzas baked in 15 minutes\n", customerID);
    //time_delay(15); //all ovens occupied at once
    return 15;
}
int packPizza(int quantity, int customerID){
    sleep(Tpack);
    printf("Order %d's pizzas packed in 2 minutes\n", customerID);
    //time_delay(2);
    return 2;
}
int deliverPizza (int customerID) {
    int randInt = returnRandom(Tdellow, Tdelhigh);
    sleep(randInt);
    //time_delay(randInt);
    return randInt;
}
//3, 4
void* placeOrderAndProcess(void* customerID) {
    struct timespec start, finish, delta, localStart;            //DESC: Conditional statements are used with mutex locks
    if (availableAgents == 0){                                  //counts are maintained of ovens, agents, etc.
        pthread_mutex_lock(&customerLock);                     //these counts are manipulated throughout the execution
    }
    availableAgents--; //decrease the available agents as one is now engaged
    int * L_customerID = (int*) customerID;
    int * no_Of_Pizzas = (int*) malloc(sizeof(int));
    int * avgTimeCalculations = (int*) malloc(sizeof(int)*5);
    clock_gettime(CLOCK_REALTIME, &start);                 //gets the current time for manipulation later on
    int randomWaitTime = returnRandom(Torderlow, Torderhigh);
    sleep(randomWaitTime);
    *no_Of_Pizzas  = returnRandom(Norderlow, Norderhigh);
    if (*no_Of_Pizzas > 0){                       
        //generates a random integer between 0-5, if 5. order fails
        if (PFail == returnRandom(0, PFail)) {
            printf("Order %d cancelled/failed.\n", *L_customerID);
            sub_timespec(start, finish, &delta);
            restaurantStats->waitTimesForCallAgent[*L_customerID] = delta;
            restaurantStats->cancelledOrders++;
            return NULL;
        }
        else { 
        avgTimeCalculations[0] = randomWaitTime;
        //time_delay(randomWaitTime);
        restaurantStats->revenue = restaurantStats->revenue + Cpizza*(*no_Of_Pizzas);
        printf("Order %d registered.\n",  *L_customerID);
    }
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    sub_timespec(start, finish, &delta);
    restaurantStats->waitTimesForCallAgent[*L_customerID] = delta;
    if (availableAgents < 3) { //lcall agent is free now so increase val
        availableAgents++;
    }
    pthread_mutex_unlock(&customerLock);
    pthread_mutex_lock(&prepLock); //1 guy prepares pizzas so till preparation is complete lock the mutex
    avgTimeCalculations[1] = prepPizza(*no_Of_Pizzas, *L_customerID);
    pthread_mutex_unlock(&prepLock);

    if (currentAvailableOvens< *no_Of_Pizzas){  //lock oven if current requirement is more than the available ovens
        pthread_mutex_lock(&ovenLock);
    } 
    currentAvailableOvens-= (*no_Of_Pizzas);
    avgTimeCalculations[2] = bakePizzas(*no_Of_Pizzas, *L_customerID);
    currentAvailableOvens+= (*no_Of_Pizzas);
    avgTimeCalculations[3] = packPizza(*no_Of_Pizzas, *L_customerID);
    pthread_mutex_unlock(&ovenLock); //unlock oven when execution complete
    clock_gettime(CLOCK_REALTIME, &localStart);
    if (deliveryPeople < 0){
        pthread_mutex_lock(&deliveryLock);
        deliveryPeople--;
    }   //avg calculations are returned. 
    avgTimeCalculations[4] = deliverPizza(*L_customerID);
    printf("Order %d 's pizzas delivered in %d minutes\n", *L_customerID, avgTimeCalculations[4]);
    deliveryPeople++;
    clock_gettime(CLOCK_REALTIME, &finish);
    sub_timespec(start, finish, &delta);
    restaurantStats->customerServiceTimes[*L_customerID] = delta;
    sub_timespec(localStart, finish, &delta);
    restaurantStats->coolingTimes[*L_customerID] = delta;
    pthread_mutex_unlock(&deliveryLock);
    return avgTimeCalculations;
}

void printSummary(int totalNoOfOrders){
    //AVG Time 1
    int sum [3]= {0}, max[3] = {0};
    for (int i=0; i<totalNoOfOrders; i++){
        sum[0] += ((int)restaurantStats->customerServiceTimes[i].tv_nsec + NS_PER_SECOND);
        if (((int)restaurantStats->customerServiceTimes[i].tv_nsec + NS_PER_SECOND) > max[0]) {
            max[0] = ((int)restaurantStats->customerServiceTimes[i].tv_nsec + NS_PER_SECOND);
            //record the max. NS_PER_SECOND converts nano-seconds back to seconds.
        }
        sum[1] += ((int)restaurantStats->waitTimesForCallAgent[i].tv_nsec + NS_PER_SECOND);
        if (((int)restaurantStats->waitTimesForCallAgent[i].tv_nsec + NS_PER_SECOND) > max[1]) {
            max[1] = ((int)restaurantStats->waitTimesForCallAgent[i].tv_nsec + NS_PER_SECOND);
            //record the max. NS_PER_SECOND converts nano-seconds back to seconds.
        }
        sum[2] += ((int)restaurantStats->coolingTimes[i].tv_nsec + NS_PER_SECOND);
         if (((int)restaurantStats->coolingTimes[i].tv_nsec + NS_PER_SECOND)>max[2]) {
            max[2] = ((int)restaurantStats->coolingTimes[i].tv_nsec + NS_PER_SECOND);
            //record the max. NS_PER_SECOND converts nano-seconds back to seconds.
        }
    }

    printf("STATS: MAX Customer Service Time: %d\n", max[0]);
    printf("STATS: AVG Customer Service Time: %d\n", sum[0]/totalNoOfOrders);

    printf("STATS: MAX Call Agent Time: %d\n", max[1]);
    printf("STATS: AVG Call Agent Time: %d\n", sum[1]/totalNoOfOrders);

    printf("STATS: MAX Cooling Time: %d\n", max[2]);
    printf("STATS: AVG Cooling Time: %d\n", sum[2]/totalNoOfOrders);
}
int main(void) {

int Ncust;
printf("DEBUG: F1 MAIN\n");
printf("Enter No. of Customers: \n");
scanf ("%d", &Ncust);
printf("Number of customers entered: %d\n", Ncust);
pthread_t customers[Ncust];
int * pizzaOrders = (int*) malloc(Ncust*sizeof(int));
int ** ordersAndAvgTimes;
*ordersAndAvgTimes = malloc(Ncust * sizeof(int));
restaurantStats = malloc(sizeof(restaurantStats));
//initializing the struct. could've been done in an function but for better understanding left here.
restaurantStats->coolingTimes = malloc(sizeof(struct timespec*)*Ncust);
restaurantStats->customerServiceTimes = malloc(sizeof(struct timespec*)*Ncust);
restaurantStats->waitTimesForCallAgent = malloc(sizeof(struct timespec*)*Ncust);
restaurantStats->cancelledOrders=0;
restaurantStats->revenue=0;
//------------------------------------------------------//--------------------------------------------------------//
int orderIDs[Ncust]; //separate orderIDs created because of dangling memory. if &i is passed instead, it will not be unique-
for (int i=0; i<Ncust; i++){ //--and result in unwanted conflicts.
    orderIDs[i] = i;
    if (pthread_create(&customers[i], NULL, &placeOrderAndProcess, &orderIDs[i]) == -1){
        printf("Failed: Error! Couldn't create thread\n");
    } else {
        printf("DEBUG: Thread was passed ID %d\n", i);
    }
    
}
for (int i=0; i<Ncust; i++){
    int * ptr;
    pthread_join(customers[i], (void**)&ptr);
    if (ptr){
        ordersAndAvgTimes[i] = malloc(sizeof(int*));
        ordersAndAvgTimes[i] = ptr;
    }
    printf("Last FOR in main\n");
   }
//print stats;
printf("STATS: Total Revenue Generated: %d\n", restaurantStats->revenue);
printf("STATS: Amount of successful Orders: %d\n", Ncust-restaurantStats->cancelledOrders);
printf("STATS: Amount of unsuccessful Orders: %d\n", restaurantStats->cancelledOrders);
printSummary(Ncust);

return 0;
}


