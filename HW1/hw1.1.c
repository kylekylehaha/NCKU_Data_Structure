#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_SIZE 1000

int i , icount ;
float number[MAX_SIZE];

void check(){
	int ocount = 0;
	int index = 0;
	int output[icount];

	/*check whether is float or not*/
	for(i=0;i<icount;i++){
		float origin = number[i];
		int x = (int)number[i];
		float y = (float)x;
		if((origin - y) == 0){
			ocount ++;
			output[index] = (int)y;
			index++;
		}
	}

	/*printf*/
	printf("%d\n",ocount);
	for(i=0;i<ocount;i++){
		printf("%d\n",output[i]);
	}

	return ; 	
}

int main(){

	scanf("%d",&icount);
	
	for(i=0;i<icount;i++){
		scanf("%f",&number[i]);
	}

	check();
	
	return 0; 
}
