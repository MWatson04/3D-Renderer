SRC = *.c
CC = gcc
CFLAGS = -Wall -std=c99
LIBS = -lSDL2 -lm

# Debug target
Debug:
	mkdir -p ./bin/Debug
	$(CC) $(CFLAGS) -g $(SRC) $(LIBS) -o ./bin/Debug/3DR

# Release target
Release:
	mkdir -p ./bin/Release
	$(CC) $(CFLAGS) -O2 $(SRC) $(LIBS) -o ./bin/Release/3DR

# Custom build target for direct use
build:
	ifeq ($(MODE), debug)
		$(MAKE) Debug
	else
		$(MAKE) Release
	endif

# Run target
run:
	ifeq ($(MODE), debug)
		./bin/Debug/3DR
	else
		./bin/Release/3DR
	endif

# Clean target
clean:
	rm -f ./bin/Debug/3DR ./bin/Release/3DR
