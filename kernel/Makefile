AC = /opt/cross/bin/i686-elf-as
CXX = /opt/cross/bin/i686-elf-g++
CXXFLAGS  = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

OBJ_DIR = ../build/obj

PROJDIRS := arch/i386 core libc/stdio libc/string terminal

SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.cc")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.h")
ASMFILES := $(shell find $(PROJDIRS) -type f -name "*.s")

ASM_OBJ := $(ASMFILES:.s=.o)
CPP_OBJ := $(SRCFILES:.cc=.o)

ASM_OBJ_WITH_DIR :=  $(addprefix $(OBJ_DIR)/, $(notdir $(ASM_OBJ)))
CPP_OBJ_WITH_DIR :=  $(addprefix $(OBJ_DIR)/, $(notdir $(CPP_OBJ)))

%.o: %.s
	$(AC) $< -o $(OBJ_DIR)/$(@F)

%.o: %.cc
	$(CXX) -c $< -o $(OBJ_DIR)/$(@F) $(CXXFLAGS) 

all: dirs aether

aether: $(ASM_OBJ) $(CPP_OBJ)
	$(CXX) -T arch/i386/linker.ld -o ../build/isodir/boot/aether.bin $(ASM_OBJ_WITH_DIR) $(CPP_OBJ_WITH_DIR) -lgcc -ffreestanding -O2 -nostdlib
	cp arch/i386/grub.cfg ../build/isodir/boot/grub/grub.cfg
	grub-mkrescue -o ../build/aether.iso ../build/isodir/

dirs:
	mkdir -p ../build/obj
	mkdir -p ../build/isodir/boot/grub

