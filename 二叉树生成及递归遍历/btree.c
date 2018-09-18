#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

#include "mecBase.h"
#include "stack.h"
#include "btree.h"

const int BT_END_SIGN = '#';

enum BTreeStatus {
	BT_BEGIN,
	BT_FIRST_ALPHA,
	BT_LEFT_BRACKET,
	BT_ALPHA,
	BT_RIGHT_BRACKET,
	BT_COMMA,
	BT_END,
	BT_ERROR,
};

typedef struct BT_PARA {
	boolean ok;
	FILE *in;
	int status;
	int bracketMatch;
	boolean whichChild;
	MEC_STACK *stack;
	BTREE *root;
	BTREE *node;
}BT_PARA;

static BTREE *initBtree(FILE *in);
static void skipBlankInFile(FILE *in);
static void dealBtreeBegin(int ch, BT_PARA *para);
static void dealBtreeFirstAlpha(int ch, BT_PARA *para);
static void dealBtreeLeftBracket(int ch, BT_PARA *para);
static void dealBtreeComma(int ch, BT_PARA *para);
static void dealBtreeAlpha(int ch, BT_PARA *para);
static void dealBtreeRightBracket(int ch, BT_PARA *para);
static void processLeftBracket(BT_PARA *para);
static void processRightBracket(BT_PARA *para);
static void processComma(BT_PARA *para);
static void processAlpha(int ch, BT_PARA *para);
static long getFileSize(FILE *in);
static BTREE *createBtreeNode(int ch);
static void destoryBtree(BTREE *root);

static void destoryBtree(BTREE *root) {
	if (NULL == root) {
		return;
	}

	destoryBtree(root->left);
	destoryBtree(root->right);

	free(root->data);
	free(root);
}

void destoryBTree(BTREE **rootHead) {
	BTREE *root = *rootHead;

	if (NULL == root) {
		return;
	}
	destoryBtree(root);

	rootHead = NULL;
}

static BTREE *createBtreeNode(int ch) {
	int *data = (int *) malloc(sizeof(int));
	BTREE *node = (BTREE *) calloc(sizeof(BTREE), 1);

	*data = ch;
	node->data = (void *)data;
	node->left = node->right = NULL;

	return node;
}

static long getFileSize(FILE *in) {
	long size;

	fseek(in, 0, SEEK_END);
	size = ftell(in);
	fseek(in, 0, SEEK_SET);

	return size;
}

static void processAlpha(int ch, BT_PARA *para) {
	BTREE *node = createBtreeNode(ch);
	BTREE *parent = NULL;

	para->node = node;
	parent = readTop(para->stack);
	if (NULL == parent) {
		printf("出现严重的未知错误！\n");
		para->ok = FALSE;
		return;
	}

	if (LEFT_CHILD == para->whichChild) {
		parent->left = node;
		return;
	}

	if (parent->right == NULL) {
		parent->right = node;
		return;
	}
	printf("子孩子数量超过2个！\n");
	para->ok = FALSE;
}

static void processComma(BT_PARA *para) {
	para->whichChild = RIGHT_CHILD;
}

static void processRightBracket(BT_PARA *para) {
	if (--para->bracketMatch < 0) {
		printf("缺少左括号！\n");
		para->ok = FALSE;
		return;
	}
	pop(para->stack);
}

static void processLeftBracket(BT_PARA *para) {
	++para->bracketMatch;
	push(para->stack, para->node);
	para->whichChild = LEFT_CHILD;
}

static void dealBtreeRightBracket(int ch, BT_PARA *para) {
	if (')' == ch) {
		processRightBracket(para);
		para->status = BT_RIGHT_BRACKET;
	} else if (',' == ch) {
		processComma(para);
		para->status = BT_COMMA;
	} else if (BT_END_SIGN == ch) {
		para->status = BT_END;
	} else {
		printf("右括号后出现不可识别的符号！\n");
		para->ok = FALSE;
	}
}

