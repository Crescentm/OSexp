# commands/Makefile

#ENTRYPOINT	= 0x1000
HD		= ../80m.img

ASM		= nasm
DASM		= objdump
CC		= gcc
LD		= ld
ASMFLAGS	= -I ../include/ -f elf
CFLAGS		= -I ../include/ -c -fno-builtin -fno-stack-protector -Wall
LDFLAGS		= -Ttext 0x1000
DASMFLAGS	= -D
LIB		= ../lib/orangescrt.a
BIN		= echo ls mult printA printB disproc pwd stest sum stuid

# All Phony Targets
.PHONY : everything final clean realclean disasm all install

# Default starting position
everything : $(BIN)

install : all clean
	cp ../boot/hd*.bin ./ -v
	cp ../kernel.bin ./ -v
	tar vcf inst.tar kernel.bin $(BIN) hd*.bin
	dd if=inst.tar of=$(HD) seek=`echo "obase=10;ibase=16;(\`egrep -e '^ROOT_BASE' ../boot/include/load.inc | sed -e 's/.*0x//g'\`+\`egrep -e '#define[[:space:]]*INSTALL_START_SECT' ../include/sys/config.h | sed -e 's/.*0x//g'\`)*200" | bc` bs=1 count=`ls -l inst.tar | awk -F " " '{print $$5}'` conv=notrunc

all : realclean everything

final : all clean

clean :
	rm -f *.o

realclean :
	rm -f $(BIN) *.o

kernel.bin :
	cp ../kernel.bin ./

start.o : start.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

echo.o: echo.c ../include/type.h ../include/stdio.h
	$(CC) $(CFLAGS) -o $@ $<

echo : echo.o start.o $(LIB)
	$(LD) $(LDFLAGS) -o $@ $?

ls.o: ls.c ../include/type.h ../include/stdio.h
	$(CC) $(CFLAGS) -o $@ $<

ls : ls.o start.o $(LIB)
	$(LD) $(LDFLAGS) -o $@ $?
mult.o: mult.c ../include/type.h ../include/stdio.h
	$(CC) $(CFLAGS) -o $@ $<

mult : mult.o start.o $(LIB)
	$(LD) $(LDFLAGS) -o $@ $?
printA.o: printA.c ../include/type.h ../include/stdio.h
	$(CC) $(CFLAGS) -o $@ $<

printA : printA.o start.o $(LIB)
	$(LD) $(LDFLAGS) -o $@ $?
printB.o: printB.c ../include/type.h ../include/stdio.h
	$(CC) $(CFLAGS) -o $@ $<

printB : printB.o start.o $(LIB)
	$(LD) $(LDFLAGS) -o $@ $?


disproc.o: disproc.c ../include/type.h ../include/stdio.h
	$(CC) $(CFLAGS) -o $@ $<

disproc : disproc.o start.o $(LIB)
	$(LD) $(LDFLAGS) -o $@ $?

pwd.o: pwd.c ../include/type.h ../include/stdio.h
	$(CC) $(CFLAGS) -o $@ $<

pwd : pwd.o start.o $(LIB)
	$(LD) $(LDFLAGS) -o $@ $?

stest.o: stest.c ../include/type.h ../include/stdio.h
	$(CC) $(CFLAGS) -o $@ $<

stest : stest.o start.o $(LIB)
	$(LD) $(LDFLAGS) -o $@ $?

sum.o: sum.c ../include/type.h ../include/stdio.h
	$(CC) $(CFLAGS) -o $@ $<

sum : sum.o start.o $(LIB)
	$(LD) $(LDFLAGS) -o $@ $?

stuid.o: stuid.c ../include/type.h ../include/stdio.h
	$(CC) $(CFLAGS) -o $@ $<

stuid : stuid.o start.o $(LIB)
	$(LD) $(LDFLAGS) -o $@ $?


