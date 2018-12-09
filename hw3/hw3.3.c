#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000
#define INFINITE 99999
#define TRUE 1
#define FALSE 0

typedef struct{
	int dest_from_start;
	int position;
}DEST_FROM_START;

typedef struct{
	int node1;
	int node2;
	int dest;
}WEIGHT;

int index_weight = 0; // index for weight[]
int total_count= 0;
int road_count;
int total_node[MAX_SIZE];
DEST_FROM_START *S;
DEST_FROM_START *Q;
WEIGHT weight[MAX_SIZE];

void init(){
	int i, j;

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

int find_dest (int start, int end){
	int i, dest_between = INFINITE;

	for (i=0;i<index_weight;i++){
		if ((start == weight[i].node1) && (end == weight[i].node2)){
			dest_between = weight[i].dest;
			return dest_between;
		}	
	}
	for (i=0;i<index_weight;i++){
		if ((end == weight[i].node1) && (start == weight[i].node2)){
			dest_between = weight[i].dest;
			return dest_between;
		}
	}

	return dest_between;

}

void update(DEST_FROM_START pick, int number_in_Q){
	int i,min,dest_between;

	for (i=0;i<number_in_Q;i++){
		dest_between = find_dest(pick.position,Q[i].position);
		if (Q[i].dest_from_start < pick.dest_from_start + dest_between)
			min = Q[i].dest_from_start;
		else 
			min = pick.dest_from_start + dest_between;
		Q[i].dest_from_start = min;
	}

	return ;
}

void dijkstra(int start_node , int end_node){
	int i, final_dest, min;
	int find = FALSE;
	int number_in_S = 0;
	int number_in_Q = total_count;
	DEST_FROM_START pick;
	
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

	for (i=0;i<number_in_S;i++){
		if (end_node == S[i].position){
			if (S[i].dest_from_start != INFINITE){
				find = TRUE;
				printf("%d",S[i].dest_from_start);
			}
			else {
				find = FALSE;
			}
			break;
		}
	}
	if (!find)
		printf ("404\n");

	return ;
}

int main(){
	int i, j, check_node1, check_node2,  node1, dest, node2, len, start_node, end_node ;

	init();
	index_weight = 0;
	scanf("%d",&road_count);
	for (i=0;i<road_count;i++){
		scanf("%d%d%d",&node1,&dest,&node2);
		if (dest <=0){
			printf ("404\n");
			exit(1);
		}
		weight[index_weight].node1= node1;
		weight[index_weight].node2 = node2;
		weight[index_weight++].dest = dest;		
		//check whether start有沒有被算過
		check_node1 = TRUE;
		check_node2 = TRUE;
		for (j=0;j<total_count;j++){
			if (node1 == total_node[j]){
				check_node1 = FALSE;
				break;
			}
		}
		if (check_node1) {
			total_node[total_count++] = node1;
		}
		for (j=0;j<total_count;j++){
			if (node2 == total_node[j]){
				check_node2 = FALSE;
				break;
			}
		}
		if (check_node2) {
			total_node[total_count++] = node2;
		}
		
	}
	scanf("%d%d",&start_node, &end_node);

	dijkstra(start_node, end_node);

	return 0;
}
