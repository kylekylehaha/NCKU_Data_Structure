#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define INFINITE 9999
#define TRUE 1
#define FALSE 0

typedef struct{
	int dest_from_start;
	int position;
}DEST_FROM_START;

int total_count= 0;
int road_count;
int weight[MAX_SIZE][MAX_SIZE];
int total_node[MAX_SIZE];
DEST_FROM_START *S;
DEST_FROM_START *Q;

void init(){
	int i, j;

	for (i=0;i<MAX_SIZE;i++)
		for (j=0;j<MAX_SIZE;j++){
			weight[i][j] = INFINITE;
			if (i == j) weight[i][j] = 0;
		}

	return ;
}

// push node in S
void push(DEST_FROM_START pick, int *number_in_S){
	S[(*number_in_S) ++] = pick;

	return ;
}

void pop(int *number_in_Q, DEST_FROM_START pick){
	int i, index;
	DEST_FROM_START temp;

	for (i=0;i<(*number_in_Q);i++){
		if (pick.position == Q[i].position){
			index = i;
			break;
		}
	}

	//swap
	temp.dest_from_start = Q[index].dest_from_start;
	temp.position = Q[index].position;
	Q[index].dest_from_start = Q[(*number_in_Q) -1].dest_from_start;	
	Q[index].position = Q[(*number_in_Q) -1].position;
	Q[(*number_in_Q) -1].dest_from_start = temp.dest_from_start;
	Q[(*number_in_Q) -1].position = temp.position;

	(*number_in_Q) --;
	
	return ;
}

DEST_FROM_START findNext(int number_in_Q){
	int i;
	DEST_FROM_START pick;	

	pick = Q[0];	
	for (i=0;i<number_in_Q;i++){
		if (pick.dest_from_start > Q[i].dest_from_start)
			pick = Q[i];
		}

	return pick;
}

void update(DEST_FROM_START pick, int number_in_Q){
	int i,min;

//	printf("func. update, pick position %d, dest %d\n",pick.position,pick.dest_from_start);
	for (i=0;i<number_in_Q;i++){
		if (Q[i].dest_from_start < pick.dest_from_start + weight[pick.position][Q[i].position])
			min = Q[i].dest_from_start;
		else 
			min = pick.dest_from_start + weight[pick.position][Q[i].position];
//		printf("position %d, after update, dest is %d\n",Q[i].position,min);
		Q[i].dest_from_start = min;
	}

	return ;
}

void dijkstra(int start_node , int end_node){
	int i, final_dest, min;
	int number_in_S = 0;
	int number_in_Q = total_count;
	DEST_FROM_START pick;
	
//	printf("func. dijkstra\n");
	//initial all Q dest_from_start = INFINITE, except startposition itself
	S = malloc(sizeof(DEST_FROM_START)*total_count);	
	Q = malloc(sizeof(DEST_FROM_START)*total_count);	
	for (i=0;i<total_count;i++){
		Q[i].position = total_node[i];
		if (Q[i].position == start_node){
			Q[i].dest_from_start = 0;
		}
		else {
			Q[i].dest_from_start = INFINITE;
		}
	}

	//dijkstra algorithm
	while (number_in_Q >0){

		//find the smallest dest_from_start in Q
		pick = findNext(number_in_Q);
		pop(&number_in_Q,pick);
		update(pick,number_in_Q);
		push(pick,&number_in_S);
	}	

	for (i=0;i<total_count;i++){
		if (end_node == S[i].position){
			printf("%d\n",S[i].dest_from_start);
			break;
		}
	}

	return ;
}

int main(){
	int i, j, check_start, check_end,  start, dest, end, len, start_node, end_node;

	init();

	scanf("%d",&road_count);
	for (i=0;i<road_count;i++){
		scanf("%d%d%d",&start,&dest,&end);
		weight[start][end] = dest;
		weight[end][start] = dest;
		//check whether start有沒有被算過
		check_start = TRUE;
		check_end = TRUE;
		for (j=0;j<total_count;j++){
			if (start == total_node[j]){
				check_start = FALSE;
				break;
			}
		}
		if (check_start) total_node[total_count++] = start;
		for (j=0;j<total_count;j++){
			if (end == total_node[j]){
				check_end = FALSE;
				break;
			}
		}
		if (check_end) total_node[total_count++] = end;
		
	}
	scanf("%d%d",&start_node, &end_node);

	dijkstra(start_node, end_node);

	return 0;
}
