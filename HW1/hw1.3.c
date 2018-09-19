#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000

int i , j ,k , count ;
char temp[MAX_SIZE];
char *token;
char **output;

void reverse(){
	/*initial output*/
	output = malloc(sizeof(char*)*MAX_SIZE);
	for(j=0;j<MAX_SIZE;j++)
		output[j] = NULL;

	for(j=0;j<count;j++){
		fgets(temp , MAX_SIZE , stdin);

		i = 0;
		
		token = strtok(temp," ");
		while(token != NULL){
			output[i++] = token;
			token = strtok(NULL , " ");
		}

		i = i -1;			/*Because it is array , start from 0*/

		for(;i>=0;i--){
			for(k=0;k<strlen(output[i]);k++){
				if(*(*(output+i)+k) != '\n')
					printf("%c",*(*(output+i)+k));
			}
			printf(" ");
		}
		printf("\n");
	}
}

int main(){
	scanf("%d",&count);

	getchar();
		
	reverse();
	
	return 0;
}	
