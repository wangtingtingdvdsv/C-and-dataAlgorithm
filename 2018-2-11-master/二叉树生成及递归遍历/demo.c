#include <stdio.h>

#include "mecBase.h"
#include "stack.h"
#include "btree.h"

void firstRoot(const BTREE *root);
void middleRoot(const BTREE *root);
void lastRoot(const BTREE *root);

void lastRoot(const BTREE *root) {
	int data;

	if (NULL == root) {
		return;
	}
	lastRoot(root->left);
	lastRoot(root->right);

	data = *((int *) root->data);
	printf("%c ", data);
}

void middleRoot(const BTREE *root) {
	int data;

	if (NULL == root) {
		return;
	}
	middleRoot(root->left);

	data = *((int *) root->data);
	printf("%c ", data);

	middleRoot(root->right);
}

void firstRoot(const BTREE *root) {
	int data;

	if (NULL == root) {
		return;
	}
	data = *((int *) root->data);
	printf("%c ", data);

	firstRoot(root->left);
	firstRoot(root->right);
}

int main(void) {
	BTREE *treeOne = NULL;

	createBTree("tree.txt", &treeOne);

	printf("先根序:\n");
	firstRoot(treeOne);
	printf("\n");

	printf("中根序:\n");
	middleRoot(treeOne);
	printf("\n");

	printf("后根序:\n");
	lastRoot(treeOne);
	printf("\n");

	destoryBTree(&treeOne);

	return 0;
}
