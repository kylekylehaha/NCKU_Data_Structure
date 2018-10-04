#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 999

int count, oddcount, evencount;
int indexnum = 1;
int oddnumber[MAX_SIZE];
int evennumber[MAX_SIZE];
char odd[MAX_SIZE];
char even[MAX_SIZE];
char buffer[MAX_SIZE];

char *strrev(char *str){
	int i,j;
	int length = strlen(str);
	char temp;

	for(i=0,j=length-1;i<j;i++,j--){
		temp = str[j];
		str[j] = str[i];
		str[i] = temp;
	}
	
	return str;
}

void bignumadd(){
	int i, j, lenodd, leneven, maxlen, sum, carry, zero;
	int *add;
	char *revresult;
	char *revodd, *reveven;

	/* reverse string for add */
	revodd = strrev(odd);
	reveven = strrev(even);

	/* change word to integar */
	lenodd = strlen(revodd);
	for(i=0;i<lenodd;i++)
		oddnumber[i] = revodd[i]-'0';
	leneven = strlen(reveven);
	for(i=0;i<leneven;i++)
		evennumber[i] = reveven[i]-'0';

	/* put zero behind shorter string */
	if(lenodd > leneven){
		maxlen = lenodd;
		for(i = leneven;i<lenodd;i++)
			evennumber[i] = 0;
	}
	else{
		maxlen = leneven;
		for(i = lenodd;i<leneven;i++)
			oddnumber[i] = 0;
	}

	add = malloc(sizeof(int)*maxlen);
	
	/* add oddnumber and evennumber */
	for(i=0, carry=0;i<maxlen;i++){
		sum = oddnumber[i] + evennumber[i] + carry;
		if(sum >=10){
			add[i] = sum -10;
			carry = 1;	
		}
		else{
			add[i] = sum;
			carry = 0;
		}
	}	
	if(carry == 1){
		add[maxlen] = 1;
		maxlen = maxlen +1;
	}

	for(i=maxlen-1;i>=0;i--)
		printf("%d",add[i]);
	printf("\n");
	
	return;
}

int main(){
	/* count how many odd and even */ 
	scanf("%d",&count);
	(count % 2 ==1) ? oddcount = count/2 +1 : oddcount /2;
	evencount = count /2;

	/* strcat buffer to oddstring or evenstring */
	memset(odd,0,sizeof(odd));
	memset(even,0,sizeof(even));
	memset(buffer,0,sizeof(buffer));
	while(indexnum <= count){
		scanf("%s",buffer);
		(indexnum % 2 ==1)? strcat(odd,buffer) : strcat(even,buffer);
		indexnum ++;
		memset(buffer,0,sizeof(buffer));
	}
	
	/* big number add */
	bignumadd();
}
