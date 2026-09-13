DEVKITPRO ?= /opt/devkitpro
DEVKITPPC ?= $(DEVKITPRO)/devkitPPC
WIIU_PREFIX ?= $(DEVKITPRO)/wut

CC := $(DEVKITPPC)/bin/powerpc-eabi-gcc
CXX := $(DEVKITPPC)/bin/powerpc-eabi-g++
AS := $(DEVKITPPC)/bin/powerpc-eabi-as
LD := $(DEVKITPPC)/bin/powerpc-eabi-ld
OBJCOPY := $(DEVKITPPC)/bin/powerpc-eabi-objcopy

CFLAGS := -mvsx -O2 -Wall -I$(WIIU_PREFIX)/include
LDFLAGS := -L$(WIIU_PREFIX)/lib -lwut

TARGET := hello_world
SOURCES := source/hello.c
OBJECTS := $(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET).wuhb

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(TARGET).wuhb: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).wuhb