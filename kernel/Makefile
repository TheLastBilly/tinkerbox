ROOT:=../

include $(ROOT)/globals.config

include make.config

all:	$(KERNEL_OBJS)

%.o: %.c
	$(CC) $(CC_FLAGS) -o $@ $<

clean:
	-rm -f *.o
	-rm -f utils/*.o