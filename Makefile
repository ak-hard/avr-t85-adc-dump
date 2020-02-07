DEVICE  = attiny85
COMMON_FLAGS = -g -mmcu=$(DEVICE) -DNDEBUG -DTX=1
CFLAGS += $(COMMON_FLAGS) -std=gnu89 -O3 -fdata-sections -ffunction-sections -mno-call-prologues -Wall -Wextra

ASFLAGS = $(COMMON_FLAGS) -x assembler-with-cpp
LDFLAGS = -g -mmcu=$(DEVICE) -Wl,--gc-sections,-Map=$@.map

include Makefile.inc

CC      = avr-gcc
AS      = avr-gcc
LD      = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE    = avr-size
NM      = avr-nm

BINARIES = main
all: $(patsubst %,$(BINDIR)/%,$(BINARIES))

MAIN_SRC = main.c
MAIN_ASM = sw_uart_div4.s
MAIN_OBJ += $(patsubst %.c, $(OBJDIR)/%.o, $(MAIN_SRC))
MAIN_OBJ += $(patsubst %.s, $(OBJDIR)/%.o, $(MAIN_ASM))
$(foreach d,$(MAIN_SRC),$(eval $(call make-obj-c,$d,$(SRCDIR))))
$(foreach d,$(MAIN_ASM),$(eval $(call make-obj-asm,$d,$(SRCDIR))))

ALL_OBJ = $(MAIN_OBJ)

$(BINDIR)/main: Makefile $(ALL_OBJ)
	$(LD) $(LDFLAGS) -o $@ $(ALL_OBJ)
	$(OBJCOPY) -j .text -j .data -j .eeprom -j .fuse -O ihex $@ $@.hex
	$(OBJDUMP) -h -S -C $@ >$@.lst
	$(SIZE) -C --mcu=$(DEVICE) $@

clean:
	-rm $(ALL_OBJ) $(BINDIR)/*

-include $(shell mkdir $(OBJDIR) 2>/dev/null) $(wildcard $(OBJDIR)/*.d)
