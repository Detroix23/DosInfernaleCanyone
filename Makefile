CC := gcc
CFLAGS_DEV := -g -Wall -Wextra -Werror -Iinclude -std=c11 -pedantic -fsanitize=address
CFLAGS_RELEASE := -O2
LIBRARIES := -lncurses

dev:
	@echo "Building for development \`main-dev\`."
	$(CC) src/main.c $(CFLAGS_DEV) -o bin/main-dev $(LIBRARIES)

release:
	@echo "Building for release \`infernal-canyone-v1.1\`."
	$(CC) src/main.c $(CFLAGS_RELEASE) -o bin/infernal-canyone-v1.1 $(LIBRARIES)
