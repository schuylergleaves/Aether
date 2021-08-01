AC = /opt/cross/bin/i686-elf-as
CXX = /opt/cross/bin/i686-elf-g++
CXXFLAGS  = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
ISOFLAGS = -lgcc -nostdlib
LINKER = -T arch/i386/linker.ld

BUILD_DIR = ../build
OBJ_DIR = $(BUILD_DIR)/obj
ISO_DIR = $(BUILD_DIR)/isodir
BOOT_DIR = $(ISO_DIR)/boot
GRUB_DIR = $(BUILD_DIR)/isodir/boot/grub
INCLUDE_DIR = .

# add any new src/header directories here
PROJECT_DIRS := arch/i386 core libc/stdio libc/string terminal

SRC_FILES := $(shell find $(PROJECT_DIRS) -type f -name "*.cc")
ASM_FILES := $(shell find $(PROJECT_DIRS) -type f -name "*.s")

ASM_OBJ_WITH_SRC_DIR := $(ASM_FILES:.s=.o)
CPP_OBJ_WITH_SRC_DIR := $(SRC_FILES:.cc=.o)

ASM_OBJ_WITH_OBJ_DIR :=  $(addprefix $(OBJ_DIR)/, $(notdir $(ASM_OBJ_WITH_SRC_DIR)))
CPP_OBJ_WITH_OBJ_DIR :=  $(addprefix $(OBJ_DIR)/, $(notdir $(CPP_OBJ_WITH_SRC_DIR)))

%.o: %.s
	$(AC) $< -o $(OBJ_DIR)/$(@F)

%.o: %.cc
	$(CXX) -c $< -o $(OBJ_DIR)/$(@F) $(CXXFLAGS) -I$(INCLUDE_DIR)

.PHONY: DIRS ISO CLEAN

all: DIRS ISO

ISO: $(ASM_OBJ_WITH_SRC_DIR) $(CPP_OBJ_WITH_SRC_DIR)
	$(CXX) $(LINKER) -o $(BOOT_DIR)/aether.bin $(ASM_OBJ_WITH_OBJ_DIR) $(CPP_OBJ_WITH_OBJ_DIR) $(CXXFLAGS) $(ISOFLAGS)
	cp arch/i386/grub.cfg $(GRUB_DIR)/grub.cfg
	grub-mkrescue -o $(BUILD_DIR)/aether.iso $(ISO_DIR)

DIRS:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(GRUB_DIR)

CLEAN:
	rm -rf $(BUILD_DIR)/*

