#include <stdlib.h>
#include "cyclic_buffer.h"

#define CB_IDX(_idx0, _pos, _size) (((_idx0) + (_pos)) % (_size))

struct cyclic_buffer {
	uint64_t size;
	void **buf;
	uint64_t idx0;
	cyclic_buffer_dtor_t dtor;
};

void cb_uninit(cyclic_buffer_t *cb)
{
	struct cyclic_buffer *_cb = (struct cyclic_buffer*)cb;
	int i;

	if (!_cb)
		return;

	if (_cb->dtor) {
		for (i = 0; i < _cb->size; i++)
			_cb->dtor(_cb->buf[i]);
	}
	free(_cb->buf);
	free(_cb);
}

cyclic_buffer_t *cb_init(uint64_t size, cyclic_buffer_dtor_t dtor)
{
	struct cyclic_buffer *_cb;

	_cb = calloc(1, sizeof(struct cyclic_buffer));
	if (!_cb)
		return NULL;

	_cb->buf = calloc(size, sizeof(void*));
	if (!_cb->buf) {
		free(_cb);
		return NULL;
	}

	_cb->size = size;
	_cb->idx0 = 0;
	_cb->dtor = dtor;
	return (cyclic_buffer_t)_cb;
}

uint64_t cb_size(cyclic_buffer_t cb)
{
	struct cyclic_buffer *_cb = (struct cyclic_buffer*)cb;

	return _cb->size;
}

void *cb_at(cyclic_buffer_t cb, uint64_t pos)
{
	struct cyclic_buffer *_cb = (struct cyclic_buffer*)cb;

	return _cb->buf[CB_IDX(_cb->idx0, pos, _cb->size)];
}

int cb_insert(cyclic_buffer_t cb, uint64_t pos, void *e)
{
	struct cyclic_buffer *_cb = (struct cyclic_buffer*)cb;
	void **old;

	if (_cb->size <= pos)
		return -1;

	old = &_cb->buf[CB_IDX(_cb->idx0, pos, _cb->size)];
	if (_cb->dtor && *old)
		_cb->dtor(*old);
	*old = e;

	return 0;
}

int cb_advance(cyclic_buffer_t cb, uint64_t count)
{
	struct cyclic_buffer *_cb = (struct cyclic_buffer*)cb;
	int i;

	for (i = 0; i < count; i++) {
		if (cb_insert(cb, i, NULL))
			return -1;
	}

	_cb->idx0 += count;
	_cb->idx0 %= _cb->size;
	return 0;
}

