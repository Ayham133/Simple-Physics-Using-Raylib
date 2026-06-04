CC = gcc
CFLAGS = -Wall
TARGET = game

# Declare phony targets so make doesn't look for files named 'run' or 'all'
.PHONY: all run clean

# Default target builds the game
all: $(TARGET)

# Links the source files into the executable
$(TARGET): main.c object.c
	$(CC) $(CFLAGS) main.c object.c -o $(TARGET) -lraylib -lm -lpthread -ldl -lrt -lX11

# Runs the compiled game automatically
run: $(TARGET)
	./$(TARGET)

# Optional but recommended: cleans up the binary
clean:
	rm -f $(TARGET)
