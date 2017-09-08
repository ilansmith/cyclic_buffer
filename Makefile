CC=gcc
AR=ar
CFLAGS=-Wall -Werror -O0 -g -m64
LFLAGS=-lcb -L.
LIBS=libcb.a
OBJS=cyclic_buffer.o

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $<

.PHONY: clean cleanall

libcb.a: cyclic_buffer.o
	$(AR) -r $@ $<

clean:
	@echo "removing executables"
	@rm -f $(APP)
	@echo "removing object files"
	@rm -f *.o *.a

cleanall: clean
	@echo "removing pre compilation files"
	@rm -f *_pre.c
	@echo "removing tag file"
	@rm -f tags

