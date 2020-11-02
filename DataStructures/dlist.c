#include <stdlib.h>		/* malloc */
#include <assert.h>

#include "dlist.h"

typedef struct dlist_node_st dlist_node_t;

struct dlist_node_st
{
    void *data; /*store node data*/
    
    dlist_node_t *next;
    dlist_node_t *prev;
};

struct dlist_st
{
    dlist_node_t head;
    dlist_node_t tail;
};

/* ************************* */
dlist_t *DlistCreate(void)
{
	dlist_t *dlist;
	
	dlist = (dlist_t *)malloc(sizeof(dlist_t));
	if (NULL == dlist)
	{
		return (NULL);
	}
	
	(dlist->head).data = NULL;
	(dlist->head).next = &(dlist->tail);
	(dlist->head).prev = NULL;
	
	
	(dlist->tail).data = NULL;
	(dlist->tail).next = NULL;
	(dlist->tail).prev = &(dlist->head);
	
	return (dlist);
}


/* ************************* */
/*  **** Complexity: O(n) ****** */
void DlistDestroy(dlist_t *dlist)
{
	assert (dlist != NULL);
	
	while (!DlistIsEmpty(dlist))
	{
		DlistPopFront(dlist);
	}
	
	free(dlist);
	
	return;
}
/* ************************* */	
/*  **** Complexity: O(n) ****** */
size_t DlistSize(const dlist_t *dlist)
{
	size_t count = 0;
	dlist_iter_t curr = NULL;
	dlist_iter_t end = NULL;
		
	assert (dlist != NULL);  
	
	curr = DlistBegin(dlist);
	end = DlistEnd(dlist);
		
	for (; !DlistIsSameIter(curr, end) ; curr = DlistNext(curr))
	{
		++count;
	}
	
	return (count);
}
/* ************************* */	
/*  **** Complexity: O(1) ****** */
int DlistIsEmpty(const dlist_t *dlist)
{
	assert (dlist != NULL);

	return (DlistIsSameIter(DlistBegin(dlist), DlistEnd(dlist)));	
} 

/* ************************* */
/*  **** Complexity: O(1) ****** */
dlist_iter_t DlistBegin(const dlist_t *dlist)
{

	assert (dlist != NULL);

	return ((dlist->head).next);
}

/* ************************** */
/* **** Complexity: O(1) **** */
dlist_iter_t DlistEnd(const dlist_t *dlist)
{	
	assert (dlist != NULL);
	
	return ((dlist_iter_t)&(dlist->tail));
}

/* ************************** */
/* **** Complexity: O(1) **** */
int DlistIsSameIter(dlist_iter_t iter_1, dlist_iter_t iter_2)
{
	assert (iter_1 != NULL);
	assert (iter_2 != NULL);

	return (iter_1 == iter_2);
}

/* ************************** */
/* **** Complexity: O(1) **** */
dlist_iter_t DlistNext(dlist_iter_t iter)
{
	assert (iter != NULL);
	assert (iter->next != NULL);

	return (iter->next);
}

/* ************************** */
/* **** Complexity: O(1) **** */
dlist_iter_t DlistPrev(dlist_iter_t iter)
{
	assert (iter != NULL);
	assert (iter->prev != NULL);

	return (iter->prev);
}

/* ************************** */
/* **** Complexity: O(1) **** */
dlist_iter_t DlistInsert(dlist_t *dlist, dlist_iter_t where, void *data)
{	
	assert (dlist != NULL);
	assert (where != NULL);
	

	return (DlistInsertAfter(dlist, DlistPrev(where), data));
}

/* ************************** */
/* **** Complexity: O(1) **** */
dlist_iter_t DlistInsertAfter(dlist_t *dlist, dlist_iter_t where, void *data)
{
	dlist_node_t *new_node = NULL;	
	
	assert (dlist != NULL);
	assert (where != NULL);
	assert (where->next != NULL);
	
	new_node = (dlist_node_t *)malloc(sizeof(dlist_node_t));
	if (NULL == new_node)
	{
		return (DlistEnd(dlist));
	}

	new_node->data = data;
	new_node->next = DlistNext(where);
	new_node->prev = where;
	
	(DlistNext(where))->prev = new_node;	
	where->next = new_node;
	
	return (new_node);
}

