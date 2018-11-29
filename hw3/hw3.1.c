#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 1000
#define MAX_SIZE 10000

int index_total;
int *freq;
char key[WORD_SIZE][WORD_SIZE];
char txt[MAX_SIZE];
char temp[WORD_SIZE];
char cmp[]="-----";

void init(){
	memset(txt,0,sizeof(txt));
	memset(temp,0,sizeof(temp));

	return ;
}

/* check whether token is in key array, and count the frequency*/
void count (char *str){
	int i = 0;
	for (i=0;i<index_total;i++){
		if (strcmp(str,key[i]) == 0){
			freq[i]++;
			break;
		}
	}
	
	return ;
}

void compare(){
	int i, j;
	char *token;

	token = strtok(txt," ");
	while (token != NULL){
		/*find symbol and move it*/
		for (i=0,j=0;i<strlen(token);i++){
			if ((token[i]<65) || ((90<token[i]) && (token[i]<97)) || (token[i]>122)){
				token[i] = '\0';
			}
		}
		count(token);
		token = strtok(NULL," ");
	}

	return ;
		
}

/* find the max freq and print */
void find_max(){
	int i, max;
	
	max = freq[0];
	/* find the max freq */
	for (i=0;i<index_total;i++){
		if ( max >= freq[i]){
			max = freq[i];
		}
	}
	/* check how many key have same max freq*/
	for (i=0;i<index_total;i++){
		if (max == freq[i])
			printf("%s %d\n",key[i],freq[i]);
	}

	return ;
}

int main(int argc , char *argv[]){
	int j, max;
	int i=1;
	int length = 0;

	init();

	index_total = 0;
	while(i<argc){
		if (strcmp(argv[i],cmp) == 0){
			for(j=i+1;j<argc;j++){			//i+1 for skip "-----"
				length = strlen(argv[j]);
				strcpy(temp,argv[j]);
				temp[length] = ' ';			//there are extra blankspace behind the last word
				strcat(txt,temp);
				memset(temp,0,sizeof(temp));			
			}
			break;
		}
		else{
			strcpy(key[index_total++],argv[i++]);
		} 
	}
	
	freq = malloc(sizeof(int)*index_total);
	for (i=0;i<index_total;i++)
		freq[i] = 0;	

	compare();	

	find_max();

	free(freq);
	return 0;
}
