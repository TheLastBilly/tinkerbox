ROOT:=.
PROJECT_NAME:=tinkerbox

include $(ROOT)/globals.config

include $(ROOT)/bootloader/make.config
include $(ROOT)/kernel/make.config
include $(ROOT)/libc/make.config

ELF:=$(PROJECT_NAME).elf
BIN:=$(PROJECT_NAME).bin

rebuild: clean all

all: make-kernel make-libc make-bootloader link binary

# Build
make-kernel:
	$(MAKE) -C $(KERNEL_ROOT)

make-bootloader:
	$(MAKE) -C $(BOOTLOADER_ROOT)

make-libc:
	$(MAKE) -C $(LIBC_ROOT)

# Linking
link:
	$(LD) $(LINKER_FLAGS) -T linker.ld $(BOOTLOADER_OBJS) $(KERNEL_OBJS) $(LIBC_OBJS) -o $(ELF)

binary:
	$(OBJCOPY) $(OBJ_FLAGS) $(ELF) $(BIN)

#Cleanning
clean: clean-root clean-bootloader clean-kernel clean-libc

clean-bootloader:
	$(MAKE) -C $(BOOTLOADER_ROOT) clean

clean-kernel:
	$(MAKE) -C $(KERNEL_ROOT) clean

clean-libc:
	$(MAKE) -C $(LIBC_ROOT) clean

clean-root:
	-rm -f *.elf
	-rm -f tinkerbox.bin

run:
	$(QEMU) $(QEMU_FLAGS)$(BIN)
