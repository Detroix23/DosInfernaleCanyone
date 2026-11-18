# TP9: Canyon infernal.

## Introduction.

Rapidly descend in an unpredictable and unforgiving canyon. All playable _only_ in the terminal.

The Canyon :
![The cyclist in the Canyon.](./docs/Screenshot_Game2_v1.0.png)

## Playing.

Use the keys :
- `h` : left ;
- `l` : right ;

**Goal**: stay in between the ravine and do not crash in the walls.

## Build.

Built on `ncurses`.

Development :
```sh
make dev
```

- Routine for :
```sh
gcc main.c -o bin/main_dev -g -Wall -Wextra -Werror -pedantic -std=c11 -lncurses -fsanitize=address
./main
```

Release :
```sh
make release
```

- Routine for :
```sh
gcc main.c -o bin/infernal-canyon-vX.Y -O2 -lncurses
```