/* ************************** */
/* **** Complexity: O(1) **** */
dlist_iter_t DlistPushBack(dlist_t *dlist , void *data)
{
	assert (dlist != NULL);
	
	return (DlistInsert(dlist, DlistEnd(dlist), data)); 
}

/* ************************** */
/* **** Complexity: O(1) **** */
dlist_iter_t DlistPushFront(dlist_t *dlist ,void *data)
{
	assert (dlist != NULL);
	
	return (DlistInsert(dlist, DlistBegin(dlist), data)); 
}

/* ************************** */
/* **** Complexity: O(1) **** */
void *DlistGetData(dlist_iter_t where)
{
	assert(where != NULL);
	assert(where->next != NULL);
	
 	return (where->data);
}

/* ************************** */
/* **** Complexity: O(1) **** */
/* returns iter to the next node */
dlist_iter_t DlistErase(dlist_iter_t iter)
{
	dlist_iter_t ret_iter = NULL;
	
	assert(iter != NULL);
	assert(iter->next != NULL);
	
	ret_iter = DlistNext(iter);

	DlistPrev(iter)->next = DlistNext(iter);
	DlistNext(iter)->prev = DlistPrev(iter);
	free(iter);
	
	return (ret_iter);
}

/* ************************** */
/* **** Complexity: O(n) **** */	
/* returns iter_t to upon failure*/
dlist_iter_t DlistFind(dlist_iter_t from,
                         dlist_iter_t to,
                 int (*is_match)
                     (const void *node_data,
                     const void *data,
                     void *param),
                 const void *data,
                  void *param)
{
	dlist_iter_t curr = from;
	
	assert(from != NULL);
	assert(to != NULL);	
	assert(is_match != NULL);
	
	while (!DlistIsSameIter(curr, to) && !is_match(DlistGetData(curr), data, param))
	{
		curr = DlistNext(curr);
	}
	
	return (curr);	
}


/* ************************** */
/* **** Complexity: O(1) **** */			
void *DlistPopFront(dlist_t *dlist)
{
	dlist_iter_t iter_to_pop = NULL;
	void *ret_data = NULL;
	
	assert(dlist != NULL);
	assert(!DlistIsEmpty(dlist));
	
	iter_to_pop = DlistBegin(dlist);
	ret_data = DlistGetData(iter_to_pop);
	
	DlistErase(iter_to_pop);
	
	return (ret_data);
}


/* ************************** */
/* **** Complexity: O(1) **** */			
void *DlistPopBack(dlist_t *dlist)
{
	dlist_iter_t iter_to_pop = NULL;
	void *ret_data = NULL;
	
	assert(dlist != NULL);
	assert(!DlistIsEmpty(dlist));
	
	iter_to_pop = DlistPrev(DlistEnd(dlist));
	ret_data = DlistGetData(iter_to_pop);
	
	DlistErase(iter_to_pop);
	
	return (ret_data);
}
		

/* ************************** */
/* **** Complexity: O(n) **** */			
int DlistForEach(dlist_iter_t from, dlist_iter_t to,
                int (*func)
                (void *node_data,
                void *param),
                void *param)
{
	dlist_iter_t curr = from;
	int ret_func = 0;
	
	assert(from != NULL);
	assert(to != NULL);
	assert(func != NULL);
	
	while (!DlistIsSameIter(curr, to) && !(ret_func = func(DlistGetData(curr), param)))
	{
		curr = DlistNext(curr);
	}
	
	return (ret_func);	
}

/* ************************** */
/* **** Complexity: O(1) **** */			
dlist_iter_t DlistSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to)
{
	dlist_iter_t ret_iter = NULL;

	assert(where != NULL);
	assert(from != NULL);
	assert(to != NULL);
	assert(!DlistIsSameIter(from, to));

	/* general :"move" iters from 'from' until the prev of 'to' before iter 'where' */
	/* a. Save prev of 'to' */
	/* b. Update the next fields of where and prev of 'from' and prev of 'to' */
	/* c. Update the prev fields of to and from */
	/* d. Set prev of 'where' to be the saved prev of 'to' and returns it */ 
	ret_iter = DlistPrev(to);
	
	DlistPrev(to)->next = where;	
	DlistPrev(where)->next = from;
	DlistPrev(from)->next = to;
	
	to->prev = DlistPrev(from);
	from->prev = DlistPrev(where);
	where->prev = ret_iter;
	
	return (ret_iter);
}
	

	
