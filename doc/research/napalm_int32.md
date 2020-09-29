## Procedure for switching to real mode, calling a bios interrupt and going back to protected mode

### int32
- Clear interrupts
- Push all general porpuse registers to stack (pusha)
- Move the `use32` routine to 0x7c00 so it can be loaded once in 16 bit mode
- Clear direction flag
- Move to [reloc](#reloc)

### <a name="reloc"></a>reloc
- Save the current 32 bit stack pointerto `stack32_ptr`, the current idt pointer to `idt32_ptr`, the current gdt pointer to `gdt32_ptr`
- Load the new 16 gdt pointer
- Load `intnum` (which interrupt you'd like to call) into `ib`
- Copy `regs` into the 16 bit stack. Napalm sets `esp` to the start of the 16 stack just before doing the `rep`, but I do not know if this is necessary, I'll do it just in case.
- Move to [p_mode16](#p_mode16)

### <a name="p_mode16"></a>p_mode16
- Set the segmentations registers to 16 bit section of the real mode code (?)
- Turn off protected mode
- Move to [r_mode16](#r_mode16)

### <a name="r_mode16"></a>r_mode16
- Load the 16 bit idt
- Call [resetpic](#resetpic) with 0x0870 (?)
- Load `gs`, `fs`, `es`, `ds` and the general porpuse registers from 16 bit stack
- Enable interrupts
- Call interrupt from described in `intnum`. This is done by defining `int` as ``db 0xcd``, and `intnum`'s value is taken from `ib` (Look at [reloc](#reloc))
- Disable all interrupts
- Save eflags, `gs`, `fs`, `es`, `ds` and general porpuse registers into 16 bit stack
- Call [resetpic](#resetpic) with 0x2028 (?)
- Turn protected mode back on
- Move to [p_mode32](#p_mode32)

### <a name="p_mode32"></a>p_mode32
- Set segmentation registers to "data selector" (DATA32) (?)
- Restopre `gdt32_ptr`, and `idt32_ptr`
- Restore 32 bit stack pointer into `esp`
- Copy the contents on the 16 bit stack into regs, but before doing `rep movsb`, clear direction flag
- Restore registers
- Enable interrupts
- Finally, return call

### <a name="resetpic"></a>resetpic
#### Notes: expects bh = master vector, bl = slave vector
- Save state of `ax` into stack
- Send `ICW1_INIT | ICW1_ICW4` to master and slave pic
- Get vector from `bh` and send it master pic
- Get vector from `bl` and send it to slave pic
- Tell master to set slave to `IRQ2`
- Tell slave it's on `IRQ2` of master
- Set `ICW4_8086` to master and slave
- Restore `ax` from stack
- Return function call