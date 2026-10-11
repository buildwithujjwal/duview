# Compiler and flags: -Wall shows warnings, -Iinclude finds headers in include/
CC = gcc
CFLAGS = -Wall -Iinclude

# Source files and the program name
SRC = src/main.c src/tree.c src/sort.c src/terminal.c src/ui.c
TARGET = duview

HDR = include/tree.h include/sort.h include/terminal.h include/ui.h

# Default target: build the program
$(TARGET): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Remove the built program
clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: clean