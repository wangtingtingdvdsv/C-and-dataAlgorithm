#ifndef _B_TREE_H_
#define _B_TREE_H_

#include "mecBase.h"

#define LEFT_CHILD		0
#define RIGHT_CHILD		1

typedef struct BTREE {
	void *data;                                             
	struct BTREE *left;
	struct BTREE *right;
}BTREE;

boolean createBTree(const char *fileName, BTREE **treeHead);
void destoryBTree(BTREE **rootHead);

#endif
