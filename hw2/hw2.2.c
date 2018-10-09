#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

char *enter;
char *targetsmall;
char buffer[MAX_SIZE];
char target[MAX_SIZE];
char replace[MAX_SIZE];

void init(){
	memset(buffer,0,sizeof(buffer));
	memset(target,0,sizeof(target));
	memset(replace,0,sizeof(replace));
}

char *captosmall(char *str){
	int i;
	int len = strlen((str));

	for(i=0;i<len;i++){
		if( (str[i]>=65) && (str[i]<=90))
			str[i] = str[i]+32;
	}

	return str;
}

void change(){
	int i, wordlen, targetlen;
	char *token;
	char *tokensmall;
	char original[MAX_SIZE];

	targetlen = strlen(target);
	memset(original,0,sizeof(original));

	token = strtok(buffer," ");
	while(token != NULL){
		wordlen = strlen(token);
		if(wordlen != targetlen){
			printf("%s",token);
		}
		else{
			strcpy(original,token);
			tokensmall = captosmall(token);
			if( strcmp(tokensmall,targetsmall) == 0){
				printf("%s",replace);
			}
			else {
				printf("%s",original);
			}
		}
		token = strtok(NULL," ");
		if(token != NULL)
			printf(" ");
	}	
}

int main(){
	init();

	fgets(buffer,MAX_SIZE,stdin);
	fgets(target,MAX_SIZE,stdin);
	fgets(replace,MAX_SIZE,stdin);

	/* delete '\n' in buffer, target, replace */
	enter = strchr(buffer,'\n');
	*enter = '\0';
	enter = strchr(target,'\n');
	*enter = '\0';
	enter = strchr(replace,'\n');
	*enter = '\0';	

	/* ready for compare whether is captial or small */
	targetsmall = captosmall(target);

	/* replace target word and print */
	change();
}
