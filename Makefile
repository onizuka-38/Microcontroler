MCU = atmega328p
F_CPU = 16000000UL
BAUD = 9600

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS = -std=c11 -Wall -Wextra -Werror -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -Iinclude
LDFLAGS = -mmcu=$(MCU)

TARGET = smart_cooling_controller
SRC = $(wildcard src/*.c src/drivers/*.c src/app/*.c)
OBJ = $(SRC:.c=.o)

all: $(TARGET).hex

$(TARGET).elf: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash: $(TARGET).hex
	$(AVRDUDE) -c arduino -p m328p -P COM3 -b 115200 -U flash:w:$(TARGET).hex:i

clean:
	-del /Q src\*.o src\drivers\*.o src\app\*.o 2>nul
	-del /Q $(TARGET).elf $(TARGET).hex 2>nul

.PHONY: all clean flash
