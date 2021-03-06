#ifndef _CYCLIC_BUFFER_
#define _CYCLIC_BUFFER_

typedef unsigned long uint64_t;

typedef void *cyclic_buffer_t;
typedef void (*cyclic_buffer_dtor_t)(void *e);

cyclic_buffer_t *cb_init(uint64_t size, cyclic_buffer_dtor_t dtor);
void cb_uninit(cyclic_buffer_t *cb);

uint64_t cb_size(cyclic_buffer_t cb);
void *cb_at(cyclic_buffer_t cb, uint64_t pos);
int cb_insert(cyclic_buffer_t cb, uint64_t pos, void *e);
int cb_advance(cyclic_buffer_t cb, uint64_t count);
#endif

