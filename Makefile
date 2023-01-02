# Makefile
CC := gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -O0 -g -fsanitize=address -static-libasan
LDLIBS = -lm -fsanitize=address -static-libasan
LDFLAGS =

SOURCE := $(shell find src -type f -name "*.c")
OBJECTS = $(SOURCE:%.c=%.o)

TEST := $(shell find test -type f -name "*.c")
OBJECTS_TEST = $(TEST:%.c=%.o)

all: prefix_tree test

prefix_tree: $(OBJECTS)
	$(CC) -o build/prefix_tree $(OBJECTS) $(LDLIBS)

test : prefix_tree $(OBJECTS_TEST)
	$(CC) -o build/test $(OBJECTS) $(OBJECTS_TEST) $(LDLIBS) -lcriterion

clean:
	rm -rf $(OBJECTS) $(OBJECTS_TEST) build/*

.PHONY: all clean neural_network

# END
