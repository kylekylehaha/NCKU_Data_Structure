#include <stdio.h>
#include <stdlib.h>

int main(){
	int a[] = {2,3,4,8,9,29,34,21,43,1};
	int i, j, temp;
	for (i=0;i<10;i++)
		for (j=0;j<10;j++){
				if (a[i]<a[j]){
					temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
			}
	for (i=0;i<10;i++)
		printf("%d",a[i]);
}

