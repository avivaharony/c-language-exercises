#ifndef DLIST_H_    
#define DLIST_H_    

#include <stddef.h>

typedef struct dlist_st dlist_t;

typedef struct dlist_node_st *dlist_iter_t;

dlist_t *DlistCreate(void);

void DlistDestroy(dlist_t* dlist);

/* returns the number of elements in the dlist*/
size_t DlistSize(const dlist_t *dlist);

int DlistIsEmpty(const dlist_t *dlist);

dlist_iter_t DlistBegin(const dlist_t *dlist);

dlist_iter_t DlistEnd(const dlist_t *dlist);

int DlistIsSameIter(dlist_iter_t iter_1, dlist_iter_t iter_2);

dlist_iter_t DlistNext(dlist_iter_t iter);

dlist_iter_t DlistPrev(dlist_iter_t iter);

/* return an iterator to the new data inserted or END upon failure*/
dlist_iter_t DlistInsert(dlist_t *dlist, dlist_iter_t where, void *data);

/* return an iterator to the new data inserted or END upon failure*/
dlist_iter_t DlistInsertAfter(dlist_t *dlist, dlist_iter_t where, void *data);

/* insert to the end of the dlist returns new node, return END upon failure*/
dlist_iter_t DlistPushBack(dlist_t *dlist , void *data);

/* insert to the beginning of the dlist returns new node, return END upon failure*/
dlist_iter_t DlistPushFront(dlist_t *dlist ,void *data);

/* returns node data or Null if the dlist is empty*/
void *DlistGetData(dlist_iter_t where);

/* returns iter to the next node */
dlist_iter_t DlistErase(dlist_iter_t iter);

/* returns iter_t to upon failure*/
dlist_iter_t DlistFind(dlist_iter_t from,
                         dlist_iter_t to,
                 int (*is_match)
                     (const void *node_data,
                     const void *data,
                     void *param),
                 const void *data,
                  void *param);
                 
/* returns the popped data */
void *DlistPopFront(dlist_t *dlist);

/* returns the popped data */
void *DlistPopBack(dlist_t *dlist);

/* send the data from each node to func, along with param. stops in case func fails (return != 0). returns the last call from the user function */
int DlistForEach(dlist_iter_t from, dlist_iter_t to,
                int (*func)
                (void *node_data,
                void *param),
                void *param);

/* returns iter to the last spliced element*/
dlist_iter_t DlistSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to);
    
#endif /*DLIST*/

