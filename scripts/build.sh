#!/bin/bash
cd ../build
/opt/cross/bin/i686-elf-as ../src/arch/i386/boot.s -o boot.o
/opt/cross/bin/i686-elf-g++ -c ../src/kernel/kernel.cc -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
/opt/cross/bin/i686-elf-g++ -c ../src/terminal/terminal.cc -o terminal.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
/opt/cross/bin/i686-elf-g++ -c ../src/libc/string/strlen.cc -o strlen.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
/opt/cross/bin/i686-elf-g++ -c ../src/libc/stdio/printf.cc -o printf.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti


mkdir -p isodir/boot/grub

/opt/cross/bin/i686-elf-g++ -T ../src/arch/i386/linker.ld -o isodir/boot/aether.bin -ffreestanding -O2 -nostdlib boot.o kernel.o terminal.o strlen.o printf.o -lgcc

cp ../src/arch/i386/grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o aether.iso isodir/