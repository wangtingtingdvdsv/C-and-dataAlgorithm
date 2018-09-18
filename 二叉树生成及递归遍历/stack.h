#ifndef _MEC_STACK_H_
#define _MEC_STACK_H_

#include "mecBase.h"

typedef struct MEC_STACK {
	void **stack;
	int capacity;
	int top;
}MEC_STACK;

boolean createStack(MEC_STACK **stackHead, int capacity);
void destoryStack(MEC_STACK **stackHead);
boolean isStackEmpty(const MEC_STACK *stack);
boolean isStackFull(const MEC_STACK *stack);
boolean push(MEC_STACK *stack, void *data);
void *pop(MEC_STACK *stack);
void *readTop(const MEC_STACK *stack);

#endif
