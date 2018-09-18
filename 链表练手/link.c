#include <stdio.h>
#include <malloc.h>
#include "link.h"



PointNode* getTail(LinkTable* tableHead) {
	PointNode* p = tableHead->pointHead;
	PointNode* tail = p;
	for (p; p; p = p->next) {
		tail = p;
	}
	return tail;
}

void* removeNode(void* var, LinkTable** tableHead) {
	PointNode* p = (*tableHead)->pointHead;
	PointNode* pre;
	PointNode* temp;
	void* varia;
	for (p; p; p = p->next) {
		if (p->variable == var && p == (*tableHead)->pointHead) {
			temp = p;
			(*tableHead)->pointHead = p->next;
			varia = temp->variable;
			free(temp);
			((*tableHead)->count)--;
			(*tableHead)->tail = getTail(*tableHead);
			return varia;
		}
		else if (p->variable == var && p != (*tableHead)->pointHead)
		{
			temp = p;
			pre->next = temp->next;
			varia = temp->variable;
			free(temp);
			((*tableHead)->count)--;
			(*tableHead)->tail = getTail(*tableHead);
			return varia;
		}
		pre = p;
	}
	printf("不存在您要删除的东西\n");
	return NULL;
}
void* findByIndex(int index, LinkTable* tableHead) {
	PointNode* p = tableHead->pointHead;
	int i = 0;
	printf("通过下标查找（起始下标为1）\n");
	for (p; p; p = p->next) {
		i++;
		if (i == index) {
			return p->variable;
		}
	}
}

void* findByValue(void* var, LinkTable* tableHead) {
	PointNode* p = tableHead->pointHead;
	for (p; p; p = p->next) {
		if (p->variable == var) {
			return var;
		}
	}
}
void* destoryLink(LinkTable** tableHead) {
	PointNode* temp;
	PointNode* p = (*tableHead)->pointHead;
	void* aria;

	if (p != NULL) {
		if (p->next != NULL){
			temp = p->next;
			p->next = temp->next;
			aria = temp->variable;
			free(temp);
			return aria;
			
		}
		if (p->next == NULL) {
			aria = p->variable;
			free(p);
			(*tableHead)->count = 0;
			(*tableHead)->tail = NULL;
			(*tableHead)->pointHead = NULL;
			free(*tableHead);
			*tableHead = NULL;
			return aria;
		}

		return NULL;
	}

	
}

void show(LinkTable* tableHead) {
	PointNode* pointNode = tableHead->pointHead;
	PointNode* p;
	for (p = pointNode; p; p = p->next) {
		printf("%s\n", p->variable);
	}
}
void addNode(LinkTable** tableHead, void* var) {
	int end = 0;
	PointNode* pre;
	PointNode* pointNode = (*tableHead) -> pointHead;
	if (pointNode == NULL) {
		pointNode = createNode(var);
		(*tableHead)->pointHead = pointNode;
		(*tableHead)->tail = pointNode;
	} else {
		pre = (*tableHead)->tail;
		pre->next = createNode(var);
		(*tableHead)->tail = pre->next;
	}
}

PointNode* createNode(void* var) {
	PointNode* node;

	node = (PointNode*)malloc(sizeof(PointNode));
	node->variable = var;
	node->next = NULL;

	return node;
}
/*
void destoryLink(LinkTable** tableHead) {
	PointNode* temp;
	PointNode* p = (*tableHead)->pointHead;
	
	if (p != NULL) {
		while (p->next != NULL){
			temp = p->next;
			p->next = temp->next;
			free(temp);
		}
		free(p);
	}
	
	(*tableHead)->count = 0;
	(*tableHead)->tail = NULL;
	(*tableHead)->pointHead = NULL;
	free(*tableHead);
	*tableHead = NULL;
}
*/
void initLink(LinkTable** tableHead) {
	
	LinkTable* linkTable;
	if (*tableHead != NULL) {
		return;
	}

	linkTable = (LinkTable*)malloc(sizeof(LinkTable));
	linkTable->count = 0;
	linkTable->tail = NULL;
	linkTable->pointHead = NULL;

	*tableHead = linkTable;
}
