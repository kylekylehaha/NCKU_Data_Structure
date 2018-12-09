#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 100

typedef struct NODE *NodePointer;
typedef struct NODE{
	char *str;
	int value;
	NodePointer left;
	NodePointer right;
	NodePointer parent;			//easy to delete node
}NODE;

NodePointer root;

void create_node(NodePointer *ptr, char *string){
	NodePointer temp;
	temp = malloc (sizeof(*temp));
	temp -> value = 1;
	temp -> str = string;
	temp -> left = NULL;
	temp -> right = NULL;
	temp -> parent = NULL;
	*ptr = temp;

	return;
}

NodePointer search(NodePointer tree, char *string){
	while (tree){
		char *temp = tree->str;
		if (strcmp(temp,string) == 0) return tree;
		else if (strcmp(string, temp) >0) tree = tree->right;
		else tree = tree->left; 
	}

	return NULL;
}

void insert(char *string){
	NodePointer insert_pos, check, ptr, temp = search(root,string);
	
	check = root;
	insert_pos = NULL;
	create_node(&ptr,string);
	if (!root){
		root = ptr;
		return ;
	}
	if (!temp){			//string haven't be in the tree
		while (check != NULL){
			/* find right insert position*/
			insert_pos = check;
			if (strcmp(string,check->str) >0) check = check -> right;
			else if (strcmp(string,check->str) <0) check = check->left;
		}
		ptr ->parent = insert_pos;
		if (strcmp(string,insert_pos->str) >0) insert_pos ->right = ptr;
		else insert_pos -> left = ptr;
	}
	else{			//String have be  in the tree
		(temp -> value) ++;
	}	

	return ;
}

/*find the min of delete node of subtree*/
NodePointer Predecessor(NodePointer delete){
	NodePointer temp = delete->left;

	while (temp->right){
		temp = temp ->right;
	}

	return temp;
}

void delete (char *string){
	//NodePointer y -- 最後會被free掉的
	//NOdePointer x -- 最後會被free掉的child
	NodePointer x, y, delete_node = search(root,string);
		
	if (!root || !delete_node){
		printf("There is no node with correct string in the tree\n");
		exit(1);
	}
	(delete_node ->value)--;
	if ((delete_node -> value) ==0){
		//case 1: have two child --need to find Successor or Predecessor
		//casw 2: have one child 
		//case 3: have no child
		//case 2 & case3 can deal with together
		if (delete_node ->left ==NULL || delete_node ->right ==NULL) //先把y找到，使case1變成case 2跟case3的處理方式
			y = delete_node;
		else 
			y = Predecessor(delete_node);
		
		if (y ->left !=NULL) 		//找到y的child 即便沒有child ,x 會是NULL
			x = y->left;
		else 
			x = y->right;
		
		if (x != NULL)			//把x 連接回BST
			x->parent = y->parent;
		
		if (y -> parent ==NULL) 
			root = x;
		else if (y == y->parent->left) 
			y->parent->left = x;
		else 
			y->parent->right = x;
		
		if (y!=delete_node){
			delete_node->str = y->str;
			delete_node->value = y->value;
		}
		free(y);
	}
		
	return ;
}

void process(char *string){
	int len_without_op = strlen(string) -1;
	char op = string[0];
//	char str_without_op[len_without_op];
//	memset(str_without_op,0,sizeof(str_without_op));
// if use array , the memory will disappear when function is end
	char *str_without_op;
	str_without_op = calloc(len_without_op,sizeof(char));	
	strcpy(str_without_op, string+1);
	if (op == '+'){
		insert(str_without_op);	
	}
	else {
		delete(str_without_op);
	}

	return ;
}

void preorder_travel(NodePointer current){
	if (current){
		printf("%s %d\n",current->str,current->value);
		preorder_travel(current->left);
		preorder_travel(current->right);
	}

	return ;
}

int main(int argc, char *argv[]){
	int i;
	char *enter;
	char buffer[WORD_SIZE];

	memset(buffer,0,sizeof(buffer));
	root = NULL;
	while (fgets(buffer,WORD_SIZE,stdin) != NULL){
		enter = strchr(buffer,'\n');
		*enter = '\0';
		process (buffer);
		memset(buffer,0,sizeof(buffer));
	}
	// input with feof

/*	for (i=1;i<argc;i++){
		process(argv[i]);
	}	
*/
	preorder_travel(root);

	return 0;	
}
