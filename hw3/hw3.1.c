#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 1000000
#define MAX_SIZE 1000000
#define TRUE 1
#define FALSE 0

int index_total;
int txt_total;
int *freq;
char *key[MAX_SIZE];
//char key[WORD_SIZE][WORD_SIZE];
char *txt[MAX_SIZE];
char buffer[WORD_SIZE];
char cmp[]="-----";

void init(){
	memset(buffer,0,sizeof(buffer));

	return ;
}

/* check whether token is in key array, and count the frequency*/
void count (char *str){
	int i = 0;
//	printf ("enter func count\n");	
	for (i=0;i<index_total;i++){
		if (strcmp(str,key[i]) == 0){
			freq[i]++;
			break;
		}
	}
	
	return ;
}

void compare(){
	int i, k, check_symbol = FALSE;
	char *token;
	
//	printf("enter func compare\n");
	for (k=0;k<txt_total;k++){
//		printf("now the txt is %s\n",txt[k]);
		token = strtok(txt[k]," ");
		while (token != NULL){
			/*find symbol and move it*/
//			printf("before find symbol, token is %s\n",token);
			for (i=0;i<index_total;i++){
				if (strcmp (token,key[i]) == 0){
					check_symbol = TRUE;
					break;
				}
			}
			if (!check_symbol){
				for (i=0;i<strlen(token);i++){
					if ((token[i]<65) || ((90<token[i]) && (token[i]<97)) || (token[i]>122)){		
						token[i] = '\0';
					}
				}
			}
//			printf ("after find symbol, token is %s\n",token);
			count(token);
//			printf ("after compare(), all freq now is \n");
//			for (i=0;i<index_total;i++)
//				printf ("key is %s; freq is  %d",key[i],freq[i]);
			check_symbol = FALSE;
			token = strtok(NULL," ");
		}
	}

	return ;
}

/* find the max freq and print */
void find_max(){
	int i, j, len, max;
	char *temp;
	char *max_key[WORD_SIZE];
	
//	printf ("enter find_max()\n");
	max = freq[0];
	/* find the max freq */
	for (i=0;i<index_total;i++){
		if ( max < freq[i]){
			max = freq[i];
		}
	}
//	printf ("the max freq is %d\n",max);
//	printf ("check whether max is max\n");
//	for (i=0;i<index_total;i++)
//		printf ("key %s ; freq %d",key[i],freq[i]);
	/* check how many key have same max freq*/
	for (i=0, len = 0;i<index_total;i++){
		if (max == freq[i]){
			max_key[len++] = key[i];
		}
	}	
	/* printf with dictionary*/
//	printf ("before order(), len is %d\n",len);
//	for (i=0;i<len;i++)
//		printf("max_key[%d] : %s\n",i,max_key[i]);
	for (i=0;i<len-1;i++)
		for(j=i+1;j<len;j++){
			if (strcmp (max_key[i],max_key[j]) >0){
				temp = max_key[i];
				max_key[i] = max_key[j];
				max_key[j] = temp;
			}
		}
//	printf("after order()\n");
//	for (i=0;i<len;i++)
//		printf("max_key[%d] : %s\n",i,max_key[i]);
	for (i=0;i<len;i++)
		printf ("%s %d\n",max_key[i],max);

	return ;
}

int main(){
	int i, j, len;
	int repeat = 0;
	char *enter;

	init();

	index_total = 0;
	txt_total = 0;

	while (fgets(buffer,WORD_SIZE,stdin) !=NULL){
		enter = strchr(buffer,'\n');
		*enter = '\0';
		if (strcmp(buffer,cmp) == 0){
			memset(buffer,0,sizeof(buffer));
			while (fgets(buffer,WORD_SIZE,stdin) !=NULL){
				enter = strchr(buffer,'\n');
				*enter = '\0';
				len = strlen(buffer);
				txt[txt_total] = malloc (sizeof(char)*len);
				strcpy(txt[txt_total++],buffer);
				memset(buffer,0,sizeof(buffer));
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
//	printf ("index_total %d ; txt_total %d\n",index_total,txt_total);
//	printf ("print key\n");
//	for (i=0;i<index_total;i++)
//		printf("%s\n",key[i]);
//	printf ("print txt\n");
//	for (i=0;i<txt_total;i++)
//		printf("%s\n",txt[i]);

	freq = malloc(sizeof(int)*index_total);
	for (i=0;i<index_total;i++)
		freq[i] = 0;	

	compare();

	find_max();

	return 0;
}