static void dealBtreeAlpha(int ch, BT_PARA *para) {
	if ('(' == ch) {
		processLeftBracket(para);
		para->status = BT_LEFT_BRACKET;
	} else if (')' == ch) {
		processRightBracket(para);
		para->status = BT_RIGHT_BRACKET;
	} else if (',' == ch) {
		processComma(para);
		para->status = BT_COMMA;
	} else {
		printf("数值后出现不可识别的符号！\n");
		para->ok = FALSE;
	}
}

static void dealBtreeComma(int ch, BT_PARA *para) {
	if (isalnum(ch)) {
		processAlpha(ch, para);
		para->status = BT_ALPHA;
	} else if (')' == ch) {
		processRightBracket(para);
		para->status = BT_RIGHT_BRACKET;
	} else {
		printf("逗号后出现不可识别字符！\n");
		para->ok = FALSE;
	}
}

static void dealBtreeLeftBracket(int ch, BT_PARA *para) {
	if (isalnum(ch)) {
		processAlpha(ch, para);
		para->status = BT_ALPHA;
	} else if (',' == ch) {
		processComma(para);
		para->status = BT_COMMA;
	} else {
		printf("左括号后出现不可识别字符！\n");
		para->ok = FALSE;
	}
}

static void dealBtreeFirstAlpha(int ch, BT_PARA *para) {
	if ('(' == ch) {
		processLeftBracket(para);
		para->status = BT_LEFT_BRACKET;
	} else if (BT_END_SIGN == ch) {
		para->status = BT_END;
	} else {
		printf("节点数值必须是单字母或单数字；或者出现错误的符号！\n");
		para->ok = FALSE;
	}
}

static void dealBtreeBegin(int ch, BT_PARA *para) {
	if (isalnum(ch)) {
		BTREE *node = createBtreeNode(ch);
		para->status = BT_FIRST_ALPHA;
		para->root = node;
		para->node = node;
	} else {
		printf("无效的根节点数值！\n");
		para->ok = FALSE;
	}
}

static void skipBlankInFile(FILE *in) {
	int ch;

	ch = fgetc(in);
	while(isspace(ch) && !feof(in)) {
		ch = fgetc(in);
	}
	if(!feof(in)) {
		ungetc(ch, in);
	}
}

static BTREE *initBtree(FILE *in) {
	int ch;
	BT_PARA para = {
		TRUE,		// boolean ok;
		in,			// FILE *in;
		BT_BEGIN,	// int status;
		0,			// int bracketMatch;
		LEFT_CHILD,	// boolean whichChild;
		NULL,		// MEC_STACK *stack;
		NULL, 		// BTREE *root;
		NULL,		// BTREE *node;
	};
	boolean finished = FALSE;
	int capacity;

	capacity = (int) (getFileSize(in) >> 1);
	createStack(&para.stack, capacity);

	skipBlankInFile(in);
	ch = fgetc(in);
	while(para.ok && !finished && !feof(in)) {
		switch (para.status) {
		case BT_BEGIN :
			dealBtreeBegin(ch, &para);
			break;
		case BT_FIRST_ALPHA :
			dealBtreeFirstAlpha(ch, &para);
			break;
		case BT_LEFT_BRACKET :
			dealBtreeLeftBracket(ch, &para);
			break;
		case BT_COMMA :
			dealBtreeComma(ch, &para);
			break;
		case BT_ALPHA :
			dealBtreeAlpha(ch, &para);
			break;
		case BT_RIGHT_BRACKET :
			dealBtreeRightBracket(ch, &para);
			break;
		case BT_END :
			finished = TRUE;
			break;
		default :
			break;
		}

		skipBlankInFile(in);
		ch = fgetc(in);
	}

	destoryStack(&para.stack);
	if(para.ok) {
		return para.root;
	}
	destoryBTree(&para.root);

	return NULL;
}

boolean createBTree(const char *fileName, BTREE **treeHead) {
	BTREE *tree = *treeHead;
	FILE *in;

	if(NULL != tree) {
		return FALSE;
	}

	in = fopen(fileName, "r");
	if(NULL == in) {
		printf("文件[%s]打开失败！\n", fileName);
		return FALSE;
	}

	*treeHead = initBtree(in);

	fclose(in);

	return TRUE;
}
