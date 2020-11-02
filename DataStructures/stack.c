#include <stdio.h>	
#include <stdlib.h>		/* malloc */
#include <string.h> 	/* memmove */
#include <assert.h>
#include "stack.h"

/* enum defintions */
enum ret_values { success = 0, stack_full = 1 };

struct stack_st
{
	size_t element_size;
	char *end; 			/* Pointer to end of stack available area 	*/
	char *top ;			/* Pointer to element on top of stack		*/
	
	char data[1];

};


/* Returns pointer to a new Created stack with given number of elements , and given element size .  Returns NULL pointer if malloc failed   */ 
stack_t *StackCreate(size_t num_elements, size_t element_size)
{
	stack_t *stack = NULL;
	
	/* Alloacate memory for stack, with size for the struct and the elements  */
	stack = (stack_t *)malloc(sizeof(stack_t) + (num_elements * element_size));	
	if (NULL == stack)
	{
		return NULL;
	}
				
	/* Set element_size field ,and pointer to end of available stack   */
	stack->element_size = element_size ;
	stack->end = stack->data + num_elements * element_size ;
	/* set top stack pointer to data */
	stack->top = stack->data ;
	/* return new stack_t pointer */
	return stack;
}

/* ************************************************************************************ */

/* Destroy stack and all it's elements */
void StackDestroy(stack_t *stack)
{
	assert(stack != NULL);
	/* free stack */
	free(stack);
	stack =  NULL ; 
}


/* ************************************************************************************ */

/* Removes last element from stack */
void StackPop(stack_t *stack)
{
	assert(stack != NULL);
	/* decrease top of stack pointer by stack element size */
	if (stack->top > stack->data)
	{
		stack->top -= stack->element_size;
	}	
}



/* ************************************************************************************ */
/* Adds a new element to stack , returns 0 for success and 1 for failure (Full Stack) */
int StackPush(stack_t *stack, const void * new_element)
{

	assert(stack != NULL);
	/* if stack top pointer didn't reach end pointer,				*/
	/* update stack top pointer and then copy new_element to stack . */
	if (stack->top < stack->end)
	{
		stack->top += stack->element_size;
		memmove(stack->top, new_element, stack->element_size);
	}
	else
	{
		return stack_full;
	}
	
	return success;
}
/* ************************************************************************************ */
/* returns the last element in the stack  */
void *StackPeek(const stack_t *stack)
{
	assert(stack != NULL);
	
	return stack->top;
}
	


/* ************************************************************************************ */
/* returns stack number of elements */
size_t StackSize(const stack_t *stack)
{
	assert(stack != NULL);
	
	return ((stack->top - stack->data) / stack->element_size);
}


