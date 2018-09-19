#include <stdio.h>
#include <stdlib.h>

int i , j , k, count;

void check(){
	int length = 0;
	int freq = 0;
	int output[count];

	/*check which one freq ==1*/
	for(i=0;i<count;i++){
		scanf("%d",&length);
		int number[length];

		/*scanf ith data*/
		for(j=0;j<length;j++){
			scanf("%d" , &number[j]);
		}

		/*check which one freq is 1*/
		for(j=0;j<length;j++){
			int x = number[j];
			for(k=0;k<length;k++){
				if (x == number[k])
					freq++;
			}

			if(freq == 1){
				output[i] = x;		
			}
			else{
				freq = 0;
			}
		}		
	}

	/*printf output*/
	for(i=0;i<count;i++){
		printf("%d\n",output[i]);
	}

	return ;
}

int main(){
	scanf("%d",&count);

	check();

	return 0 ;
}
