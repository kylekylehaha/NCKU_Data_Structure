#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int start;
	int destination;
}ROAD;

int nodecount, roadcount, totalvalue, endvalue, failcount, successcount;
int *nodevalue;
ROAD *road;

void init(){
	nodevalue = malloc(sizeof(int)*nodecount);
	road = malloc(sizeof(ROAD)*roadcount);
	successcount = 0;
	failcount = 0;

	return;
}

int check(int position){
	int j; 
	int count = 0;
	for(j=0;j<roadcount;j++){
		if(position == road[j].start)
			count++;
	}

	return count;
}

int find(int position){
	int j;
	int startposition = -1;
	for(j=0;j<roadcount;j++){
		if(position == road[j].start){
			startposition = j;
			break;
		}
	}

	return startposition;
}

void travel(int position){
	int i;
	int count = check(position);
	int startposition = find(position);

	if(totalvalue >endvalue){
		return;
	}
	
	if(count == 0){
		return;
	}

	for(i=startposition;i<count+startposition;i++){
		if(totalvalue > nodevalue[road[i].destination]){
			totalvalue = totalvalue + nodevalue[road[i].destination];
			successcount ++;
			travel(road[i].destination);
		}
		else{
			failcount ++;
		}
	}

	return;

}

int main(){
	int i;

	scanf("%d%d%d%d",&nodecount, &roadcount, &totalvalue, &endvalue);
	init();

	/* read nodevalue & road info */
	for(i=0;i<nodecount;i++){
		scanf("%d",&nodevalue[i]);
	}
	for(i=0;i<roadcount;i++){
		scanf("%d",&(road[i].start));
		scanf("%d",&(road[i].destination));
	}
	
	if (totalvalue > nodevalue[0]){
	successcount ++;
	travel(road[0].start);
	}
	else {
		failcount ++;
	}

	/* print result */
	printf("%d %d %d",failcount, successcount, totalvalue);

	free(nodevalue);
	free(road);
}
