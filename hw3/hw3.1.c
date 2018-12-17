#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_SIZE 1000
#define MAX_SIZE 1000
#define TRUE 1
#define FALSE 0

int index_total;
int txt_total;
int *freq;
char *key[MAX_SIZE];
char txt[MAX_SIZE];
char buffer[WORD_SIZE];
char cmp[]="-----";

void init(){
	memset(buffer,0,sizeof(buffer));
	memset(txt,0,sizeof(MAX_SIZE));

	return ;
}

int check(char boundary){
	if(boundary>='0' && boundary<='9')//number
		return FALSE;
	else if(boundary>='A' && boundary<='Z')//capital
		return FALSE;
	else if(boundary>='a' && boundary<='z')//lower
		return FALSE;
	else
		return TRUE;	
}

int search(char *str, char *target, int time){
	int len = strlen(target);
	char *next = strstr(str,target);
	while (next != NULL){
		if (check(*(next-1)) && check(*(next+len))){
			time++;
		}
		next = strstr((next+len),target);
		if (next == NULL) break;
	}	
	return time;
}

void compare(){
	int i;
	for (i=0;i<index_total;i++){
		freq[i] = search(txt,key[i],freq[i]);
	}
	
	return ;
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
	int i, j, len;
	int repeat = 0;
	char *enter;
	char c;
	init();

	index_total = 0;
	txt_total = 0;
	while (fgets(buffer,WORD_SIZE,stdin) !=NULL){
		enter = strchr(buffer,'\n');
		*enter = '\0';
		if (strcmp(buffer,cmp) == 0){
			memset(buffer,0,sizeof(buffer));
			c = getchar();
			while (c!=EOF){
				txt[txt_total++] = c;
				c = getchar();
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
