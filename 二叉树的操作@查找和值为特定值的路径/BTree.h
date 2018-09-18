#ifndef _B_TREE_H_
#define _B_TREE_H_

#include<stdio.h>
#include<malloc.h>

typedef unsigned char boolean;
#define TRUE		1
#define FALSE	0

#define STATE_START		1
#define STATE_DATA		2

//·¢²¼°æÓ¦É¾µô£»
//typedef int USER_TYPE;

typedef struct TREE_NODE {
	USER_TYPE data;
	struct TREE_NODE *leftChild;
	struct TREE_NODE *rightChild;
} TREE_NODE;

void creatBTree(TREE_NODE **root, char *tree, USER_TYPE stringToUserType(char *), int *index);
void destoryBTree(TREE_NODE **root);
void showBTree(TREE_NODE *root, void showUserType(USER_TYPE));

void showBTree(TREE_NODE *root, void showUserType(USER_TYPE)) {
	if (root == NULL) {
		printf("*");
		return;
	}

	showUserType(root->data);
	printf("(");
	showBTree(root->leftChild, showUserType);
	showBTree(root->rightChild, showUserType);
	printf(")");
}

void destoryBTree(TREE_NODE **root) {
	if (*root == NULL) {
		return;
	}

	destoryBTree(&((*root)->leftChild));
	destoryBTree(&((*root)->rightChild));
	free(*root);
	*root = NULL;
}

//123(45(*78(**))6(99(**)100(**)))
void creatBTree(TREE_NODE **root, char *tree, USER_TYPE stringToUserType(char *), int *index) {
	char nodeData[81] = { 0 };
	int i;

	while (tree[*index] == ')') {
		(*index)++;
	}
	if (tree[*index] == '*') {
		*root = NULL;
		(*index)++;
		return;
	}

	for (i = 0; tree[*index] != '(' && i < 81; i++, (*index)++) {
		nodeData[i] = tree[*index];
	}
	(*index)++;

	if (i != 0) {
		*root = (TREE_NODE *)calloc(1, sizeof(TREE_NODE));
		(*root)->data = stringToUserType(nodeData);

		creatBTree(&((*root)->leftChild), tree, stringToUserType, index);
		creatBTree(&((*root)->rightChild), tree, stringToUserType, index);
	}
}

#endif // !_B_TREE_H_
