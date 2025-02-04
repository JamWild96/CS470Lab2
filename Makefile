# Compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c17 -Wall -Wextra -pedantic

# Target executable name
TARGET = progmgr_sim

# Source files
SRC = procmgr_sim.c

# Object files
OBJ = $(SRC:.c=.o)

# Default target (builds the executable)
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program after building (Creates a test file first)
run: $(TARGET)
# Debug Mode (includes debug symbols)
debug: CFLAGS += -g
debug: $(TARGET)

# Verbose Mode (prints each command)
verbose: CFLAGS += -v
verbose: $(TARGET)

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

# PHONY targets (to prevent conflicts with real files)
.PHONY: all clean run debug verbose
