OBJDIR=obj
SRCDIR=.
BINDIR=bin

define make-obj-c
ifneq ($(MAKECMDGOALS),clean)
$(patsubst %.c,$(OBJDIR)/%.d,$1): $2/$1
	$(CC) $(CFLAGS) -M -MF $$@ -MT $(patsubst %.c,$(OBJDIR)/%.o,$1) $$<
-include $(patsubst %.c,$(OBJDIR)/%.d,$1)
endif
CLEAN_FILES += $(patsubst %.c,$(OBJDIR)/%.d,$1)
$(patsubst %.c,$(OBJDIR)/%.o,$1): $2/$1 $(patsubst %.c,$(OBJDIR)/%.d,$1)
	$(CC) $(CFLAGS) -o $$@ -c $2/$1
CLEAN_FILES += $(patsubst %.c,$(OBJDIR)/%.o,$1)
endef

define make-obj-asm
ifneq ($(MAKECMDGOALS),clean)
$(patsubst %.s,$(OBJDIR)/%.d,$1): $2/$1
	$(AS) $(ASFLAGS) -M -MF $$@ -MT $(patsubst %.s,$(OBJDIR)/%.o,$1) $$<
-include $(patsubst %.s,$(OBJDIR)/%.d,$1)
endif
CLEAN_FILES += $(patsubst %.s,$(OBJDIR)/%.d,$1)
$(patsubst %.s,$(OBJDIR)/%.o,$1): $2/$1
	$(AS) $(ASFLAGS) -o $$@ -c $2/$1
CLEAN_FILES += $(patsubst %.s,$(OBJDIR)/%.o,$1)
endef

define make-link
$(patsubst %.c,$(OBJDIR)/%.o,$1): $2/$1 $(patsubst %.c,$(OBJDIR)/%.d,$1)
	$(CC) $(CFLAGS) -o $$@ -c $2/$1
CLEAN_FILES += $(patsubst %.c,$(OBJDIR)/%.o,$1)
endef
