#include <stdlib.h>		/* malloc */
#include <assert.h>

#include "slist.h"


slist_node_t *SListCreateAndInitNode(void *data, slist_node_t *next)
{
	slist_node_t *new_node = NULL;
	
	new_node = (slist_node_t *)malloc(sizeof(slist_node_t));
	if (NULL == new_node)
	{
		return (NULL);
	}
	
	new_node->data = data;
	new_node->next = next;
	
	return (new_node);		
}

/*  **** Complexity: O(1) ****** */
slist_node_t *SListInsert(slist_node_t *where, slist_node_t *new_node)
{
	/* Insert new_node after 'where' and Swap data of 'where' and 'new_node' */
	void *temp_data = NULL;

	assert(where != NULL);
	assert(new_node != NULL);
	
	temp_data = where->data;
	where->data = new_node->data;
	new_node->data = temp_data;
	
	new_node->next = where->next;
	where->next = new_node;
	
	return (where);
}

/*  **** Complexity: O(1) ****** */
slist_node_t *SListInsertAfter(slist_node_t *where, slist_node_t *new_node)
{
	assert(where != NULL);
	assert(new_node != NULL);

	new_node->next = where->next;
	where->next = new_node;
		
	return (new_node);
}

/*  **** Complexity: O(1) ****** */
slist_node_t *SListRemove(slist_node_t *node)
{
	/* Copy content of node->next to node and remove node->next */
	slist_node_t *ret_next = NULL;

	assert(node != NULL);
	assert(node->next != NULL);

	ret_next = node->next;
	
	node->data = (node->next)->data;
	node->next = (node->next)->next;
	
	return (ret_next);
}

/*  **** Complexity: O(1) ****** */
slist_node_t *SListRemoveAfter(slist_node_t *node)
{
	slist_node_t *ret_next = NULL;

	assert(node->next != NULL);
	
	ret_next = node->next;
	node->next = (node->next)->next;
	
	return (ret_next);
}

/*  **** Complexity: O(n) ****** */
void SListFreeAll(slist_node_t *head)
{
	slist_node_t *temp_node = NULL;

	while (head != NULL)
	{
		temp_node = head;
		head = head->next;
		
		free(temp_node);
		temp_node = NULL;
	}	
	
	return;
}

/*  **** Complexity: O(n) ****** */
size_t SListCount(const slist_node_t *head)
{
	size_t count = 0;

	for (; head != NULL ; head = head->next)
	{
		++count;
	}
	
	return (count);
}


/*  **** Complexity: O(n) ****** */
slist_node_t *SListFind(slist_node_t *head, int (*is_match)(const void *node_data, const void *data, void *param), const void *data,void *param
                                           )
{

	assert(is_match != NULL);	
		
/* create loop saving next of head and comparing with is_match function. */
/* if one returns from function, returns current node on the loop */
/* if NULL reached -> return NULL */
	while (head != NULL && !(is_match(head->data, data, param)))
	{
		head = head->next;
	}
	
	return (head);
}


/*  **** Complexity: O(n) ****** */
int SListHasLoop(const slist_node_t *head)
/* loop on list from head with two pointers:*/
/* every loop one pointer jump one node ahead and the other two nodes .*/
/* until null (no loop) or until the faster pointer meets the slower one */
{
	const slist_node_t *fast_node = NULL;
	const slist_node_t *slow_node = head;
	
	if (NULL == head)
	{
		return (0);
	}
	
	fast_node = head->next;
	
	while (fast_node != NULL && fast_node->next != NULL)
	{
		if (fast_node == slow_node || fast_node->next == slow_node)
		{
			return (1);
		}
		
		fast_node = fast_node->next->next;
		
		slow_node = slow_node->next;
	}
	
	return (0);
}


/*  **** Complexity: O(n) ****** */
slist_node_t *SListFlip(slist_node_t *head)
{
	slist_node_t *temp_node = NULL;
	slist_node_t *prev_node = NULL;
	
	while (head != NULL)
	{
		temp_node = head->next;
		head->next = prev_node;
		prev_node = head;
		head = temp_node;
	}

	return (prev_node);
}

/*  **** Complexity: O(n) ****** */
int SListForEach(slist_node_t *head, int (*func)(void *node_data, void *param), void *param)
{
	int func_ret_val = 0;

	assert(func != NULL);	
	
	while (head != NULL)
	{
		func_ret_val = func(head->data, param);
		if (func_ret_val != 0)
		{
			return (func_ret_val);
		}
		
		head = head->next;
	}
	
	return (0);
}

/*  **** Complexity: O(n+m) ****** */
slist_node_t *SListFindIntersection(const slist_node_t *head1, const slist_node_t *head2)
{
/*
    Count nodes of the two linked list. 
    calculate the difference between sizes and traverses 'diff' nodes on the longer list.
    (results in placing the two lists at same distance from intersection node)
    walk on each list compare the nodes until finding the common.
*/
 	const slist_node_t *curr_long = NULL;
	const slist_node_t *curr_short = NULL;
	size_t size1, size2, diff = 0;
	
  	size1 = SListCount(head1);
  	size2 = SListCount(head2); 
  	
 	if (size1 > size2)
 	{
 		diff = size1 - size2;
 		curr_long = head1;
 		curr_short = head2;
  	}
  	else
  	{
 		diff = size2 - size1;
  	 	curr_long = head2;
 		curr_short = head1;
	}
	
	/* traverses 'diff' nodes on the longer list, 
	placing the two lists at same distance from intersection node */
	for (; diff > 0; --diff)
	{
		curr_long = curr_long->next;
	}

	 /* walk on each list compare the nodes until finding the common.*/
	while ((curr_long != NULL) && (curr_long != curr_short))
	{
		curr_long = curr_long->next;
		curr_short = curr_short->next;
	}
	
	return ((slist_node_t *)curr_long);	
} 

