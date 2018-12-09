#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_SIZE 10000
#define MAX_SIZE 10000
#define TRUE 1
#define FALSE 0

int index_total;
int txt_total;
int *freq;
char *key[MAX_SIZE];
char *txt[MAX_SIZE];
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

int check_symbol(char c){
	if ((c >=97) && (c<=122))	return FALSE;
	else if ((c>=65) && (c<=90))	return FALSE;
	else if ((c>=48) && (c<=57))	return FALSE;
	else return TRUE;
}

void compare(){
	int i, j, k, check, len_token,len_key,len_count;
	char *token, *start;
	
	for (i=0;i<txt_total;i++){
		token = strtok(txt[i], " ");
		while (token != NULL){
			len_token = strlen(token);
			//compare all keyword
			for (j=0;j<index_total;j++){
				len_key = strlen(key[j]);
				start = strstr(token,key[j]);
				if (start){
					if (len_token == len_key) check = TRUE;
					else if (check_symbol(*(start-1)) && check_symbol(*(start+len_key))) check = TRUE;
					else check = FALSE;
					if (check){
						count(key[j]);
						check = FALSE;
						break;
					}
				}
			}
			token = strtok(NULL, " ");
		}
	}
	return ;
}

int strCompare(char *str1, char *str2) { 
	while (*str1 && *str1 == *str2) {		
		++str1, 
		++str2; 
	}
	return *str1 >= *str2; 
} 

/* find the max freq and print */
void find_max(){
	int i, j, len, max,index_num = 0;
	char *temp;
	char *max_key[index_total];
	char *number[index_total];
	
	max = freq[0];
	/* find the max freq */
	for (i=0;i<index_total;i++){
		if ( max < freq[i]){
			max = freq[i];
		}
	}
	/* check how many key have same max freq*/
	for (i=0, len = 0;i<index_total;i++){
		if (max == freq[i]){
			max_key[len++] = key[i];
		}
	}	
	/* printf with dictionary*/
	for (i=0;i<len-1;i++)
		for(j=i+1;j<len;j++){
			if (strCompare (max_key[i],max_key[j]) >0){
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
	int i, j, len;
	int repeat = 0;
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
				len = strlen(buffer);
				txt[txt_total] = malloc (sizeof(char)*len+1);
				strcpy(txt[txt_total++],buffer);
				memset(buffer,0,sizeof(buffer));
			}
			break;
		}
		else {
			for (i=0;i<index_total;i++)
				if (strcmp(buffer,key[i]) ==0)
					repeat = 1;
			if (!repeat){
				len = strlen(buffer);
				key[index_total]= malloc(sizeof(char)*len);
				strcpy(key[index_total++],buffer);
			}
				//strcpy(key[index_total++],buffer);
			memset(buffer,0,sizeof(buffer));
			repeat = 0;
		}
	}
	freq = malloc(sizeof(int)*index_total);
	for (i=0;i<index_total;i++)
		freq[i] = 0;	

	compare();

	find_max();

	return 0;
}
