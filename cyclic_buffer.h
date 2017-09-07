#ifndef _CYCLIC_BUFFER_
#define _CYCLIC_BUFFER_

typedef unsigned long uint64_t;

typedef void *cyclic_buffer_t;

cyclic_buffer_t *cb_init(uint64_t size);
void cb_uninit(cyclic_buffer_t *cb);

uint64_t cb_size(cyclic_buffer_t cb);
void cb_advance(cyclic_buffer_t cb, uint64_t count);
uint64_t cb_at(cyclic_buffer_t cb, uint64_t pos);
int cb_insert(cyclic_buffer_t cb, uint64_t pos, uint64_t val);
#endif

