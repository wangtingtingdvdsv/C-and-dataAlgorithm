#ifndef _LINK_H_
#define _LINK_H_

typedef struct Node{
	void* variable;
	struct Node* next;
}PointNode;

typedef struct linkTable {
	PointNode* tail;
	int count;
	PointNode* pointHead;
}LinkTable;

void initLink(LinkTable** tableHead);
//void destoryLink(LinkTable** tableHead);
PointNode* createNode(void* var);
void addNode(LinkTable** tableHead, void* var);
void show(LinkTable* tableHead);
void* destoryLink(LinkTable** tableHead);
void* findByValue(void* var, LinkTable* tableHead);
void* findByIndex(int index, LinkTable* tableHead);
void* removeNode(void* var, LinkTable** tableHead);
PointNode* getTail(LinkTable* tableHead);
#endif
