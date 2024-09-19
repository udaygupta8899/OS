#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

struct Process{
	int pid;
	int aTime;
	int bTime;
	int cTime;
	int tTime;
	int wTime;
	int rTime;
	int remainingTime;
};
typedef struct Process PR;

int findShortestProcess(PR PROCESS[],int n, int currentTime){
	int minIndex=-1;
	int minTime=100000;
	for(int i=0;i<n;i++){
		if(PROCESS[i].aTime <= currentTime && PROCESS[i].remainingTime > 0 && PROCESS[i].remainingTime < minTime){
			minIndex=i;
			minTime=PROCESS[i].remainingTime;
		}
	}
	return minIndex;
}
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
	int currentTime=0;
	int completed=0;
	while(completed!=n){
		int shortest=findShortestProcess(PROCESS,n,currentTime);
		if(shortest!=-1){
			if(PROCESS[shortest].bTime==PROCESS[shortest].remainingTime){
				PROCESS[shortest].rTime=currentTime-PROCESS[shortest].aTime;
			}
			PROCESS[shortest].remainingTime--;
			if(PROCESS[shortest].remainingTime==0){
				PROCESS[shortest].cTime=currentTime+1;
				PROCESS[shortest].tTime=currentTime+1-PROCESS[shortest].aTime;
				PROCESS[shortest].wTime=PROCESS[shortest].tTime-PROCESS[shortest].bTime;
				completed++;
			}
		}
		currentTime++;
	}
	printf("PID \t aTime \t bTime \t cTime \t tTime \t wTime \t rTime \n");
	for(int i=0;i<n;i++){
		printf("%d \t %d \t %d \t %d \t %d \t %d \t %d\n",PROCESS[i].pid,PROCESS[i].aTime,PROCESS[i].bTime,PROCESS[i].cTime,PROCESS[i].tTime,PROCESS[i].wTime,PROCESS[i].rTime);
	}
	return 0;
}
