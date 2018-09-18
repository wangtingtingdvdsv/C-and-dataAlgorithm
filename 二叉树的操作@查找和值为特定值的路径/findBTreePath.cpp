#include<stdio.h>
#include<malloc.h>

typedef int USER_TYPE;

#include"BTree.h"

int stringToInteger(char *str);
void showInteger(int data);
void findPath(TREE_NODE *root, int value, int *pathArray, int *result, int *index, int *flag);

void findPath(TREE_NODE *root, int value, int *pathArray, int *result, int *index, int *flag) {
	int i;

	if(root == NULL) {
		return;
	}

	*result += root->data;
	pathArray[(*index)++] = root->data;

	if(*result == value) {
		for(i = 0; i < *index; i++) {
			printf("%d ", pathArray[i]);
		}
		printf("\n");
	}

	findPath(root->leftChild, value, pathArray, result, index, flag);
	
	while(root->data != pathArray[(*index) - 1]) {
		(*result) -= pathArray[--(*index)];
	}

	findPath(root->rightChild, value, pathArray, result, index, flag);
}

void showInteger(int data) {
	printf("%d", data);
}

int stringToInteger(char *str) {
	int i;
	int result = 0;

	for (i = 0; str[i] != 0; i++) {
		result *= 10;
		result += (str[i] - '0');
	}

	return result;
}


void main(void) {
	TREE_NODE *root = NULL;
	int i = 0;
	int array[20] = {0};
	int result = 0;
	int index = 0;
	int flag = 0;

	/*123(45(*78(**))6(99(**)100(**)))*/
	creatBTree(&root, "123(45(*78(**))6(99(**)100(**)))", stringToInteger, &i);
	showBTree(root, showInteger);

	findPath(root, 229, array, &result, &index, &flag);

	fflush(stdin);
	getchar();
}