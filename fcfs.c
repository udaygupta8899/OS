#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

struct Process{
	int pid;
	int aTime;
	int bTime;
	int cTime;
	int tTime;
	int rTime;
	int wTime;
};
typedef struct Process PR;
int main(){
	int n;
	printf("Enter the number of processes\n");
	scanf("%d",&n);
	PR PROCESS[n];
	int val;
	for(int i=0;i<n;i++){
		printf("Enter the arrival time for process %d: ",i+1);
		scanf("%d",&val);
		printf("\n");
		PROCESS[i].pid=i+1;
		PROCESS[i].aTime=val;
	}
	for(int i=0;i<n;i++){
		printf("Enter the burst time for process %d: ",i+1);
		scanf("%d",&val);
		printf("\n");
		PROCESS[i].bTime=val;
	}
	int currentTime=0;
	for(int i=0;i<n;i++){
		if(PROCESS[i].aTime > currentTime){
			currentTime = PROCESS[i].aTime;
		}
		PROCESS[i].rTime=currentTime-PROCESS[i].aTime;
		PROCESS[i].cTime=currentTime+PROCESS[i].bTime;
		currentTime+=PROCESS[i].bTime;
	}
	for(int i=0;i<n;i++){
		PROCESS[i].tTime=PROCESS[i].cTime-PROCESS[i].aTime;
		PROCESS[i].wTime=PROCESS[i].tTime-PROCESS[i].bTime;
	}
	printf("PID \t C Time \t T Time \t W Time \t R Time \n");
	for(int i=0;i<n;i++){
		printf("%d \t %d \t\t %d \t\t %d \t\t %d \n",PROCESS[i].pid,PROCESS[i].cTime,PROCESS[i].tTime,PROCESS[i].wTime,PROCESS[i].rTime);
	}
	return 0;
}
