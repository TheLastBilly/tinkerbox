ROOT:=../

include $(ROOT)/globals.config

include make.config

all:	$(BOOTLOADER_OBJS)

%.o: %.asm
	$(NASM) $(NASM_FLAGS) $< -o $@

clean:
	-rm -f $(BOOTLOADER_OBJS)