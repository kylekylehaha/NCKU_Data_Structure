#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 999

int count, oddcount, evencount;
int indexnum = 1;
char odd[MAX_SIZE];
char even[MAX_SIZE];
char *result;
char buffer[MAX_SIZE];

void bignumadd(){

}

int main(){
	/* count how many odd and even */ 
	scanf("%d",&count);
	(count % 2 ==1) ? oddcount = count/2 +1 : oddcount /2;
	evencount = count /2;

	/* strcat buffer to oddstring or evenstring */
	memset(buffer,0,sizeof(buffer));
	while(indexnum <= count){
		scanf("%s",buffer);
		(indexnum % 2 ==1)? strcat(odd,buffer) : strcat(even,buffer);
		indexnum ++;
		memset(buffer,0,sizeof(buffer));
	}
	
	/*test*/
	printf("odd string is: %s\neven string is: %s\n",odd,even);
	
	/* big number add */
	bignumadd();

	/* print result */
	printf("%s",result);
}

