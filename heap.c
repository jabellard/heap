#include <stdlib.h>
#include "heap.h"

#define sfree(p) safe_free((void**)&(p))

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static heap_node_t *
heap_node_create(heap_key_t k, void *v);

static void
heap_node_destroy(heap_node_t *n);

static void
max_heapify(heap_t *h, size_t i);

static void
safe_free(void **pp);

static heap_node_t *
heap_node_create(heap_key_t k, void *v)
{
	heap_node_t *n = malloc(sizeof(heap_node_t));
	if (!n)
	{
		return NULL;
	} // end if
	
	n->k = k;
	n->v = v;
	n->container = NULL;
	return n;
} // end heap_node_create()

static void
heap_node_destroy(heap_node_t *n)
{
	if (!n)
	{
		return;
	} // end if
	
	if (n->v && n->container && n->container->dtor)
	{
		n->container->dtor(n->v);
	} // end if
	
	sfree(n);
} // end heap_node_destroy()

heap_t *
heap_create(size_t capacity, data_dtor_func_t dtor)
{
	if (!dtor)
	{
		return NULL;
	} // end if
	
	size_t _capacity = MAX(HEAP_MIN_CAPACITY, capacity);
	
	heap_t *h = malloc(sizeof(heap_t));
	if (!h)
	{
		return NULL;
	} // end if
	
	h->nodes = malloc(sizeof(heap_node_t *) * _capacity);
	if (!h->nodes)
	{
		sfree(h);
		return NULL;
	} // end if
	
	h->capacity = _capacity;
	h->size = 0;
	h->dtor = dtor;
	
	return h;
} // end heap_create()

void 
heap_destroy(heap_t *h)
{
	 if (!h)
	 {
	 	return;
	 } // end if
	 
	 if (h->nodes)
	 {
	 	 size_t i = 0;
		 for (; i < h->size; i++)
		 {
	 		heap_node_destroy(h->nodes[i]);
	 	 } // end for
	 } // end if
	
	sfree(h);
} // end heap_destory()

int
heap_insert(heap_t *h, heap_key_t k, void *v)
{
	if (!h || h->size == h->capacity || !h->nodes)
	{
		return -1;
	} // end if
	
	heap_node_t *n = heap_node_create(k, v);
	if (!n)
	{
		return -1;
	} // end if
	
	(h->size)++;
	
	n->container = h;
	h->nodes[h->size -1] = n;
	
	size_t i = h->size - 1;
	while (i > 0 && h->nodes[(i - 1) / 2]->k < h->nodes[i]->k)
	{
		heap_node_t *tmp = h->nodes[i];
		h->nodes[i] = h->nodes[(i - 1) / 2];
		h->nodes[(i - 1) / 2] = tmp;
		i = (i - 1) / 2;
	} // end while
	
	return 0;
} // end heap_insert()

heap_node_t *
_heap_get_max(heap_t *h)
{
	if (!h || !h->nodes)
	{
		return NULL;
	} // end if
	
	return h->nodes[0];
} // end _heap_get_max()

void *
heap_get_max(heap_t *h)
{
	heap_node_t *r = _heap_get_max(h);
	
	if (r)
	{
		return r->v;
	} // end if
	
	return NULL;
} // end heap_get_max()

static void
max_heapify(heap_t *h, size_t i)
{
	if (!h || !h->nodes)
	{
		return;
	} // end if
	
	size_t l = 2 * i + 1;
	size_t r = 2 * i + 2; // index problem???
	size_t largest = i;
	
	if (l <= h->size && h->nodes[l] > h->nodes[r])
	{
		largest = l;
	} // end if
	
	if (r <= h->size && h->nodes[r] > h->nodes[largest])
	{
		largest = r;
	} // end if
	
	if (largest != i)
	{
		heap_node_t *tmp = h->nodes[i];
		h->nodes[i] = h->nodes[largest];
		h->nodes[largest] = tmp;
		
		max_heapify(h, largest);
	} // end if
} // end max_heapify()

void
heap_destroy_max(heap_t *h)
{
	if (!h || !h->nodes || !h->size)
	{
		return;
	} // end if
	
	heap_node_destroy(h->nodes[0]);
	
	h->nodes[0] = h->nodes[h->size - 1];
	h->nodes[h->size - 1] = NULL;
	
	(h->size)--;
	
	max_heapify(h, 0);
	
	return;
} // end heap_destory_max()

size_t
heap_get_size(heap_t *h)
{
	if (!h)
	{
		return -1;
	} // end if
	
	return h->size;
} // end heap_get_size()

size_t 
heap_get_capacity(heap_t *h)
{
	if (!h)
	{
		return -1;
	} // end if
	
	return h->capacity;
} // end heap_get_capacity()

static void 
safe_free(void **pp)
{
	if (pp != NULL && *pp != NULL)
	{
		free(*pp);
		*pp = NULL;
	} // end if
} // end safe_free()
