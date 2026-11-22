CC := gcc
CFLAGS_DEV := -g -Wall -Wextra -Werror -Iinclude -std=c11 -pedantic -fsanitize=address
CFLAGS_RELEASE := -O2
LIBRARIES := -lncurses
MAJOR := 1
MINOR := 2
RELEASE_NAME := infernal-canyone-v${MAJOR}.${MINOR}

BIN := bin
SRC := src

dev:
	@echo "Building for development \`${BIN}/main-dev\` from \`${SRC}/main.c\`."
	$(CC) "${SRC}/main.c" $(CFLAGS_DEV) -o "${BIN}/main-dev" $(LIBRARIES)

release:
	@echo "Building for release \`${BIN}/${RELEASE_NAME}\` from \`${SRC}/main.c\`."
	$(CC) "${SRC}/main.c" $(CFLAGS_RELEASE) -o "${BIN}/${RELEASE_NAME}" $(LIBRARIES)
