#include <stdlib.h> /* malloc, free */
#include <assert.h> 

#include "slist.h" 
#include "queue.h"

struct queue_st
{
	slist_node_t *head;		/* first node of the queue */
	slist_node_t *tail;		/* last node of the queue */
};

queue_t *QueueCreate(void)
{
	queue_t *queue = NULL;
	slist_node_t *dummy = NULL;
	
	queue = (queue_t *)malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return (NULL);
	}
	
	dummy = SListCreateAndInitNode(NULL, NULL);
	if (dummy == NULL)
	{
		free(queue);
		return (NULL);
	}
	
	queue->head = dummy;
	queue->tail = dummy;
	
	return(queue);
}	
/*********************************/
/*  **** Complexity: O(n) ****** */
void QueueDestroy(queue_t *queue)
{
	assert(queue != NULL);

	SListFreeAll(queue->head);	/*  frees also dummy */

	free(queue);
	
	return;
}
/*********************************/
/*  **** Complexity: O(n) ****** */
size_t QueueSize(const queue_t *queue)
{
	assert(queue != NULL);
			
	return (SListCount(queue->head) - 1); /* decrease dummy element */
}
/*********************************/
/*  **** Complexity: O(1) ****** */
int QueueIsEmpty(const queue_t *queue)
{
	assert(queue != NULL);
	
	return (queue->head == queue->tail);
}
/*********************************/
/*  **** Complexity: O(1) ****** */
int QueueEnqueue(queue_t *queue, void *data)
{
	slist_node_t *new_node = NULL;
	
	assert(queue != NULL);
	
	new_node = SListCreateAndInitNode(data, NULL);
	if (NULL == new_node)
	{
		return (1);
	}
	
	/* Update tail to point on dummy */
	queue->tail = (SListInsert(queue->tail, new_node))->next;

	return (0);
}
/*********************************/
/*  **** Complexity: O(1) ****** */
void *QueueDequeue(queue_t *queue)
{
	void *ret_data = NULL;
	slist_node_t *removed_node = NULL;
		
	assert(queue != NULL);
	
	if (QueueIsEmpty(queue))
	{
		return (NULL);
	}
		
	ret_data = queue->head->data;

	removed_node = SListRemove(queue->head);
	
	/* update tail if last element was removed */
	if (removed_node == queue->tail)
	{
		queue->tail = queue->head;
	}
	
	free(removed_node);
	
	return (ret_data);
}
/*********************************/
/*  **** Complexity: O(1) ****** */
void *QueuePeek(const queue_t *queue)
{
	assert(queue != NULL);

	if (QueueIsEmpty(queue))
	{
		return (NULL);
	}
	
	return ((queue->head)->data);
}
/*********************************/
/*  **** Complexity: O(1) ****** */
void QueueAppend(queue_t *to, queue_t *from)
{
	slist_node_t *dummy = NULL;
		
	/* connect tail of 'to' queue to head of 'from' queue */
	/* Then empty 'from', using the removed dummy node of 'to' */  

	assert(to != NULL);
	assert(from != NULL);

	if (!QueueIsEmpty(from))
	{
		(to->tail)->next = from->head;

		dummy = SListRemove(to->tail);
	
		dummy->data = NULL;
		dummy->next = NULL;

		to->tail = from->tail;
		from->head = from->tail = dummy;

	}	
	
	return;
}

