ROOT:=.
PROJECT_NAME:=tinkerbox

include $(ROOT)/globals.config

include $(ROOT)/bootloader/make.config
include $(ROOT)/kernel/make.config

ELF:=$(PROJECT_NAME).elf
BIN:=$(PROJECT_NAME).bin

all: make-kernel make-bootloader link $(BIN)

# Build
make-kernel:
	$(MAKE) -C $(KERNEL_ROOT)

make-bootloader:
	$(MAKE) -C $(BOOTLOADER_ROOT)

# Linking
link:
	$(LD) $(LINKER_FLAGS) -T tinkerbox.ld $(BOOTLOADER_OBJS) $(KERNEL_OBJS) -o $(ELF)

%.bin: %.elf
	$(OBJ) $(OBJ_FLAGS) $< $@

#Cleanning
clean: clean-root clean-bootloader clean-kernel

clean-bootloader:
	$(MAKE) -C $(BOOTLOADER_ROOT) clean

clean-kernel:
	$(MAKE) -C $(KERNEL_ROOT) clean

clean-root:
	-rm -f *.elf

run:
	$(QEMU) $(QEMU_FLAGS)$(BIN)
