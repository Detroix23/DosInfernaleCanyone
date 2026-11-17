CC := gcc
CFLAGS_DEV := -g -Wall -Wextra -Werror -Iinclude -std=c11 -pedantic -fsanitize=address
CFLAGS_RELEASE := -O2
LIBRARIES := -lncurses

dev:
	@echo "Building for development."
	$(CC) main.c $(CFLAGS_DEV) -o bin/main-dev $(LIBRARIES)

release:
	@echo "Building for release."
	$(CC) main.c $(CFLAGS_RELEASE) -o bin/infernal-canyone-v1.1 $(LIBRARIES)
