#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#define MAX_LENGTH 78763 
clock_t start,finish;

typedef struct node *NodePointer;
typedef struct node{
	char *key;
	NodePointer left;
	NodePointer right;
}node;

NodePointer root = NULL;
void create(NodePointer *ptr, char *string){
	NodePointer temp;
	temp = malloc(sizeof(*temp));
	temp -> left = NULL;
	temp -> right = NULL;
	temp -> key = string;
	*ptr = temp;
	return ;
}

void insert (char *data){
	NodePointer insert_pos, check, ptr;
	check = root;
	insert_pos = NULL;
	create (&ptr,data);
	if (!root){
		root = ptr;
		return ;
	}
	while (check != NULL){
		insert_pos = check;
		if (strcmp (data,check -> key) >0)	check = check ->right;
		else if (strcmp (data,check->key)<0)	check = check ->left;
	}
	if (strcmp(data,insert_pos -> key) >0)	insert_pos ->right = ptr;
	else insert_pos -> left = ptr;
	return ;
}
// change temp_A[5] -> temp_A[20]
// change temp_B[5] -> temp_B[10]
// because overflow
char *check(char data[MAX_LENGTH], char answer[MAX_LENGTH]) {
    static char clue[12];
    char temp_A[20],temp_B[10];
    int i;
    int A = 0;
    int ans_appear_times[10] = {0, 0, 0, 0, 0, 
                              0, 0, 0, 0, 0};
    int data_appear_times[10] = {0, 0, 0, 0, 0, 
                               0, 0, 0, 0, 0};

    //calculate A
    for(i=0; i<MAX_LENGTH; i++) {
        if(data[i] == answer[i]) {
            A++;
        } 
        else {
            ans_appear_times[answer[i]-'0']++;
            data_appear_times[data[i]-'0']++;
        }  
    }
  // calculate B
    int B = 0;
    for(i=0; i<10; i++) {
        if(data_appear_times[i] >= ans_appear_times[i]) {
            B += ans_appear_times[i];
        } 
        else {
            B += data_appear_times[i];
        }
    }
    if(A==MAX_LENGTH && B==0)	{
  	    return "AC";
    }
	sprintf(temp_A,"%d",A);  
	sprintf(temp_B,"%d",B);
    	strcat(temp_A,"A"); 
	strcat(temp_B,"B"); 
	strcat(temp_A,temp_B);  
	strcpy(clue,temp_A);
	return clue;
} 

int start_check =0;
int zeroA_check = 0;
int crazy_count = 0;			//0~9
int crazy_check = 0;			//0~MAX_LENGTH-1
int zero_A = 0;
char data_last[MAX_LENGTH];
char data_standary[MAX_LENGTH];

void init(){
	int i;
	for (i=0;i<MAX_LENGTH;i++)
		data_standary[i] = '0';
	return ;
}

char *guess(char *clue){
	int i, j, len,len_clue_count, clue_A, clue_B, index=0;
	static char data[MAX_LENGTH];

	len = strlen(clue);
	char clue_count[len];
	memset(clue_count,0,sizeof(clue_count));
	//find A_time & B_time
	for (i=0;i<len;i++){
		if (clue[i] == 'A'){
			clue_A = atoi(clue_count);
			index = 0;
			memset(clue_count,0,sizeof(clue_count));
		}
		else if (clue[i] == 'B'){
			clue_B = atoi(clue_count);
			index = 0;
			memset(clue_count,0,sizeof(clue_count));
		}
		else{
			clue_count[index++] = clue[i];
		}
	}
	if (!start_check){
		//prepare compare data
		//strcpy(data,data_standary)
		for (j=0;j<MAX_LENGTH;j++)
			data[j] = data_standary[j];
		//strcpy(data_last,data)
		for (j=0;j<MAX_LENGTH;j++)
			data_last[j] = data[j];
		start_check = 1;
	}
	else {
		//strcpy(data,data_last);
		for (j=0;j<MAX_LENGTH;j++)
			data[j] = data_last[j];
		if (!zeroA_check){
			zero_A = clue_A;
			crazy_count ++;
			//strcpy(data_last,data)
			for (j=0;j<MAX_LENGTH;j++)
				data_last[j] = data[j];
			data[crazy_check] = crazy_count + '0';
			zeroA_check = 1;
		}
		//compare ()
		else {
			if ((clue_A - zero_A) >0){			//move to next position
				crazy_check++;
				crazy_count = 0;	
				zero_A = clue_A;
			}
			else if ((clue_A - zero_A) ==0){			//find next possible for current position
				crazy_count++;
				data[crazy_check] = crazy_count + '0';
			}
			else {			//last possible is correct
				int temp = data_last[crazy_check] - '0';
				if (temp !=0) temp --;
				data[crazy_check] = temp + '0' ;
				crazy_check ++;
				crazy_count = 0;
			}	
			//strcpy(data_last,data);
			for (j=0;j<MAX_LENGTH;j++)
				data_last[j] = data[j];
		}
	}
//	printf ("data return is %s\n",data);
	return data;
}

int main(int argc, char *argv[]) {

    char ans[MAX_LENGTH];
    char get_back[MAX_LENGTH]="0A0B";   //initial input to guess function
    srand(time(NULL));
    struct timeval tval_before, tval_after, tval_result;

    int i;
    for(i=0; i<MAX_LENGTH; i++) {
        ans[i] = rand()%10+'0';
    }
	init();
    //time start
    gettimeofday(&tval_before, NULL);
    while(1){
        //get_back is mean that the result of your guess
  	strcpy(get_back,check(guess(get_back), ans));
        // your guessed right!!! Congratulation !!!
        if(strcmp(get_back,"AC")==0)	break;
	gettimeofday(&tval_after, NULL);
	long t = (tval_after.tv_sec*1e6 + tval_after.tv_usec) - (tval_before.tv_sec*1e6 + tval_before.tv_usec);
	// convert to we can read
        const int n = snprintf(NULL, 0, "%lu", t);
        assert(n > 0);
        char buf[n+1];
        int c = snprintf(buf, n+1, "%lu", t);
        assert(buf[n] == '\0');
        assert(c == n);
	int length = strlen(buf);
        //print time
        if(length>6) {
            for(int i=0; i<length-6;i++){
                printf("%c",buf[i]);
            }
            printf(",");
            for(int i=length-6; i<length;i++) {
                printf("%c",buf[i]);
            }
            printf("\n"); 
        }
    }
	printf ("done!!!\n");
    return 0;
}
