#include <stdlib.h>
#include <stdio.h>
#include "cyclic_buffer.h"

#define SIZE 11
#define SIZE_ADVANCE 4

static void cb_free(void *e)
{
	int *d = (int*)e;

	printf("Freeing element %d\n", *d);
	free(d);
}

int main(int argc, char **argv)
{
	cyclic_buffer_t cb;
	int i;

	cb = cb_init(SIZE, cb_free);
	if (!cb) {
		printf("Failed to create a cyclic buffer\n");
		return -1;
	}

	printf("Initialized cb, size: %lu\n", cb_size(cb));

	printf("\nInitializing %d elements...\n", SIZE);
	for (i = 0; i < cb_size(cb); i++) {
		int *d;

		d = (int*)malloc(sizeof(int));
		if (!d) {
			printf("Failed to allocate an integer\n");
			exit(-1);
		}

		*d = i;
		if (cb_insert(cb, i, d)) {
			printf("failed to insert %d\n", *d);
			continue;
		}
	}

	for (i = 0; i < cb_size(cb); i++) {
		int *n;

		n = cb_at(cb, i);
		if (n)
			printf("cb[%d]: %d\n", i, *n);
		else
			printf("cb[%d]: NULL\n", i);
	}

	printf("\nAdvancing cb by %d...\n", SIZE_ADVANCE);
	cb_advance(cb, SIZE_ADVANCE);

	for (i = 0; i < cb_size(cb); i++) {
		int *n;

		n = cb_at(cb, i);
		if (n)
			printf("cb[%d]: %d\n", i, *n);
		else
			printf("cb[%d]: NULL\n", i);
	}

	printf("\nTrying to add more elements to cb...\n");
	for (i = 0; i < SIZE_ADVANCE+1; i++) {
		int *d;

		d = (int*)malloc(sizeof(int));
		if (!d) {
			printf("Failed to allocate an integer\n");
			exit(-1);
		}

		*d = 20 + i;
		if (cb_insert(cb, SIZE - SIZE_ADVANCE + i, d)) {
			printf("Failed to insert %d\n", *d);
		} else {
			printf("cb[%d] = %d\n", SIZE - SIZE_ADVANCE + i,
				*(int*)cb_at(cb, SIZE - SIZE_ADVANCE + i));
		}
	}

	printf("\nUninitializing cb...\n");
	cb_uninit(cb);
}

