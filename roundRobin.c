#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define TIME_QUANTUM 1
struct Process{
	int pid;
	int aTime;
	int bTime;
	int cTime;
	int tTime;
	int rTime;
	int wTime;
	int remainingTime;
};
typedef struct Process PR;

int main(){
	int n;
	printf("Enter the number of processes\n");
	scanf("%d",&n);
	PR PROCESS[n];
	int val;
	for(int i=0;i<n;i++){
		printf("Enter the arrival time of process %d: ",i+1);
		scanf("%d",&val);
		PROCESS[i].aTime=val;
		PROCESS[i].pid=i+1;
	}
	for(int i=0;i<n;i++){
		printf("Enter the burst time of process %d: ",i+1);
		scanf("%d",&val);
		PROCESS[i].bTime=val;
		PROCESS[i].remainingTime=val;
	}
	int completed=0;
	int currentTime=0;
	int front=0;
	int rear=-1;
	int queue[n];
	int processesInQueue=0;
	int processInQueueTracker[n];
	for(int i=0;i<n;i++){
		processInQueueTracker[i]=0;
	}
	while(completed!=n){
		for(int i=0;i<n;i++){
			if(PROCESS[i].aTime <=currentTime && PROCESS[i].remainingTime > 0 && processInQueueTracker[i]==0){	
				queue[++rear % n]=i;
				processesInQueue++;
				processInQueueTracker[i]=1;
			}
		}
		if(processesInQueue>0){
			int index=queue[front % n];
			front=(front+1)%n;
			processesInQueue--;
			printf("%d\n",index+1);
			if(PROCESS[index].remainingTime == PROCESS[index].bTime){
				PROCESS[index].rTime=currentTime;
			}
			if(PROCESS[index].remainingTime > TIME_QUANTUM){
				currentTime+=TIME_QUANTUM;
				PROCESS[index].remainingTime-=TIME_QUANTUM;
			}else{
				currentTime+=PROCESS[index].remainingTime;
				PROCESS[index].remainingTime=0;
				PROCESS[index].cTime=currentTime;
				PROCESS[index].tTime=PROCESS[index].cTime-PROCESS[index].aTime;
				PROCESS[index].wTime=PROCESS[index].tTime-PROCESS[index].bTime;
				completed++;
			}
			
			if(PROCESS[index].remainingTime > 0){
				queue[++rear % n]=index;
				processesInQueue++;
			}else{
				processInQueueTracker[index]=0;
			}
		}else{
			currentTime++;
		}
	}
	// Display the final results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", PROCESS[i].pid, PROCESS[i].aTime, PROCESS[i].bTime,
               PROCESS[i].cTime, PROCESS[i].tTime, PROCESS[i].wTime);
    }

    return 0;
}
