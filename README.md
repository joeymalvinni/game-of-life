# Conway's Game of Life

Simple implementation of Conway's Game of Life, a two-dimensional cellular automaton.
<br><br>
<img width="1000" alt="image" src="https://github.com/joeymalvinni/game-of-life/assets/76851062/28dff462-b5c5-447d-9b56-f7e9d4d91c6d">

## Rules

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.


## Installation

Clone the github repository:
```
git clone https://github.com/joeymalvinni/game-of-life.git
```

Compile the code:
```
make
```

Run the code:

```
make run
```

## License
[MIT License](LICENSE)
