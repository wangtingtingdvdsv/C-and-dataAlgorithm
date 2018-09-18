#ifndef _MIN_STACK_H_
#define _MIN_STACK_H_

#include<stdio.h>
#include<malloc.h>

#define MAX_LENGTH	100

#define BIGGER		0
#define SMALLER		1
#define EQUAL		2

//TEMP CODE
typedef int USER_TYPE

typedef struct STACK_ELE {
	USER_TYPE data;
	USER_TYPE minData;
}STACK_ELE;

typedef struct STACK_HEAD {
	int topIndex;
	STACK_ELE *dataArray;
}STACK_HEAD;

int initMinStack(STACK_HEAD **stackHead);
void destory(STACK_HEAD **stackHead);
USER_TYPE pop(STACK_HEAD *stackHead);
int push(STACK_HEAD *stackHead, USER_TYPE data, int compare*(USER_TYPE, USER_TYPE));
USER_TYPE getMinValue(STACK_HEAD stackHead);

USER_TYPE getMinValue(STACK_HEAD stackHead) {
	return stackHead.dataArray[stackHead.topIndex].minData;
}

/*
The compare() function must return a value from BIGGER¡¢SMALLER and EQUAL;
*/
int push(STACK_HEAD *stackHead, USER_TYPE data, int compare*(USER_TYPE, USER_TYPE)) {
	STACK_ELE newEle = {0};

	if(staclHead->topIndex >= MAX_LENGTH) {
		return 0;
	}

	newEle.data = data;
	newEle.minData = compare(stackHead->dataArray[stackHead->topIndex].minData, data) == BIGGER ? data : stackHead->dataArray[stackHead->topIndex].minData;
	
	stackHead->dataArray[++stackHead] = newEle;

	return 1;
}

USER_TYPE pop(STACK_HEAD *stackHead) {
	return stackHead->dataArray[stackHead->topIndex--].data;
}

void destory(STACK_HEAD **stackHead) {
	if(NULL == *stackHead) {
		return;
	}

	free((*stackHead)->dataArray);
	free(*stackHead);
	*stackHead = NULL;
}

int initMinStack(STACK_HEAD **stackHead) {
	if(NULL != *stackHead) {
		return 0;
	}

	*stackHead = (STACK_HEAD *)calloc(1, sizeof(STACK_HEAD));
	(*stackHead)->dataArray = (STACK_ELE *)calloc(MAX_LENGTH, sizeof(STACK_ELE));
	(*stackHead)->topIndex = -1;

	return 1;
}

#endif