# TP9: Canyon infernal.

## Game.

Rapidly descend in an unpredictable and unforgiving canyon. All playable _only_ in the terminal.

The Canyon :
![The cyclist in the Canyon.](./docs/Screenshot_Game2_v1.0.png)

## Build.

Built on `ncurses`.

Development :
```sh
gcc main.c -o main -Wall -Wextra -Werror -pedantic -std=c11 -lncurses -fsanitize=address
./main
```

Release :
```sh
gcc main.c -o infernal-canyon-v1.0 -Wall -Wextra -Werror -pedantic -std=c11 -lncurses -O2
```
