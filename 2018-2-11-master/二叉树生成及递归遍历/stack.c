#include <stdio.h>
#include <malloc.h>

#include "mecBase.h"
#include "stack.h"

void *readTop(const MEC_STACK *stack) {
	if(NULL == stack || isStackEmpty(stack)) {
		return NULL;
	}

	return stack->stack[stack->top - 1];
}

void *pop(MEC_STACK *stack) {
	if (NULL == stack || isStackEmpty(stack)) {
		return NULL;
	}

	return stack->stack[--stack->top];
}

boolean push(MEC_STACK *stack, void *data) {
	if (NULL == stack || isStackFull(stack)) {
		return FALSE;
	}
	stack->stack[stack->top++] = data;

	return TRUE;
}

boolean isStackFull(const MEC_STACK *stack) {
	if (NULL == stack) {
		return FALSE;
	}

	return stack->top >= stack->capacity;
}

boolean isStackEmpty(const MEC_STACK *stack) {
	if (NULL == stack) {
		return FALSE;
	}

	return stack->top <= 0;
}

void destoryStack(MEC_STACK **stackHead) {
	if(NULL == *stackHead) {
		return;
	}
	free((*stackHead)->stack);
	free(*stackHead);
	*stackHead = NULL;
}

boolean createStack(MEC_STACK **stackHead, int capacity) {
	MEC_STACK *stack = *stackHead;

	if (NULL != stack) {
		return FALSE;
	}

	stack = (MEC_STACK *) calloc(sizeof(MEC_STACK), 1);
	stack->stack = (void **) calloc(sizeof(void *), capacity);
	stack->capacity = capacity;
	stack->top = 0;

	*stackHead = stack;

	return TRUE;
}
