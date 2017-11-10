#ifndef HEAP_H
#define HEAP_H

#define HEAP_MIN_CAPACITY 8

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef long heap_key_t;

typedef struct _heap_node_t
{
	heap_key_t k;
	void *v;
	struct _heap_t *container;
}heap_node_t;

typedef void (*data_dtor_func_t)(void *);

typedef struct _heap_t
{
	size_t capacity;
	size_t size;
	heap_node_t **nodes;
	data_dtor_func_t dtor;
}heap_t;

heap_node_t *
heap_node_create(heap_key_t k, void *v);

void
heap_node_destroy(heap_node_t *n);

heap_t *
heap_create(size_t capacity, data_dtor_func_t dtor);

void 
heap_destroy(heap_t *h);

int
heap_insert(heap_t *h, heap_key_t k, void *v);

heap_node_t *
_heap_get_max(heap_t *h);

void *
heap_get_max(heap_t *h);

void
max_heapify(heap_t *h, size_t i);

void
heap_destroy_max(heap_t *h);

size_t
heap_get_size(heap_t *h);

size_t 
heap_get_capacity(heap_t *h);

static void
safe_free(void **pp);

#define sfree(p) safe_free((void**)&(p))

#endif
