#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

char *enter;
char *targetsmall;
char buffer[MAX_SIZE];
char target[MAX_SIZE];
char oritarget[MAX_SIZE];
char replace[MAX_SIZE];

void init(){
	memset(buffer,0,sizeof(buffer));
	memset(target,0,sizeof(target));
	memset(oritarget,0,sizeof(oritarget));
	memset(replace,0,sizeof(replace));
}

void captosmall(char *str){
	int i;
	int len = strlen((str));

	if (str == NULL)
		return;

	for(i=0;i<len;i++){
		if( (str[i]>=65) && (str[i]<=90))
			str[i] = str[i]+32;
	}

	return ;
}

void change(){
	int i, wordlen, targetlen, count;
	char *token;
	char oritoken[MAX_SIZE];

	/* initial */
	targetlen = strlen(target);
	memset(oritoken,0,sizeof(oritoken));
	count = 0;

	token = strtok(buffer," ");
	while(token != NULL){
		memset(oritoken,0,sizeof(oritoken));
		wordlen = strlen(token);
		strcpy(oritoken,token);
		captosmall(token);
		if(wordlen != targetlen){
			if (wordlen > targetlen){
				for (i=0;i<wordlen;i++){
					if (token[i] == target[i]){
						count++;
					}
				}
				if (count == targetlen) {
					printf("%s",replace);
				}
				else { 
					printf("%s",oritoken);
				}
				count = 0;
			}
			else {
				printf("%s",oritoken);
			}
		}
		else{
			if( strcmp(token,target) == 0){
				printf("%s",replace);
			}
			else {
				printf("%s",oritoken);
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
	strcpy(oritarget,target);
	captosmall(target);

	/* replace target word and print */
	change();
}
