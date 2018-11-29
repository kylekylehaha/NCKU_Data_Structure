#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 999

int count,oddcount, evencount;
char *odd, *even, *buffer;

void init(){
	odd = malloc(sizeof(char)*MAX_SIZE*oddcount);
	even = malloc(sizeof(char)*MAX_SIZE*evencount);
	buffer = malloc(sizeof(char)*MAX_SIZE);
	memset(odd,0,sizeof(odd));
	memset(even,0,sizeof(even));
	memset(buffer,0,sizeof(buffer));
}

char *reverse(char *str, int *len){
	int i, j;
	char temp;
	int length = strlen(str);

	for (i=0,j=length-1;i<j;i++,j--){
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	*len = length;

	return str;
}

void bignumadd(){
	int i, carry, max ,oddlen,evenlen;
	int *rev_oddnum, *rev_evennum, *result;
	char *rev_odd, *rev_even;

	rev_odd = reverse(odd,&oddlen);
	rev_even = reverse(even,&evenlen);
	rev_oddnum = malloc(sizeof(int)*oddlen);
	rev_evennum = malloc(sizeof(int)*evenlen);
	for (i=0;i<oddlen;i++)
		rev_oddnum[i]= rev_odd[i] - '0';
	for (i=0;i<evenlen;i++)
		rev_evennum[i] = rev_even[i] - '0';
	if (oddlen > evenlen){
		max = oddlen;
		for (i=evenlen;i<oddlen;i++)
			rev_evennum[i] = 0;
	}
	else {
		max = evenlen;
		for (i=oddlen;i<evenlen;i++)
			rev_oddnum[i] = 0;
	}
	result = malloc(sizeof(int)*(max+1));
	for (i=0,carry=0;i<max;i++){
		int sum = rev_oddnum[i] + rev_evennum[i] + carry;
		(sum >= 10)?(carry=1):(carry=0);
		sum = sum%10;
		result[i] = sum;
	}
	if (carry == 1){
		result[max] = 1;
		max = max +1;
	}
	for (i=max-1;i>=0;i--)
		printf("%d",result[i]);
	printf("\n");
	return;
}

int main(){
	int index = 1;

	scanf("%d",&count);
	if (count%2 == 1) 
		oddcount = count/2 + 1;
	else oddcount = count/2;
	evencount = count/2;  

	init ();

	while( index <= count){
		scanf("%s",buffer);
		if (index%2 == 1)
			strcat(odd,buffer);
		else
			strcat (even,buffer);
		index++;
		memset(buffer,0,sizeof(buffer));
	}

	bignumadd();

	return 0;
}
