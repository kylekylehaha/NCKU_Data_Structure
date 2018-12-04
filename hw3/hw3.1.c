#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 10000
#define MAX_SIZE 10000

int index_total;
int txt_total;
int *freq;
char key[WORD_SIZE][WORD_SIZE];
char txt[MAX_SIZE][MAX_SIZE];
char buffer[WORD_SIZE];
char cmp[]="-----";

void init(){
	memset(buffer,0,sizeof(buffer));

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
	int i, k;
	char *token;

	for (k=0;k<txt_total;k++){
		token = strtok(txt[k]," ");
		while (token != NULL){
			/*find symbol and move it*/
			for (i=0;i<strlen(token);i++){
				if ((token[i]<65) || ((90<token[i]) && (token[i]<97)) || (token[i]>122)){
					token[i] = '\0';
				}
			}
			count(token);
			token = strtok(NULL," ");
		}
	}

	return ;
}

/* find the max freq and print */
void find_max(){
	int i, j, len, max;
	char *temp;
	char *max_key[index_total];
	
	max = freq[0];
	/* find the max freq */
	for (i=0;i<index_total;i++){
		if ( max < freq[i]){
			max = freq[i];
		}
	}
	/* check how many key have same max freq*/
	for (i=0,j=0;i<index_total;i++){
		if (max == freq[i]){
			max_key[j++] = key[i];
		}
	}
	len = j;	
	/* printf with dictionary*/
	for (i=0;i<len-1;i++)
		for(j=i+1;j<len;j++){
			if (strcmp (max_key[i],max_key[j]) >0){
				temp = max_key[i];
				max_key[i] = max_key[j];
				max_key[j] = temp;
			}
		}
	for (i=0;i<len;i++)
		printf ("%s %d\n",max_key[i],max);

	return ;
}

int main(){
	int i, j;
	char *enter;

	init();

	index_total = 0;
	txt_total = 0;

	while (fgets(buffer,WORD_SIZE,stdin) !=NULL){
		enter = strchr(buffer,'\n');
		*enter = '\0';
		if (strcmp(buffer,cmp) == 0){
			memset(buffer,0,sizeof(buffer));
			while (fgets(buffer,WORD_SIZE,stdin) !=NULL){
				enter = strchr(buffer,'\n');
				*enter = '\0';
				strcpy(txt[txt_total++],buffer);
				memset(buffer,0,sizeof(buffer));
			}
			break;
		}
		else {
			strcpy(key[index_total++],buffer);
			memset(buffer,0,sizeof(buffer));
		}
	}
	freq = malloc(sizeof(int)*index_total);
	for (i=0;i<index_total;i++)
		freq[i] = 0;	

	compare();	

	find_max();

	return 0;
}
