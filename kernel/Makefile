ROOT:=../

include $(ROOT)/globals.config

include make.config

all:	$(KERNEL_OBJS)

%.o: %.c
	$(CC) $(CC_INC_FLAGS) $(CC_FLAGS) -o $@ $<

%.o: %.asm
	$(NASM) $(NASM_FLAGS) $< -o $@

clean:
	-rm -f *.o
	-rm -f utils/*.o