CC=arm-none-eabi-
CFLAGS = -mcpu=cortex-m3 -gdwarf-2
INCS= -I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)


%.o: %.s 
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe $(CFLAGS) $(INCS) -c $< -o $@

pressure-controller-learn-in-depth.elf : $(OBJ) 
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) -o $@ -Map=Map_file.map

pressure-controller-learn-in-depth.bin: pressure-controller-learn-in-depth.elf
	$(CC)objcopy.exe -O binary $< $@


clean:
	rm -rf *.o *~ *.elf *.hex