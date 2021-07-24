# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: buzzer.elf 

#additional rules for files
buzzer_s.elf: ${COMMON_OBJECTS} buzzer.o buzzerMain.o wdInterruptHandler.o stateMachines.o led.o state_advance_s.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

buzzer_c.elf: ${COMMON_OBJECTS} buzzer.o buzzerMain.o wdInterruptHandler.o stateMachines.o led.o state_advance_c.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load_s: buzzer_s.elf
	msp430loader.sh  $^

load_c: buzzer_c.elf
	msp430loader.sh $^

clean: $^
	rm -f *.o *.elf *.*~

buzzer.c: buzzer.h
buzzerMain.c: buzzer.h

