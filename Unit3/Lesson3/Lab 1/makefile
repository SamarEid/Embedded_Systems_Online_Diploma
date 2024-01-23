#Samar Gamal Mahmoud
CC=arm-none-eabi-
CFLAGS=-mcpu=arm926ej-s -g
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
AS=$(wildcard *.s)
ASOBJ=$(AS:.s=.o)
Project_name = learn-in-depth
all: $(Project_name).bin

%.o: %.s 
	$(CC)as.exe $(CFLAGS) $< -o $@ 
%.o: %.c 
	$(CC)gcc.exe $(CFLAGS) $(INCS) -c $< -o $@
$(Project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(ASOBJ) -o $@ -Map=Map_file.map
$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.elf *.bin 

clean:
	rm *.elf *.bin 
