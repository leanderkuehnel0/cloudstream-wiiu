CC := /opt/devkitpro/devkitPPC/bin/powerpc-eabi-gcc
CXX := /opt/devkitpro/devkitPPC/bin/powerpc-eabi-g++
AS := /opt/devkitpro/devkitPPC/bin/powerpc-eabi-as
LD := /opt/devkitpro/devkitPPC/bin/powerpc-eabi-ld
OBJCOPY := /opt/devkitpro/devkitPPC/bin/powerpc-eabi-objcopy

WIIU_PREFIX := /opt/devkitpro/wut

CFLAGS := -mvsx -O2 -Wall -I$(WIIU_PREFIX)/include
LDFLAGS := -L$(WIIU_PREFIX)/lib -lwut

TITLE_ID := 0x0005000010123400
TITLE_VERSION := 0

TARGET := forwarder
SOURCES := source/forwarder.c
OBJECTS := $(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET).rpx

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(TARGET).rpx: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).rpx