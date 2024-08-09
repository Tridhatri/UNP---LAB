# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic -std=c99

# Output binary
OUTPUT = 2127_2117

# Source files
SRC = main.c database.c student.c course.c

# Header files
HEADERS = database.h student.h course.h sDB.h

# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: $(OUTPUT)

# Link object files to create the executable
$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJ) $(OUTPUT)

# Phony targets
.PHONY: all clean