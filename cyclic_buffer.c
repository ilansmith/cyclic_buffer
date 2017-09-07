#include <stdlib.h>
#include "cyclic_buffer.h"

#define CB_IDX(_idx0, _pos, _size) (((_idx0) + (_pos)) % (_size))

struct cyclic_buffer {
	uint64_t size;
	uint64_t *buf;
	uint64_t idx0;
};

void cb_uninit(cyclic_buffer_t *cb)
{
	struct cyclic_buffer *_cb = (struct cyclic_buffer*)cb;

	if (!_cb)
		return;

	free(_cb->buf);
	free(_cb);
}

cyclic_buffer_t *cb_init(uint64_t size)
{
	struct cyclic_buffer *_cb;

	_cb = calloc(1, sizeof(struct cyclic_buffer));
	if (!_cb)
		return NULL;

	_cb->buf = calloc(size, sizeof(uint64_t));
	if (!_cb->buf) {
		free(_cb);
		return NULL;
	}

	_cb->size = size;
	_cb->idx0 = 0;
	return (cyclic_buffer_t)_cb;
}

uint64_t cb_size(cyclic_buffer_t cb)
{
	struct cyclic_buffer *_cb = (struct cyclic_buffer*)cb;

	return _cb->size;
}

void cb_advance(cyclic_buffer_t cb, uint64_t count)
{
	struct cyclic_buffer *_cb = (struct cyclic_buffer*)cb;

	_cb->idx0 += count;
	_cb->idx0 %= _cb->size;
}

uint64_t cb_at(cyclic_buffer_t cb, uint64_t pos)
{
	struct cyclic_buffer *_cb = (struct cyclic_buffer*)cb;

	return _cb->buf[CB_IDX(_cb->idx0, pos, _cb->size)];
}

int cb_insert(cyclic_buffer_t cb, uint64_t pos, uint64_t val)
{
	struct cyclic_buffer *_cb = (struct cyclic_buffer*)cb;

	if (_cb->size <= pos)
		return -1;

	_cb->buf[CB_IDX(_cb->idx0, pos, _cb->size)] = val;
	return 0;
}

