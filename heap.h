#ifndef HEAP_H
#define HEAP_H

#define HEAP_MIN_CAPACITY 2

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef long heap_key_t;

typedef struct _heap_node_t
{
	heap_key_t k;
	void *v;
	struct _heap_t container;
}heap_node_t;

typedef void (*data_dtor_func_t)(void *);

typedef struct _heap_t
{
	size_t capacity;
	size_t size;
	heap_node_t **nodes;
	data_dtor_func_t dtor;
}heap_t;




static void
safe_free(void **pp);

#define sfree(p) safe_free((void**)&(p))

#endif
