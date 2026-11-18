CC := gcc
CFLAGS_DEV := -g -Wall -Wextra -Werror -Iinclude -std=c11 -pedantic -fsanitize=address
CFLAGS_RELEASE := -O2
LIBRARIES := -lncurses

BIN := "bin"
SRC := "src"

dev:
	@echo "Building for development \`${BIN}/main-dev\` from \`${SRC}/main.c\`."
	$(CC) "${SRC}/main.c" $(CFLAGS_DEV) -o "${BIN}/main-dev" $(LIBRARIES)

release:
	@echo "Building for release \`${BIN}/infernal-canyone-v1.1\` from \`${SRC}/main.c\`."
	$(CC) "${SRC}/main.c" $(CFLAGS_RELEASE) -o "${BIN}/infernal-canyone-v1.1" $(LIBRARIES)
